#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <elf.h>



int main(int argc, char *argv[])
{
	int fd = open("./program", O_RDONLY, 0400);
	if(fd < 0)
	{
		perror("open");
		abort();
	}

	struct stat stat;
	if(fstat(fd, &stat) < 0)
	{
		perror("fstat");
		abort();
	}

	void* start = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED | MAP_FILE, fd, 0);
	if(start == MAP_FAILED)
	{
		perror("mmap");
		abort();
	}

	printf("'%x' '%c' '%c' '%c'\n", *((char*)start), *((char*)start + 1), *((char*)start +2), *((char*)start + 3));

	Elf64_Ehdr* hdr = (Elf64_Ehdr*)start;
	Elf64_Shdr* sec = (Elf64_Shdr*)((char*) start + hdr->e_shoff);
	int i;
	Elf64_Sym* symbol_table;
	char* string_table;
	size_t count;

	for (i = 0; i < hdr->e_shnum; ++i) {
		if(sec[i].sh_type == SHT_SYMTAB)
		{
			symbol_table = (Elf64_Sym*)((char*)start + sec[i].sh_offset);
			count = sec[i].sh_size / sec[i].sh_entsize;
			string_table = (char*)start + sec[sec[i].sh_link].sh_offset;
		}
	}

	for (i = 0; i < count; ++i) {
		printf("%d: %s\n", i, (char*)string_table + symbol_table[i].st_name);
		
	}





	close(fd);
	return 0;
}
