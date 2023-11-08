#include <stdio.h>

unsigned long int nbchars = 0;
int mylib_puts(const char* str)
{
	int delta = puts(str);
	nbchars += (unsigned long int)delta;
	return delta;
}

unsigned long int mylib_nbchars()
{
	return nbchars;
}
