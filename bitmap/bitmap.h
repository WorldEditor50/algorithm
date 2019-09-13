#ifndef __bitmap_H
#define __bitmap_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
#define BITMAP_OK		0x01
#define BITMAP_ERR		0x02
//unsigned int *bitmap;
int getSize(int *array, int arrayLen);
unsigned int *bitmap_new(int size);
int mapping(unsigned int *bitmap, int *array, int arrayLen);
int inverseMapping(int *array, unsigned int *bitmap, int bitmapLen);
void bitmap_delete(unsigned int *bitmap);
unsigned int bit_on(unsigned int x, unsigned int position);
unsigned int bit_off(unsigned int x, unsigned int position);
void bit_swap(unsigned int *x1, unsigned int *x2, unsigned int position);
unsigned int bit_inverse(unsigned int x, unsigned int position);

#ifdef __cplusplus
}
#endif//__cplusplus 
#endif// __bitmap_H
