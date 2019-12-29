// This needs to be cleaned up

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int mgetenv(char** env, const char* key, char** buffer) {

	char *cur;
	
	int i = 0;
	
	while ( (cur = env[i]) != NULL ) {
	
		if ( strncmp(key, cur, strlen(key)) == 0 ) {
	
			*buffer = cur + strlen(key) + 1;
	
			return 1;
	
		}
	
		i++;
	
	}
	
	return 0;

}

char* takeUntil(char* str, const char until) {

	char *out = malloc(strlen(str) * sizeof(char));	
	
	char cur;
	
	int i = 0;
	
	while ( (cur = str[i]) != until && i < strlen(str) ) {
		
		out[i] = cur;
	
		i++;
	
	}
	
	return out;

}

//char** keys() {
//
//
//
//}

int main(int argc, char** argv, char** envp) {

	char *str, *user;
	
	int i = 0;
	
	while ( (str = envp[i]) != NULL ) {
	
		printf("%i: %s\n", i, str);
	
		if (strncmp("USER", str, 4) == 0)
			user = str + 5;
	
		i++;
	
	}
	
	char* buf;
	
	if (mgetenv(envp, "SHELL", &buf) == 0)
		printf("mgetenv error\n");
	else
		printf("TERM: %s\n", buf);
	
	printf("envp is %i strings long\n", i);
	
	printf("Hello world!\n");
	
	printf("Hello %s!\n", user);
	
	char *spl = takeUntil("abcdn123", 'n');
	
	printf("split: %s\n", spl);
	
	free(spl);
	
	return 0;

}
