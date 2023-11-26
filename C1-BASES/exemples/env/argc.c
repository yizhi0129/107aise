#include <stdio.h>

int main(int argc, char * argv[])
{ //conditional compilation block
#if 0
	int i;
	for(i = 0 ; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
#else
	while(*argv)
	{
		printf("%s\n", *argv);
		argv++;
	} //The loop prints each argument using printf and then increments the argv pointer to move to the next argument. 
	//The loop continues until it encounters a null pointer (*argv evaluates to false).
#endif
	return 0;
}
