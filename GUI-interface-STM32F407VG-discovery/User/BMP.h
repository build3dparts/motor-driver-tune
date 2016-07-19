#ifndef __BMP_HDR__
#define __BMP_HDR__

#include "stm32f4xx.h"

typedef struct _DIB{
	uint32_t header_sz;
	uint32_t Width;
	uint32_t Height;
	uint16_t color_planes;
	uint16_t bpp;
	uint32_t compresion_method;
	uint32_t raw_bmp_size;
	uint32_t horiz_res;
	uint32_t vert_res;
	uint32_t nr_colors;
	uint32_t important_colors;	
}__attribute__((packed))DIB;

typedef struct _BMP{
	uint16_t BMP_sig;
	uint32_t BMP_size;
	uint32_t reserved;
	uint32_t bmpoffset;	
	DIB dib_data;
}__attribute__((packed))BMP;

#endif
