#define _GNU_SOURCE 1
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>



void* (*realmalloc)(size_t) = NULL;
size_t total  = 0;
size_t cnt = 0;

__attribute__((destructor))
void fini()
{
	printf("total alloc size: %llu bytes\n", total);
	printf("nb alloc size: %llu\n", cnt);
}


void *malloc(size_t size)
{
	void* pointer = NULL;
	char tmp[100];
	int final_size;


	if(!realmalloc)
	{
		realmalloc = dlsym(RTLD_NEXT, "malloc");
		if(!realmalloc)
		{
			abort();
		}
	}
	
	pointer = realmalloc(size);
	total += size;
	cnt++;

	
	final_size = snprintf(tmp, 100, "addr = %p (%llu)\n", pointer, size);
	write(1, tmp, strlen(tmp));
	//printf("addr = %p (%llu)\n", pointer, size);
	return pointer;
}
