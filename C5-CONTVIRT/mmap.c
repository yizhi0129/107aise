#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char ** argv)
{
	int fd = open("./shmfile", O_RDWR | O_CREAT, 0700);

	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	ftruncate(fd, 1024*1024*100);


	void * addr = mmap(NULL, 1024*1024*100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if(addr == NULL)
	{
		perror("mmap");
		return 1;
	}

	unlink("./shmfile");

	pid_t c = fork();

	if(c==0)
	{
		int i;

		while(i < 10000)
		{
			int * pi = (int *)addr;
			i++;
			*pi = i;
			sleep(1);
		}

	}
	else
	{
		while(1)
		{
			int *pi = (int*)addr;
			printf("%d\n", *pi);
			sleep(1);
		}

		wait(NULL);
		munmap(addr, 1024*1024*100);
	}




	return 0;

}
