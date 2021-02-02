/*
 * QEMU System Emulator
 *
 * Copyright (c) 2003-2020 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qemu/osdep.h"
#include "qemu-common.h"
#include "sysemu/sysemu.h"
#include <zlib.h>

#ifdef CONFIG_SDL
#if defined(__APPLE__) || defined(main)
#include <SDL.h>
static int qemu_main(int argc, char **argv, char **envp);
int main(int argc, char **argv)
{
    return qemu_main(argc, argv, NULL);
}
#undef main
#define main qemu_main
#endif
#endif /* CONFIG_SDL */

#ifdef CONFIG_COCOA
#undef main
#define main qemu_main
#endif /* CONFIG_COCOA */

FILE *_pTBLog = NULL;
FILE *_pPCLog = NULL;
z_stream *_pPCZStrm = NULL;
z_stream *_pTBZStrm = NULL;
void dumpValCompressed(uint32_t val, uint8_t bForce);
void dumpTBData(uint8_t *pBuffer, uint32_t bufSize);
pthread_t _pDumpThreadID = 0;
uint8_t _nThreadStop = 0;

int main(int argc, char **argv, char **envp)
{
    // VIGGY: Open TB/PC dump log files...
    _pPCLog = fopen("pc-data.bin", "w+b");
    _pPCZStrm = (z_stream *)malloc(sizeof(z_stream));
    _pPCZStrm->zalloc = Z_NULL;
    _pPCZStrm->zfree = Z_NULL;
    _pPCZStrm->opaque = Z_NULL;
    deflateInit(_pPCZStrm, Z_DEFAULT_COMPRESSION);
    _pTBLog = fopen("tb-data.bin", "w+b");
    _pTBZStrm = (z_stream *)malloc(sizeof(z_stream));
    _pTBZStrm->zalloc = Z_NULL;
    _pTBZStrm->zfree = Z_NULL;
    _pTBZStrm->opaque = Z_NULL;
    deflateInit(_pTBZStrm, Z_DEFAULT_COMPRESSION);
    uint32_t tmpVal = __builtin_bswap32(0x5a5aa5a5);
    fwrite(&tmpVal, 4, 1, _pPCLog);
    fwrite(&tmpVal, 4, 1, _pTBLog);
    tmpVal = 1000;
    fwrite(&tmpVal, 4, 1, _pPCLog);
    fwrite(&tmpVal, 4, 1, _pTBLog);

    qemu_init(argc, argv, envp);
 
    qemu_main_loop();

    if (_pPCLog != NULL) {
        dumpValCompressed(0, 0);
        dumpValCompressed(0, 1);

        dumpTBData(NULL, 0);

        _nThreadStop = 1;
        pthread_join(_pDumpThreadID, NULL);

        fclose(_pPCLog);
        fclose(_pTBLog);
        deflateEnd(_pPCZStrm);
        deflateEnd(_pTBZStrm);
        free(_pPCZStrm);
        free(_pTBZStrm);
    }
    //fclose(_pTBLog);

    qemu_cleanup();

    return 0;
}
