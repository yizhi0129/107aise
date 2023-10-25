#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

struct particule
{
	int x;
	int y;
};

#define NUM_PART 128

int main(int argc, char ** argv)
{
	struct particule * part = malloc(sizeof(struct particule) * NUM_PART);

	if(!part)
	{
		perror("malloc");
		return 1;
	}

	int fd = open("./part.dat", O_RDONLY);

	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	size_t to_read = sizeof(struct particule) * NUM_PART;
	size_t tread = 0;

	while(tread != to_read)
	{
		ssize_t ret = read( fd, (char*)part + tread, to_read - tread);
		
		if(ret == 0)
		{
			printf("PAS normal");
			return 1;
		}

		if(ret < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}

			perror("read");
			return 1;
		}
		
		tread += ret;

	}


	int i;
	for(i = 0 ; i < NUM_PART; i++)
	{
		if( part[i].x !=  i)
		{
			printf("Erreur %d != %d\n", part[i].x, i);
		}

		if( part[i].y != i+1)
		{
			printf("Erreur %d != %d\n", part[i].y, i+1);
		}
	}




	close(fd);
	free(part);

	return 0;
}

