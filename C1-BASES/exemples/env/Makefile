all: argc envp

argc: argc.c
	gcc $^ -o $@

envp: envp.c
	gcc $^ -o $@

clean: 
	rm -f argc envp

.PHONY: clean