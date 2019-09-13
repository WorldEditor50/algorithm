#include "bitmap.h"

unsigned int bit_on(unsigned int x, unsigned int position)
{
	return	x | (1 << (position - 1));
}

unsigned int bit_off(unsigned int x, unsigned int position)
{
	return	x & (~(1 << (position - 1)));
}

void bit_swap(unsigned int *x1, unsigned int *x2, unsigned int position)
{
	unsigned int bit1 = 0;
	unsigned int bit2 = 0;
	bit1 = (*x1) & (1 << (position - 1));
	bit2 = (*x2) & (1 << (position - 1));
	if (bit1 ^ bit2 != 0) {
		if (bit1 == 0) {
			(*x1) |= bit2;
			(*x2) &= ~(1 << (position - 1));
		} else {
			(*x2) |= bit1;
			(*x1) &= ~(1 << (position - 1));
		}
	}
	return;
}

unsigned int bit_inverse(unsigned int x, unsigned int position)
{
	unsigned int bit = 0;
	bit = x & (1 << (position - 1));
	if (bit != 0) {
		return x & (~bit);
	} else {
		return x | (1 << (position - 1));
	}
}

int getSize(int *array, int arrayLen)
{
	if (array == NULL) {
		return 0;
	}
	int size = 0;
	int i = 0;
	int max = array[0];

	for (i = 0; i < arrayLen; i++) {
		if (array[i] > max) {
			max = array[i];
		}
	}
	size = max/32 +1;
	return size;
}
unsigned int *bitmap_new(int size)
{
	if (size == 0) {
		return NULL;
	}
	unsigned int *bitmap = NULL;
	bitmap = (unsigned int*)malloc(size * sizeof(unsigned int));
	if (bitmap == NULL) {
		printf("%s\n", "map malloc fail");
	}
	memset(bitmap, 0, size * sizeof(unsigned int));
	return bitmap;
}
int mapping(unsigned int *bitmap,int *array, int arrayLen)
{
	if (bitmap == NULL || array == NULL) {
		return BITMAP_ERR; 
	}
	int i = 0;
	int index = 0;

	for (i = 0; i < arrayLen; i++) {
		/* g(x)/32 --> index, g(x)%32 --> value,(index, value) */
		index = array[i] / 32;
		bitmap[index] |= (1 << (array[i] % 32));
	}
	return BITMAP_OK;
}
int inverseMapping(int *array, unsigned int *bitmap, int bitmapLen)
{
	if (bitmap == NULL || array == NULL) {
		return BITMAP_ERR; 
	}
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i < bitmapLen; i++) {
		for (j = 0; j < 32; j++) {
			/* if the number is in bitmap */
			if ((bitmap[i] & (1 << j)) != 0) {
				array[k++] = i * 32 + j;
			}
		}
	}
	return BITMAP_OK;
}
void bitmap_delete(unsigned int *bitmap)
{
	if (bitmap != NULL) {
		free(bitmap);
	}
	return;
}
