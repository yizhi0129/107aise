#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

struct proj
{
	pthread_spinlock_t lock;
	int data[100];
};


int main(int argc, char ** argv)
{
	int fd = open("./shmfile", O_RDWR | O_CREAT, 0700);

	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	ftruncate(fd, 1024*1024*100);


	struct proj * p = (struct proj*) mmap(NULL, 1024*1024*100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if(p == NULL)
	{
		perror("mmap");
		return 1;
	}

	unlink("./shmfile");

	pthread_spin_init(&p->lock, PTHREAD_PROCESS_SHARED); 

	pid_t c = fork();

	if(c==0)
	{
		int i;

		while(1)
		{
			i++;
			pthread_spin_lock(&p->lock);
			p->data[0] = i;
			pthread_spin_unlock(&p->lock);
		}

	}
	else
	{
		while(1)
		{
			pthread_spin_lock(&p->lock);
			printf("%d\n", p->data[0]);
			pthread_spin_unlock(&p->lock);
		}

		wait(NULL);
		munmap(p, 1024*1024*100);
	}




	return 0;

}
