/*
 *
 * The goal is to create an array of length n which has unique integers and sums to zero
 *
 */

#include <stdio.h>
#include <stdlib.h>

int* sumToZero(int n) {

	int* arr = malloc(sizeof(int) * n);

	if (n % 2 == 0) {
		for (int i = 1; i < n; i+=2) {
			arr[i-1] = i;
			arr[i] = -i;
		}
	} else {
		
		arr[0] = 0;

		for (int i = 1; i < n; i+=2) {
			arr[i] = i;
			arr[i+1] = -i;
		}

	}

	return arr;

}

// Utility
void print_array(int* arr, int size) {

	printf("[");

	for (int i = 0; i < size; i++) {
		if (i == size-1)
			printf("%d", arr[i]);
		else
			printf("%d,", arr[i]);
	}

	printf("]\n");

}

int main() {

	int* a = sumToZero(10);

	print_array(a, 10); // [1,-1,3,-3,5,-5,7,-7,9,-9]

	free(a);

	int* b = sumToZero(11);

	print_array(b, 11); // [0,1,-1,3,-3,5,-5,7,-7,9,-9]

	free(b);

}
