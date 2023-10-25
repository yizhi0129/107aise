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

	int i;
	for(i = 0 ; i < NUM_PART; i++)
	{
		part[i].x = i;
		part[i].y = i+1;
	}

	int fd = open("./part.dat", O_WRONLY | O_CREAT, 0600);

	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	size_t to_write = sizeof(struct particule) * NUM_PART;
	size_t written = 0;

	while(written != to_write)
	{
		ssize_t ret = write( fd, (char*)part + written, to_write - written);
		
		if(ret < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}

			perror("write");
			return 1;
		}
		
		written += ret;

	}



	close(fd);
	free(part);

	return 0;
}

