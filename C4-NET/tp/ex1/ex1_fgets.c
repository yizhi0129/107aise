#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	FILE *in = fopen("./starwars.txt", "r");

	if(!in)
	{
		perror("fopen");
		return 1;
	}

	char buff[1024];


	while(fgets(buff, 1024, in))
	{

		printf("%s", buff);

		if(strstr(buff, "\033[H"))
		{
			usleep(70000);
		}

	}

	fclose(in);

	return 0;
}
