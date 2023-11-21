CC=gcc

all: libstr.so

libstr.so: str.c str.h
	$(CC) -fPIC -shared -I. -o $@ $<

prog: program.c str.h
	$(CC) $< -o $@ -I. -L. -lstr -Wl,-rpath=.

clean:
	rm -f prog libstr.so

.PHONY: clean
