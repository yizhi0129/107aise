CC=gcc

all: libinterp.so program.exe

libinterp.so: interp.c
	gcc -shared -fPIC -o $@ $<

program.exe: main.c
	gcc $< -lm -o $@
	./$@

interp: program.exe libinterp.so
	LD_PRELOAD=./libinterp.so ./program.exe


clean:
	rm -f *.exe *.so

.PHONY: clean interp

