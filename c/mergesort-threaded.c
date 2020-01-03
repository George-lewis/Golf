//
// Mulit-threaded merge sort implemented in C using pthreads
//
// NOTICE: This code is non-functional
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define SORT(a) sort(a, 0, sizeof(a)/sizeof(a[0]))
#define PRINT(a) print(a, sizeof(a)/sizeof(a[0]))

void print(int*, int);

typedef struct {

    int* a;
    int b;
    int c;

} args;

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

void* sort(void* in) {

    printf("sort\n");

    args arg = *((args*)in);

    int* arr = arg.a;

    int l = arg.b;

    int r = arg.c;

    int size = r - l;

    if (size < 2) {

        return;

    } else {

        int middle = size / 2;

        args x = {&arr[0], 0, middle};

        sort(&x);

        args y = {&arr[middle], 0, r - middle};

        sort(&y);

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

void benchmark(int size, int num_tests) {

    srand(time(NULL));

    for (int i = 0; i < num_tests; i++) {

        int* arr = rand_array(size);

        clock_t start = clock();

        args x = {arr, 0, size};

        sort(&x);

        clock_t now = clock();

        printf("Took: %f seconds\n", (double)(now - start) /CLOCKS_PER_SEC);

    }

}

int main() {

    // int a[] = {4, 3, 2, 1, 0};

    // SORT(a);

    // PRINT(a);

    // benchmark(1000000, 100);

    int* big = rand_array(1000000);

    pthread_t threads[10];

    int c = 1000000 / 10;

    args a = {&big[0], 0, 1000000};

    int res = pthread_create(&threads[0], NULL, sort, &a);

    pthread_join(threads[0], NULL);

    printf("Thread returns: %d", res);

    // for (int i = 0; i < 10; i++) {

    //     args a = {big, c*i, c*(i+1)};

    //     pthread_create(&threads[i], NULL, sort, &a);

    // }

    // for (int i = 0; i < 10; i++) {

    //     pthread_join(threads[i], NULL);

    // }

    for (int i = 0; i < 100; i++) {
        printf("%d\n", big[i]);
    }

    free(big);

}
