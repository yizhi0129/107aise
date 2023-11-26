#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h> //for waiting for the child process to complete

int main(int argc, char ** argv )
{
	int val = 2;
	pid_t child = fork(); //creates a new process (child process)
//pid_t is a data type used to represent process IDs (PIDs)
// integer type
//The fork function returns the PID of the child process to the parent process, and returns 0 to the child process.
	if( child == 0 )
	{
		val++;
	} else { //parent process (child > 0)
		val+=2;
		wait(NULL); //The wait function makes the parent process wait until the child process terminates.
	}
//After the if-else block, both the parent and child processes execute this line. 
//It prints information about the process IDs (getpid() for the current process, getppid() for the parent process) and the value of val.
	fprintf(stderr, "PID %d PPID %d VAL is %d\n",
			getpid(),
			getppid(),
			val);

	return 0;
}
