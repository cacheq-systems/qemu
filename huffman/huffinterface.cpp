
#include <cstdint>
#include <stdio.h>
#include "huffinterface.h"
#include "huffman.h"

namespace
{
}

uint32_t huffCompress(uint32_t *pIn, uint32_t size, FILE *pOutfile)
{
    unsigned char *pBufout = new unsigned char[(size * sizeof(uint32_t)) + 384];

    uint32_t compSize = Huffman_Compress(reinterpret_cast<unsigned char *>(pIn), pBufout, size * sizeof(uint32_t));

    // Write the compressed data...
    fwrite(&compSize, sizeof(compSize), 1, pOutfile);
    fwrite(pBufout, compSize * sizeof(unsigned char), 1, pOutfile);

    delete [] pBufout;

    return compSize;
}

uint32_t huffDecompress(uint32_t *pIn, uint32_t size, FILE *pInfile)
{
    return 0;
}
