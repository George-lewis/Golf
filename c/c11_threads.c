////////////////////////////////////////////////////////////
// Demonstrates use of the standard C11 threading library //
////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <threads.h>

#define SIZE 10

int _print_t(void *arg) {
    
	printf("%s", arg);

	return 0;
	
}

thrd_t print_t(char *str) {

	thrd_t t;

	if (thrd_success != thrd_create(&t, _print_t, str)) {
		fprintf(stderr, "Failed to create thread\n");
		exit(EXIT_FAILURE);
	}

	return t;

}

int main(int argc, const char **argv) {

	thrd_t threads[SIZE + 1];

	threads[0] = print_t("Hello C11 threads!\n");

	char **lines = malloc( sizeof(char*) * SIZE );

	// Create the strings
	for (int i = 0; i < SIZE; i++) {
		lines[i] = malloc( sizeof(char) * 4 );
		sprintf(lines[i], "%d\n", i);
	}

	// Invoke threads
	for (int i = 0; i < SIZE; i++) {
		threads[i + 1] = print_t(lines[i]);
	}

	// Join threads and free mem
	for (int i = 0; i < SIZE + 1; i++) {
		
		thrd_join(threads[i], NULL);
	
		free(lines[i]);

	}

	free(lines);

}
