#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>




void func(int signal)
{
	if (signal == SIGUSR1)
	{
		printf("youhou !!\n");
	}
	else
	{
		printf("Presque: got %d\n", signal);
	}
}




int main(int argc, char *argv[])
{
	int fd = open("./file.txt", O_RDWR | O_CREAT, 0600);
	if(fd < 0)
	{
		perror("open");
		abort();
	}

	if(ftruncate(fd, 64) < 0)
	{
		perror("ftruncate");
		abort();
	}

	void* p = mmap(NULL, 64, PROT_WRITE, MAP_FILE | MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap");
		abort();
	}

	int pid = getpid();
	memcpy(p, &pid, sizeof(int));

	if(signal(SIGUSR1, func) == SIG_ERR)
	{
		perror("signal");
		abort();
	}

	printf("Stop writer: PID = %d\n", pid);
	pause();

	munmap(p, 64);

	return 0;
}
