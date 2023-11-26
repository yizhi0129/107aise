#include <stdio.h>
#include <unistd.h> //for POSIX operating system API functions like fork(), pipe() and I/O primitives (read(), write(), close(), etc.).
#include <stdlib.h> //for general utilities like atoi() and exit().

int main(int argc, char **argv, char ** envp) //envp (environment vector) is a pointer to a null-terminated array of pointers to char, 
//which in turn point to null-terminated strings representing the environment.
{
	int i;
#if 0
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
#endif

	printf("LOL = %s\n", getenv("LOL")); //retrieve the value of the environment variable named "LOL" using the getenv() function.
	//If "LOL" is not found in the environment variables, getenv returns a null pointer.
	
	return 0;
}
