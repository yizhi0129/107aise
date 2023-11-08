CC=gcc

all: mylib/libcustom.so mylib/libcustom.a

static: mylib/libcustom.a

dynamic: mylib/libcustom.so

mylib/libcustom.a: mylib/code.c
	gcc -c $<
	ar rcs $@ code.o

mylib/libcustom.so: mylib/code.c
	gcc -shared -fPIC -o $@ $<

program_dynamic: main.c
	#gcc -o $@ $< -I./mylib -L./mylib -lcustom
	#LD_LIBRARY_PATH=./mylib ./a.out
	#OU:
	gcc -o $@ $< -I./mylib -L./mylib -lcustom -Wl,-rpath=./mylib
	./a.out


program_static: main.c
	gcc -static -o $@ $< -I./mylib -L./mylib -lcustom
	./a.out

clean:
	rm -f mylib/*.so mylib/*.a mylib/*.o *.o

.PHONY: clean

