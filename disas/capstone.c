/*
 * Interface to the capstone disassembler.
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "qemu/bswap.h"
#include "disas/dis-asm.h"
#include "disas/capstone.h"

// VIGGY:
#include "disas/target-isa.h"
#include <zlib.h>

/*
 * Temporary storage for the capstone library.  This will be alloced via
 * malloc with a size private to the library; thus there's no reason not
 * to share this across calls and across host vs target disassembly.
 */
static __thread cs_insn *cap_insn;

/*
 * The capstone library always skips 2 bytes for S390X.
 * This is less than ideal, since we can tell from the first two bits
 * the size of the insn and thus stay in sync with the insn stream.
 */
static size_t CAPSTONE_API
cap_skipdata_s390x_cb(const uint8_t *code, size_t code_size,
                      size_t offset, void *user_data)
{
    size_t ilen;

    /* See get_ilen() in target/s390x/internal.h.  */
    switch (code[offset] >> 6) {
    case 0:
        ilen = 2;
        break;
    case 1:
    case 2:
        ilen = 4;
        break;
    default:
        ilen = 6;
        break;
    }

    return ilen;
}

static const cs_opt_skipdata cap_skipdata_s390x = {
    .mnemonic = ".byte",
    .callback = cap_skipdata_s390x_cb
};

/*
 * Initialize the Capstone library.
 *
 * ??? It would be nice to cache this.  We would need one handle for the
 * host and one for the target.  For most targets we can reset specific
 * parameters via cs_option(CS_OPT_MODE, new_mode), but we cannot change
 * CS_ARCH_* in this way.  Thus we would need to be able to close and
 * re-open the target handle with a different arch for the target in order
 * to handle AArch64 vs AArch32 mode switching.
 */
static cs_err cap_disas_start(disassemble_info *info, csh *handle)
{
    cs_mode cap_mode = info->cap_mode;
    cs_err err;

    cap_mode += (info->endian == BFD_ENDIAN_BIG ? CS_MODE_BIG_ENDIAN
                 : CS_MODE_LITTLE_ENDIAN);

    err = cs_open(info->cap_arch, cap_mode, handle);
    if (err != CS_ERR_OK) {
        return err;
    }

    /* "Disassemble" unknown insns as ".byte W,X,Y,Z".  */
    cs_option(*handle, CS_OPT_SKIPDATA, CS_OPT_ON);

    switch (info->cap_arch) {
    case CS_ARCH_SYSZ:
        cs_option(*handle, CS_OPT_SKIPDATA_SETUP,
                  (uintptr_t)&cap_skipdata_s390x);
        break;

    case CS_ARCH_X86:
        /*
         * We don't care about errors (if for some reason the library
         * is compiled without AT&T syntax); the user will just have
         * to deal with the Intel syntax.
         */
        cs_option(*handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_ATT);
        break;
    }

    /* Allocate temp space for cs_disasm_iter.  */
    if (cap_insn == NULL) {
        cap_insn = cs_malloc(*handle);
        if (cap_insn == NULL) {
            cs_close(handle);
            return CS_ERR_MEM;
        }
    }
    return CS_ERR_OK;
}

static void cap_annot8_insn(TargetIsaData *targIsa, disassemble_info *info,
    cs_insn *insn)
{
    TargetInsn insnData;

    insnData._size = insn->size;
    memcpy(&insnData._bytes, &insn->bytes, sizeof(insnData._bytes));
    g_array_append_val(targIsa->_p_isa_insns, insnData);
    ++targIsa->_insns_size;
}

static void cap_dump_insn_units(disassemble_info *info, cs_insn *insn,
                                int i, int n)
{
    fprintf_function print = info->fprintf_func;
    FILE *stream = info->stream;

    switch (info->cap_insn_unit) {
    case 4:
        if (info->endian == BFD_ENDIAN_BIG) {
            for (; i < n; i += 4) {
                print(stream, " %08x", ldl_be_p(insn->bytes + i));

            }
        } else {
            for (; i < n; i += 4) {
                print(stream, " %08x", ldl_le_p(insn->bytes + i));
            }
        }
        break;

    case 2:
        if (info->endian == BFD_ENDIAN_BIG) {
            for (; i < n; i += 2) {
                print(stream, " %04x", lduw_be_p(insn->bytes + i));
            }
        } else {
            for (; i < n; i += 2) {
                print(stream, " %04x", lduw_le_p(insn->bytes + i));
            }
        }
        break;

    default:
        for (; i < n; i++) {
            print(stream, " %02x", insn->bytes[i]);
        }
        break;
    }
}

