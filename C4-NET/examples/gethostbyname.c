#include <netdb.h> //definitions for network database operations, such as gethostbyname
#include <stdio.h>
#include <sys/socket.h> //socket-related functions
#include <netinet/in.h> //contains structures for internet protocol operations
#include <arpa/inet.h> //functions for manipulating internet addresses


int main(int argc, char **argv)
{
	if(argc < 2) //at least one command-line argument (the host name) is required
		return 1; //exit with error

	struct hostent *ret = gethostbyname(argv[1]); //host name : command-line argument 1
//returns a pointer to a hostent structure, which contains information about the host
//if the host is not found, NULL is returned
	if(!ret)
	{
		herror("gethostbyname"); 
		return 1; //error
	}


	printf("Host resolves to %s\n", ret->h_name);

	unsigned int i=0;
	while ( ret->h_addr_list[i] != NULL) { // iterate through the list of IP addresses
		printf( "%s\n", inet_ntoa( *( struct in_addr*)( ret->h_addr_list[i]))); 
		//inet_ntoa : convert an IPv4 address from binary to a string
		i++;
	}


	return 0;
}
