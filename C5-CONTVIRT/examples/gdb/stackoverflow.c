#include <stdio.h>

int foo()
{
	char bar[100000];
	foo();
}

int main(int argc, char ** argv)

{	foo();

	return 0;
}
