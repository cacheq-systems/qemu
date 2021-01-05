
#include <cstdint>
#include <stdio.h>
#include "huffinterface.h"
#include "huffman.h"

namespace
{
}

uint32_t huffCompress(uint32_t *pIn, uint32_t size, FILE *pOutfile)
{
    unsigned char *pBufout = NULL;
    uint32_t compSize = 0;

    huffman_encode_memory(reinterpret_cast<unsigned char *>(pIn), size * sizeof(uint32_t), &pBufout, &compSize);

    // Write the compressed data...
    fwrite(&compSize, sizeof(compSize), 1, pOutfile);
    fwrite(pBufout, compSize * sizeof(unsigned char), 1, pOutfile);

    return compSize;
}

uint32_t huffDecompress(uint32_t *pIn, uint32_t size, FILE *pInfile)
{
    return 0;
}
