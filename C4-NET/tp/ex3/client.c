#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv)
{
	if(argc < 3)
	{
		fprintf(stderr, "USAGE: %s [HOST] [PORT]\n", argv[0]);
		return 1;
	}


	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;


	struct addrinfo *ret = NULL;

	if(getaddrinfo(argv[1], argv[2], &hints, &ret) < 0 )
	{
		perror("getaddrinfo");
		return 1;
	}

	struct addrinfo *tmp = NULL;

	int sock = -1;
	int success = 0;

	for(tmp = ret; tmp != NULL; tmp = tmp->ai_next)
	{
		sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);

		if(sock < 0)
		{
			continue;
		}

		if(connect( sock, tmp->ai_addr,  tmp->ai_addrlen) < 0 )
		{
			continue;
		}

		success = 1;
		break;
	}

	/* Connected ? */
	if(!success)
	{
		fprintf(stderr, "Pas connecté\n");
		return 1;
	}
	else
	{
		printf("Connected to %s:%s\n", argv[1], argv[2]);
	}


	char * data = "Coucou\n";


	FILE * fsock =fdopen(sock, "w+");

	if(fsock == NULL)
	{
		perror("fdopen");
		return 1;
	}

	fprintf(fsock, "GET / HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.74.0\nAccept: */*\n\n");

	char buff[1024];

	while(fgets(buff, 1024, fsock))
	{
		printf("%s", buff);
	}


	fclose(fsock);

	return 0;
}
