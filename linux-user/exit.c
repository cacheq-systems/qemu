/*
 *  exit support for qemu
 *
 *  Copyright (c) 2018 Alex Bennée <alex.bennee@linaro.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include "qemu/osdep.h"
#include "qemu.h"
#include <zlib.h>
#ifdef CONFIG_GPROF
#include <sys/gmon.h>
#endif

#ifdef CONFIG_GCOV
extern void __gcov_dump(void);
#endif

extern FILE *_pTBLog;
extern FILE *_pPCLog;
extern z_stream *_pPCZStrm;
extern z_stream *_pTBZStrm;
void dumpValCompressed(uint32_t val, uint8_t bForce);
void dumpTBData(uint8_t *pBuffer, uint32_t bufSize);
extern pthread_t _pDumpThreadID;
extern uint8_t _nThreadStop;

void preexit_cleanup(CPUArchState *env, int code)
{
#ifdef CONFIG_GPROF
        _mcleanup();
#endif
#ifdef CONFIG_GCOV
        __gcov_dump();
#endif
        if (_pTBLog != NULL) {
            dumpTBData(NULL, 0);
            fclose(_pTBLog);
            deflateEnd(_pTBZStrm);
            free(_pTBZStrm);
        }
        if (_pPCLog != NULL) {
            dumpValCompressed(0, 0);
            dumpValCompressed(0, 1);

            _nThreadStop = 1;
            pthread_join(_pDumpThreadID, NULL);

            fclose(_pPCLog);
        }
        if (_pPCZStrm != NULL) {
            deflateEnd(_pPCZStrm);
            free(_pPCZStrm);
        }
        gdb_exit(env, code);
        qemu_plugin_atexit_cb();
}
