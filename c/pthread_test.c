///////////////////////////
// Demonstrates PThreads //
///////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 4

typedef struct {
	int *in, start, len, tnum;
} proc_args;

void* proc(void *args) {

	proc_args *aargs = args;

	printf("Thread-%d Start; start: %d\n", aargs->tnum, aargs->start, aargs->len);

	for (int i = 0; i < aargs->len; i++) {

		int idx = aargs->start + i, *v = aargs->in + idx, old = *v;

		*v = (*v) * (*v);

		printf("[%d]: %d -> %d\n", idx, old, *v);

	}

}

void set(proc_args *arg, int *in, int start, int len, int tnum) {
	arg->in = in;
	arg->start = start;
	arg->len = len;
	arg->tnum = tnum;
}

void print_arr(int *arr, size_t n) {

	printf("{ ");

	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			printf("%d", arr[i]);
		} else {
			printf("%d, ", arr[i]);
		}
	}

	printf(" }\n");

}

int main() {

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	
	int len = sizeof(arr) / sizeof(int);

	print_arr(arr, len);

	pthread_t threads[NTHREADS];
	proc_args args[NTHREADS]; 

	for (int i = 0; i < NTHREADS; i++) {
		set(args + i, arr, (len / NTHREADS) * i, len / NTHREADS, i + 1);
		pthread_create(threads + i, NULL, proc, args + i);
	}

	for (int i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	print_arr(arr, len);
	
	exit(EXIT_SUCCESS);

}

// Sample output:
//
// { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }
// Thread-1 Start; start: 0
// [0]: 1 -> 1
// [1]: 2 -> 4
// [2]: 3 -> 9
// Thread-2 Start; start: 3
// [3]: 4 -> 16
// [4]: 5 -> 25
// [5]: 6 -> 36
// Thread-3 Start; start: 6
// [6]: 7 -> 49
// [7]: 8 -> 64
// [8]: 9 -> 81
// Thread-4 Start; start: 9
// [9]: 10 -> 100
// [10]: 11 -> 121
// [11]: 12 -> 144
// { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144 }
