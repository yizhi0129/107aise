#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
	char v[] = "toto";
	int i = 2;

	printf("v = %s (%p) &i = %p /  malloc'd = %p\n", v, v, &i, malloc(strlen(v)));
	return 0;
}
