//////////////////
// Demonstrates forking and pipe communication
//////////////////
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

	int fd[2];
	pipe(fd);

	if (!fork()) {
	
		close(fd[0]); // We're not reading in the child
		
		char *msg = "Hello, world!";
  		write(fd[1], msg, strlen(msg));
  		close(fd[1]); // Done writing
  	
		exit(EXIT_SUCCESS);

	} else {
	
		close(fd[1]); // Not writing in the parent

		wait(NULL); // Not strictly necessary but will guarantee we're good
	
		char buf[30] = { 0 };
	
		read(fd[0], buf, 30);
	
		close(fd[0]);
	
		printf("%s\n", buf);
	
		exit(EXIT_SUCCESS);

	}

}
