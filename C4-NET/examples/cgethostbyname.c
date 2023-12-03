#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	struct hostent * host = gethostbyname(argv[1]);

	if(!host)
	{
		herror("gethostbyname");
		return 1;
	}

	int sock = socket(AF_INET, SOCK_STREAM, 0); 
	//a system call that creates an endpoint for communication and returns a socket descriptor : an intiger identifier
	//int socket(int domain, int type, int protocol);

	if(sock < 0)
	{
		perror("socket");
		return 0;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in)); //set the memory of the server structure to zero
	server.sin_family = host->h_addrtype; //The h_addrtype field indicates the address family
	server.sin_port = htons(atoi(argv[2])); 
	//atoi() : Converts the port number provided as a command-line argument (argv[2]) from a string to an integer.
	//htons() : Converts the integer port number to network byte order (big-endian)

	//to bind a socket to a specific address and port

	memcpy(&server.sin_addr, host->h_addr_list[0], host->h_length);
	// where to copy, what to copy, how much to copy (bytes)

	int ret = connect(sock, (struct sockaddr*)&server, sizeof(struct sockaddr_in));
	//connect() : initiate a connection on a socket
	//sock : endpoint of communication
	// pointer that contains the address and port information of the server
	//size of the socket address structure

	if( ret < 0) //connect atempt unsuccessful
	{
		perror("connect");
		return 0;
	}

	char toto[128];

	snprintf(toto, 128, "COUCOU TOI\n"); 
	//This function ensures that the string is truncated if it exceeds the specified size (128 in this case).

	write(sock, toto, strlen(toto));

	while((ret = read(sock, toto, 128)) != 0)
	{
		write(STDOUT_FILENO, toto, ret); //loop terminates when read() returns 0
	}

	close(sock);

	return 0;
}
