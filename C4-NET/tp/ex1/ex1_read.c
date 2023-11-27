#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int fd = open("./starwars.txt", O_RDONLY);

	if(fd < 0 )
	{
		perror("open");
		return 1;
	}

	char buff[1024];

	ssize_t sread = 0;

	while((sread = read(fd, buff, 1024)))
	{
		if(sread == 0)
		{
			break;
		}

		if(sread < 0)
		{
			perror("read");
			break;
		}

		int i;

		for(i = 0 ; i < sread; i++)
		{
			printf("%c", buff[i]);

			if(i < sread - 4)
			{
				if( buff[i] == '\033' && buff[i + 1] == '[' && buff[i+2] =='H')
				{
					usleep(120000);
				}
			}			
		}

	}

	close(fd);

	return 0;
}
