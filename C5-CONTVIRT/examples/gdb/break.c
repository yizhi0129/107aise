#include <stdio.h>

int foo(int * a)
{
	*a = *a + 1;
	return *a;
}



int main(int argc, char ** argv)
{
	int a;
	int * pint = &a;

	*pint = 10;
	
	foo(pint);

	printf("%d\n", *pint);


	return 0;
}
