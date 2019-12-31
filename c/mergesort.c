//
// Merge sort implemented in C
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SORT(a) sort(a, 0, sizeof(a)/sizeof(a[0]))
#define PRINT(a) print(a, sizeof(a)/sizeof(a[0]))

void print(int*, int);

int* merge(int* a, int asize, int* b, int bsize) {

    int* out = malloc( sizeof(int) * ( asize + bsize ) );

    for (int li = 0, ri = 0; li + ri < asize + bsize;) {

        int ax = a[li];

        int bx = b[ri];

        if ( (li < asize && ax < bx) || ri >= bsize ) {

            out[li + ri] = ax;

            li++;

        } else {

            out[li + ri] = bx;

            ri++;

        }

    }

    return out;

}

void sort(int* arr, int l, int r) {

    int size = r - l;

    if (size < 2) {

        return;

    } else {

        int middle = size / 2;

        sort(&arr[0], 0, middle);

        sort(&arr[middle], 0, r - (middle));

        int* new = merge(&arr[l], middle - l, &arr[middle], r - (middle));

        // Figure out afterwards
        // free(arr);

        for (int i = 0; i < size; i++) {

            arr[i] = new[i];

        }

        free(new);

        // arr = new;

    }

}

void print(int* arr, int size) {

    printf("{");

    for (int i = 0; i < size; i++) {

        if (i >= size - 1) {

            printf("%d", arr[i]);

        } else {

            printf("%d, ", arr[i]);

        }

    }

    printf("}\n");

}

int* rand_array(int size) {

    int* out = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {

        out[i] = rand();

    }

    return out;

}

void benchmark(int size, int num_tests) {

    srand(time(NULL));

    for (int i = 0; i < num_tests; i++) {

        int* arr = rand_array(size);

        clock_t start = clock();

        sort(arr, 0, size);

        clock_t now = clock();

        printf("Took: %f seconds\n", (double)(now - start) /CLOCKS_PER_SEC);

    }

}

int main() {

    int a[] = {4, 3, 2, 1, 0};

    SORT(a);

    PRINT(a);

    benchmark(1000, 10);

}