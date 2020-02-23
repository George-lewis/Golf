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
