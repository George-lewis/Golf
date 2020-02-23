//////////////////
// Demonstrates forking and pipe communication
//////////////////
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {

	int fd[2];
	pipe(fd);

	if (!fork()) {
  		char *msg = "Hello, world!";
  		write(fd[1], msg, strlen(msg));
  		close(fd[1]);
  		exit(EXIT_SUCCESS);
	}
	
	wait(NULL);
	
	char buf[30] = { 0 };
	
	read(fd[0], buf, 30);
	
	close(fd[0]);
	
	printf("%s\n", buf);
	
	exit(EXIT_SUCCESS);

}
