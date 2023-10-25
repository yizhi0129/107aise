#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main( int argc, char ** argv)
{
	if(argc != 2)
	{
		return 1;
	}

	char * file = argv[1];

	int fd = open(file, O_CREAT | O_RDWR);

	close(fd);

	return 0;
}
