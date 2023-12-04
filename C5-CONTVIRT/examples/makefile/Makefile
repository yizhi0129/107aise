CC=gcc


all: main

main: t.c libtoto.so
	$(CC) t.c -o $@ -ltoto 	-L. -Wl,-rpath=$(PWD) 

libtoto.so: lib.c
	$(CC) -shared -fpic $^ -o $@
