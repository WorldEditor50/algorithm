#include "bitmap.h"

void printArray(int *pArray, int arrayLen)
{
	int i = 0;
	for (i = 0; i < arrayLen; i++) {
		printf("%d\t",pArray[i]);
	}
	printf("\n");
	return;
}

int main()
{
	int i = 0;
	unsigned int bitmap[3] = {0};
	int p[10] = {60, 12, 23, 2, 32, 17, 13, 41, 29, 11};
	int q[10] = {0};
	unsigned int *map = NULL;
	map = bitmap_new(3);
	printArray(p, 10);
	mapping(map, p, 10);
	inverseMapping(q, map, 3);
	printArray(q, 10);

	bitmap_delete(map);
	return 0;
}
