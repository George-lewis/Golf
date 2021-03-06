//
// Merge sort implemented in C
//
// On my machine this algorithm can sort an array of one million elements
// In less than 100 milliseconds when compiled with gcc with the flags `-O3 -march=native`
// Even faster with `-finline-functions`
//
// Update: With Clang/LLVM my computer does it in about 30 milliseconds!
// I had no idea Clang is this much faster than GCC
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

        if (li >= asize) {
            out[li + ri] = b[ri];
            ri++;
        } else if (ri >= bsize) {
            out[li + ri] = a[li];
            li++;
        } else if (a[li] < b[ri]) {
            out[li + ri] = a[li];
            li++;
        } else {
            out[li + ri] = b[ri];
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

        arr = new;

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

// Calculates the mean iteratively
// This fixes issues with integer overflows
// See https://stackoverflow.com/questions/1930454/what-is-a-good-solution-for-calculating-an-average-where-the-sum-of-all-values-e
double mean(double* data, size_t size) {

    double avg = 0;
    
    for (int i = 1; i <= size; i++) {
        avg += (data[i - 1] - avg) / i;
    }
    
    return avg;

}

void benchmark(int size, int num_tests) {

    srand(time(NULL));

    double timings[num_tests];

    for (int i = 0; i < num_tests; i++) {

        int* arr = rand_array(size);

        clock_t start = clock();

        sort(arr, 0, size);

        clock_t now = clock();

        clock_t diff = now - start;

        double secs = (double)(now - start) / CLOCKS_PER_SEC;

        timings[i] = secs;

        printf("Took: %f seconds\n", secs);

    }

    printf( \
"\n\
-----------\n\
| RESULTS |\n\
-----------\n\
Completed: %d sorts\n\
Array length: %d\n\
Average time per sort: %f seconds\n\
-----------\n",
        num_tests, size, mean(timings, num_tests));

}

int main() {

    int a[] = {4, 3, 2, 1, 0};

    SORT(a);

    PRINT(a);

    benchmark(1000000, 100);

}