#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main( int argc, char **argv )
{
	struct addrinfo *res = NULL; //pointer to a linked list of addrinfo structures
	struct addrinfo hints;
	memset( &hints, 0, sizeof( hints ) ); //set the memory of the hints structure to zero
	hints.ai_family = AF_INET; // IPv4 addresses
	hints.ai_socktype = SOCK_STREAM; //socket type
	int ret = getaddrinfo( argv[1], argv[2], //host name and service name
	                       &hints,
	                       &res );

	if ( ret < 0 )
	{
		if(errno == EAI_SYSTEM)
		{
			perror("getaddrinfo"); //system error
		}
		else
		{
			herror( "getaddrinfo" ); //a specific error related to address resolution
		}
		return 1;
	}

	struct addrinfo *tmp;

	for ( tmp = res; tmp != NULL; tmp = tmp->ai_next )
	{
		char ip[INET6_ADDRSTRLEN];
		ip[0] = '\0'; //initialized as empty string

		if ( tmp->ai_family == AF_INET ) //IPv4 address
		{
			struct sockaddr_in *saddr = ( struct sockaddr_in * )tmp->ai_addr;
			//It casts the generic ai_addr member of the address structure (tmp->ai_addr) to a more specific type (struct sockaddr_in*)
			inet_ntop( AF_INET, &saddr->sin_addr, ip, sizeof( ip ) ); 
			//This function converts the binary representation of the address to a human-readable string and stores it in the ip array.
			printf( "IPV4 : %s %d %d %d\n", ip, tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol );
		}
		else if ( tmp->ai_family == AF_INET6 ) //IPv6 address
		{
			struct sockaddr_in6 *saddr6 = ( struct sockaddr_in6 * )tmp->ai_addr;
			inet_ntop( AF_INET6, &saddr6->sin6_addr, ip, sizeof( ip ) );
			printf( "IPV6 : %s\n", ip );
		}
	}

	return 0;
}
