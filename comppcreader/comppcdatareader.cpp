#include <iostream>
#include <iomanip>
#include <zlib.h>

#define TMP_BUF_SIZE 32768

int main (int argc, const char *argv[])
{
    if (argc <= 1) {
        std::cerr << "ERROR: No input file specified." << std::endl;
        return -1;
    }
    FILE *pInFile = ::fopen(argv[1], "rb");
    if (pInFile == nullptr) {
        std::cerr << "ERROR: Cannot open file " << argv[1] << " for reading." << std::endl;
        return -1;
    }

    int32_t pcVal = 0, flags = 0;
    // Read the headers...
    ::fread(&pcVal, 4, 1, pInFile);
    std::cout << "Sync header: 0x" << std::hex << std::setw(8)
        << std::setfill('0') << pcVal << std::endl;
    ::fread(&pcVal, 4, 1, pInFile);
    std::cout << "Version: 0x" << std::hex << std::setw(8)
        << std::setfill('0') << pcVal << std::endl;

    uint8_t inBuf[TMP_BUF_SIZE * sizeof(uint32_t)];
    uint32_t outBuf[TMP_BUF_SIZE];
    z_stream inStrm;

    inStrm.zalloc = Z_NULL;
    inStrm.zfree = Z_NULL;
    inStrm.opaque = Z_NULL;
    inStrm.avail_in = 0;
    inStrm.next_in = Z_NULL;
    int ret = inflateInit(&inStrm);
    if (ret != Z_OK) {
        std::cerr << "ERROR: Cannot initialize inflation stream." << std::endl;
        return ret;
    }

    bool start = true;
    do {
        inStrm.avail_in = ::fread(inBuf, 1, TMP_BUF_SIZE * sizeof(uint32_t), pInFile);
        if (inStrm.avail_in == 0) {
            break;
        }
        inStrm.next_in = inBuf;

        do {
            inStrm.avail_out = TMP_BUF_SIZE * sizeof(uint32_t);
            inStrm.next_out = (uint8_t *)outBuf;
            ret = inflate(&inStrm, Z_NO_FLUSH);
            bool bReportedErr = false;
            switch (ret) {
                case Z_NEED_DICT:
                    std::cerr << "ERROR: Z_NEED_DICT\n";
                    bReportedErr = true;
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                    if (!bReportedErr) {
                        std::cerr << "ERROR: Z_DATA_ERROR\n";
                        bReportedErr = true;
                    }
                case Z_MEM_ERROR:
                    if (!bReportedErr) {
                        std::cerr << "ERROR: Z_MEM_ERROR\n";
                        bReportedErr = true;
                    }
                    inflateEnd(&inStrm);
                    return ret;
            }
            for (int32_t i = 0; i < (TMP_BUF_SIZE*sizeof(uint32_t) - inStrm.avail_out) / sizeof(uint32_t); ++i) {
                if (start) {
                    std::cout << "PC: 0x" << std::hex << std::setw(8)
                        << std::setfill('0')<< outBuf[i]
                        << std::dec << std::setw(0) << ", Num Insns: " << outBuf[++i] << std::endl;
                    start = false;
                } else {
                    std::cout << "Rel PC: " << std::dec << static_cast<int32_t>(outBuf[i])
                                          << ", Num Insns: " << outBuf[++i] << std::endl;
                }
            }
        } while (inStrm.avail_out == 0);
    } while (ret != Z_STREAM_END);
    inflateEnd(&inStrm);

    ::fclose(pInFile);
}
