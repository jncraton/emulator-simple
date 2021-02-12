all: processor

processor: processor.c
	gcc -Wall -Wextra $< -o $@

run: processor
	./processor

clean:
	rm -f ./processor
