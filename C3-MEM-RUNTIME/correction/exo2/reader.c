#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>






int main(int argc, char *argv[])
{
	int fd = open("./file.txt", O_RDWR | O_CREAT, 0600);
	if(fd < 0)
	{
		perror("open");
		abort();
	}

	void* p = mmap(NULL, 64, PROT_READ, MAP_FILE | MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap");
		abort();
	}

	int pid = -1;
	memcpy(&pid, p,  sizeof(int));


	printf("Reader: PID = %d\n", pid);
	kill(pid, SIGUSR1);

	munmap(p, 64);

	return 0;
}
