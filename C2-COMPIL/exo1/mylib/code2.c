#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long int nbchars = 0;
int mylib_puts(const char* str)
{
    char* cpy = strdup(str);
    int delta = 0;
    int i = 0;
    size_t len = strlen(str);
    for (i = 0; i < len; ++ i)
    {
        cpy[strlen(str) - 1 - i] = str[i];
    }

    delta = puts(cpy);
    nbchars += (unsigned long int)delta;
    free(cpy);

    return delta;
}


unsigned long int mylib_nbchars()
{
    return nbchars;
}




