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
	unsigned int bitmap[3] = {0};
	int p[10] = {60, 2, 2, 2, 2, 17, 13, 41, 29, 11};
	int q[10] = {0};

	printArray(p, 10);
	mapping(bitmap, p, 10);
	inverseMapping(q, bitmap, 3);
	printArray(q, 10);

	return 0;
}
