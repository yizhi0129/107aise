#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{

	int * tab = malloc(10* sizeof(int));

	#pragma omp parallel
	{
		while(1)
		{}
	}

	return 0;
}
