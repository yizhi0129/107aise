#include <stdio.h>
#include <errno.h> //for error reporting
#include <unistd.h> //for POSIX operating system API functions (including unlink)
#include <string.h> //for error reporting


int main(int argc, char ** argv)
{ //unlink(argv[1]) - This function attempts to delete the file specified by the path given in argv[1]. 
//The unlink function returns 0 on success and -1 on failure. 
//If the file cannot be deleted, it sets the errno variable to indicate the specific error.
	if(unlink(argv[1]) < 0)
	{
		perror("unlink argv[1]"); // If unlink fails, perror prints a descriptive error message to the standard error stream (stderr).
	}

	return 0;
}
