#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int first, int last, int *pArray)
{
	int i = 0;
	for (i = first; i < last + 1; i++) {
		printf("%d\t", pArray[i]);
	}
	printf("\n");
	return;
}
void bubble_sort(int first, int last, int *pArray)
{
	int i = 0;
	int j = 0;
	int tmp;
	for (i = first; i < last; i++) {
		for (j = i + 1; j < last + 1; j++) {
			if (pArray[i] > pArray[j]) {
				tmp = pArray[i];
				pArray[i] = pArray[j];
				pArray[j] = tmp;
			}
		}
	}
	return;
}
void select_sort(int first, int last, int *pArray)
{
	int i = 0;
	int j = 0;
	int min_value;
	int min_pos;
	int tmp;
	for (i = first; i < last + 1; i++) {
		min_pos = i;
		min_value = pArray[i];
		for (j = i + 1; j < last + 1; j++) {
			if (pArray[j] < min_value) {
				min_value = pArray[j];
				min_pos = j;
			}
		}
		if (min_pos != i) {
			tmp = pArray[i];
			pArray[i] = min_value;
			pArray[min_pos] = tmp;
		}
	}
	return;
}
void quick_sort(int first, int last, int *pArray)
{
	if (first > last) {
		return;
	}
	int i = first;
	int j = last;
	int ref = pArray[first];
	while (i < j) {
		while (i < j && pArray[j] > ref) {
			j--;
		}
		pArray[i] = pArray[j];
		while (i < j && pArray[i] < ref) {
			i++;
		}
		pArray[j] = pArray[i];
	}
	pArray[i] = ref;
	quick_sort(first, i - 1, pArray);
	quick_sort(i + 1, last, pArray);
	return;
}
void merge_sort(int first, int last, int *pArray1, int *pArray2)
{
	if (last - first < 1) {
		return;
	}
	int i = 0;
	int j = 0;
	int k = 0;
	int mid = (first + last) / 2;
	merge_sort(first, mid, pArray1, pArray2);
	merge_sort(mid + 1, last, pArray1, pArray2);
	i = first;
	j = mid + 1;
	k = first;
	while ((i < mid + 1) && (j < last + 1) && (k < last + 1)) {
		if (pArray1[i] < pArray1[j]) {
			pArray2[k] = pArray1[i];
			i++;
		} else {
			pArray2[k] = pArray1[j];
			j++;
		}
		k++;
	}
	while (i < mid + 1) {
		pArray2[k] = pArray1[i];
		i++;
		k++;
	}
	while (j < last + 1) {
		pArray2[k] = pArray1[j];
		j++;
		k++;
	}
	for (k = first; k < last + 1; k++) {
		pArray1[k] = pArray2[k];
	}
	return;
}
void count_sort(int first, int last, int *pArray)
{
	int max = pArray[0];
	int i = 0;
	int j = 0;
	int k = 0;
	int index = 0;
	for (i = 1; i < last + 1; i++) {
		if (pArray[i] > max) {
			max = pArray[i];
		}
	}
	int *count = (int *)malloc(sizeof(int) * (max + 1));
	if (count == NULL) {
		return;
	}
	for (i = 0; i < max + 1; i++) {
		count[i] = 0;
	}
	for (i = 0; i < last + 1; i++) {
		index = pArray[i];
		count[index]++;
	}
	for (i = 0; i < max + 1; i++) {
		for (j = 0; j < count[i]; j++) {
			pArray[k] = i;
			k++;
		}
	}
	return;
}
int main()
{
	int array1[10] = {8, 2, 4, 9, 6, 0, 5, 7, 1, 3};
	int array2[10] = {1, 7, 6, 4, 5, 0, 8, 2, 9, 3};
	int array3[10] = {7, 2, 6, 9, 0, 4, 3, 8, 1, 5};
	int array4[10] = {0, 9, 1, 2, 8, 6, 5, 7, 4, 3};
	int array5[10] = {3, 2, 6, 9, 4, 0, 5, 7, 1, 8};
	int tmp[10];
	printf("bubble sort\n");
	printArray(0, 9, array1);
	bubble_sort(0, 9, array1);
	printArray(0, 9, array1);
	printf("select sort\n");
	printArray(0, 9, array2);
	select_sort(0, 9, array2);
	printArray(0, 9, array2);
	printf("quick sort\n");
	printArray(0, 9, array3);
	quick_sort(0, 9, array3);
	printArray(0, 9, array3);
	printf("merge sort\n");
	printArray(0, 9, array4);
	merge_sort(0, 9, array4, tmp);
	printArray(0, 9, array4);
	printf("count sort\n");
	printArray(0, 9, array5);
	count_sort(0, 9, array5);
	printArray(0, 9, array5);
	return 0;
}