static void cap_dump_insn(disassemble_info *info, cs_insn *insn)
{
    fprintf_function print = info->fprintf_func;
    FILE *stream = info->stream;
    int i, n, split;

    print(stream, "0x%08" PRIx64 ": ", insn->address);

    n = insn->size;
    split = info->cap_insn_split;

    /* Dump the first SPLIT bytes of the instruction.  */
    cap_dump_insn_units(info, insn, 0, MIN(n, split));

    /* Add padding up to SPLIT so that mnemonics line up.  */
    if (n < split) {
        int width = (split - n) / info->cap_insn_unit;
        width *= (2 * info->cap_insn_unit + 1);
        print(stream, "%*s", width, "");
    }

    /* Print the actual instruction.  */
    print(stream, "  %-8s %s\n", insn->mnemonic, insn->op_str);

    /* Dump any remaining part of the insn on subsequent lines.  */
    for (i = split; i < n; i += split) {
        print(stream, "0x%08" PRIx64 ": ", insn->address + i);
        cap_dump_insn_units(info, insn, i, MIN(n, i + split));
        print(stream, "\n");
    }
}

// VIGGY: Disassemble at PC, annotate data in TB...
void dumpTBData(uint8_t *pBuffer, uint32_t bufSize);
extern FILE *_pTBLog;
extern z_stream *_pTBZStrm;
#define BUFFER_MAX 65536

void dumpTBData(uint8_t *pBuffer, uint32_t bufSize)
{
    static uint8_t compLogbuf[BUFFER_MAX];
    static uint8_t tmpBuf[BUFFER_MAX];
    static uint32_t logBufSize = 0;

    if ((pBuffer != NULL) && ((logBufSize + bufSize) < BUFFER_MAX)) {
        memcpy(&tmpBuf[logBufSize], pBuffer, bufSize);
        logBufSize += bufSize;
    }
    else {
        if (logBufSize == 0) {
            memset(&tmpBuf, 0, sizeof(uint8_t) * BUFFER_MAX);
            logBufSize = 64;
        }
        unsigned int compSize;
        // Compress the buffer...
        _pTBZStrm->avail_in = logBufSize;
        _pTBZStrm->next_in = (Bytef *)&tmpBuf;
        do {
            _pTBZStrm->avail_out = BUFFER_MAX * sizeof(uint8_t);
            _pTBZStrm->next_out = compLogbuf;
            deflate(_pTBZStrm, (pBuffer == NULL) ? Z_FINISH : Z_SYNC_FLUSH);
            compSize = (BUFFER_MAX * sizeof(uint8_t)) - _pTBZStrm->avail_out;
            fwrite(&compSize, 1, sizeof(compSize), _pTBLog);
            fwrite(&compLogbuf, 1, compSize, _pTBLog);
        } while (_pTBZStrm->avail_out == 0);
        logBufSize = 0;
        if (pBuffer != NULL) {
            memcpy(&compLogbuf, pBuffer, bufSize);
            logBufSize += bufSize;
        }
    }
}

bool cap_disas_annot8(TargetIsaData *targIsa, disassemble_info *info,
    uint64_t pc, size_t size)
{
    uint8_t cap_buf[1024];
    csh handle;
    cs_insn *insn;
    size_t csize = 0;
    static uint8_t tbLogbuf[BUFFER_MAX];
    static uint32_t tbLogbufSz;

    if (cap_disas_start(info, &handle) != CS_ERR_OK) {
        return false;
    }
    insn = cap_insn;

    while (1) {
        size_t tsize = MIN(sizeof(cap_buf) - csize, size);
        const uint8_t *cbuf = cap_buf;

        info->read_memory_func(pc + csize, cap_buf + csize, tsize, info);
        csize += tsize;
        size -= tsize;

        while (cs_disasm_iter(handle, &cbuf, &csize, &pc, insn)) {
            cap_annot8_insn(targIsa, info, insn);
        }

        /* If the target memory is not consumed, go back for more... */
        if (size != 0) {
            /*
             * ... taking care to move any remaining fractional insn
             * to the beginning of the buffer.
             */
            if (csize != 0) {
                memmove(cap_buf, cbuf, csize);
            }
            continue;
        }

        /*
         * Since the target memory is consumed, we should not have
         * a remaining fractional insn.
         */
        if (csize != 0) {
            info->fprintf_func(info->stream,
                "Disassembler disagrees with translator "
                "over instruction decoding\n"
                "Please report this to qemu-devel@nongnu.org\n");
        }
        break;
    }

    // Open the TB log, and log it.
    if (_pTBLog != NULL) {
        //fwrite(&targIsa->_pc_start_addr, 4, 1, _pTBLog);
        //fwrite(&targIsa->_insns_size, 4, 1, _pTBLog);
        tbLogbufSz = 8;
        ((uint32_t *)tbLogbuf)[0] = __builtin_bswap32(targIsa->_pc_start_addr);
        ((uint32_t *)tbLogbuf)[1] = __builtin_bswap32(targIsa->_insns_size);
        for (int i = 0; i < targIsa->_insns_size; ++i) {
            TargetInsn *pInsn = &g_array_index(targIsa->_p_isa_insns, TargetInsn, i);
            for (int j = 0; j < 4/*pInsn->_size*/; ++j) {
                //fwrite(&pInsn->_bytes[j], 1, 1, _pTBLog);
                tbLogbuf[tbLogbufSz++] = pInsn->_bytes[j];
            }
        }
        dumpTBData(tbLogbuf, tbLogbufSz);
    }
    cs_close(&handle);
    return true;
}

