
#ifndef HUFF_COMPRESS
#define HUFF_COMPRESS

#ifdef __cplusplus
extern "C" {
#endif

uint32_t huffCompress(uint32_t *pIn, uint32_t size, FILE *pOutfile);
uint32_t huffDecompress(uint32_t *pIn, uint32_t size, FILE *pInfile);


#ifdef __cplusplus
};
#endif

#endif
