CC=gcc

all: mylib/libcustom.so mylib/libcustom2.so

mylib/libcustom.so: mylib/code.c
	gcc -shared -fPIC -o $@ $<

mylib/libcustom2.so: mylib/code2.c
	gcc -shared -fPIC -o $@ $<

program_dynamic: main.c mylib/libcustom.so mylib/libcustom2.so
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