/* Disassemble SIZE bytes at PC for the target.  */
bool cap_disas_target(disassemble_info *info, uint64_t pc, size_t size)
{
    uint8_t cap_buf[1024];
    csh handle;
    cs_insn *insn;
    size_t csize = 0;

    if (cap_disas_start(info, &handle) != CS_ERR_OK) {
        return false;
    }
    insn = cap_insn;

    while (1) {
        size_t tsize = MIN(sizeof(cap_buf) - csize, size);
        const uint8_t *cbuf = cap_buf;

        info->read_memory_func(pc + csize, cap_buf + csize, tsize, info);
        csize += tsize;
        size -= tsize;

        while (cs_disasm_iter(handle, &cbuf, &csize, &pc, insn)) {
            cap_dump_insn(info, insn);
        }

        /* If the target memory is not consumed, go back for more... */
        if (size != 0) {
            /*
             * ... taking care to move any remaining fractional insn
             * to the beginning of the buffer.
             */
            if (csize != 0) {
                memmove(cap_buf, cbuf, csize);
            }
            continue;
        }

        /*
         * Since the target memory is consumed, we should not have
         * a remaining fractional insn.
         */
        if (csize != 0) {
            info->fprintf_func(info->stream,
                "Disassembler disagrees with translator "
                "over instruction decoding\n"
                "Please report this to qemu-devel@nongnu.org\n");
        }
        break;
    }

    cs_close(&handle);
    return true;
}

/* Disassemble SIZE bytes at CODE for the host.  */
bool cap_disas_host(disassemble_info *info, void *code, size_t size)
{
    csh handle;
    const uint8_t *cbuf;
    cs_insn *insn;
    uint64_t pc;

    if (cap_disas_start(info, &handle) != CS_ERR_OK) {
        return false;
    }
    insn = cap_insn;

    cbuf = code;
    pc = (uintptr_t)code;

    while (cs_disasm_iter(handle, &cbuf, &size, &pc, insn)) {
        cap_dump_insn(info, insn);
    }
    if (size != 0) {
        info->fprintf_func(info->stream,
            "Disassembler disagrees with TCG over instruction encoding\n"
            "Please report this to qemu-devel@nongnu.org\n");
    }

    cs_close(&handle);
    return true;
}

/* Disassemble COUNT insns at PC for the target.  */
bool cap_disas_monitor(disassemble_info *info, uint64_t pc, int count)
{
    uint8_t cap_buf[32];
    csh handle;
    cs_insn *insn;
    size_t csize = 0;

    if (cap_disas_start(info, &handle) != CS_ERR_OK) {
        return false;
    }
    insn = cap_insn;

    while (1) {
        /*
         * We want to read memory for one insn, but generically we do not
         * know how much memory that is.  We have a small buffer which is
         * known to be sufficient for all supported targets.  Try to not
         * read beyond the page, Just In Case.  For even more simplicity,
         * ignore the actual target page size and use a 1k boundary.  If
         * that turns out to be insufficient, we'll come back around the
         * loop and read more.
         */
        uint64_t epc = QEMU_ALIGN_UP(pc + csize + 1, 1024);
        size_t tsize = MIN(sizeof(cap_buf) - csize, epc - pc);
        const uint8_t *cbuf = cap_buf;

        /* Make certain that we can make progress.  */
        assert(tsize != 0);
        info->read_memory_func(pc + csize, cap_buf + csize, tsize, info);
        csize += tsize;

        if (cs_disasm_iter(handle, &cbuf, &csize, &pc, insn)) {
            cap_dump_insn(info, insn);
            if (--count <= 0) {
                break;
            }
        }
        memmove(cap_buf, cbuf, csize);
    }

    cs_close(&handle);
    return true;
}

/* Disassemble a single instruction directly into plugin output */
bool cap_disas_plugin(disassemble_info *info, uint64_t pc, size_t size)
{
    uint8_t cap_buf[32];
    const uint8_t *cbuf = cap_buf;
    csh handle;

    if (cap_disas_start(info, &handle) != CS_ERR_OK) {
        return false;
    }

    assert(size < sizeof(cap_buf));
    info->read_memory_func(pc, cap_buf, size, info);

    if (cs_disasm_iter(handle, &cbuf, &size, &pc, cap_insn)) {
        info->fprintf_func(info->stream, "%s %s",
                           cap_insn->mnemonic, cap_insn->op_str);
    }

    cs_close(&handle);
    return true;
}
