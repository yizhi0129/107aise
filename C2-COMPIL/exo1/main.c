#include <stdio.h>
#include <mylib.h>

int main(int argc, char *argv[])
{
	int i = 0;
	char s[10];

	for (i = 0; i < 10; ++i) {


		snprintf(s, 10, "i = %d", i);
		mylib_puts(s);
	}

	printf("nb chars = %lu\n", mylib_nbchars());
	return 0;
}
