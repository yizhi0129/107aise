#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{

	int * tab = malloc(10* sizeof(int));

	tab[11]= 10;

	return 0;
}
