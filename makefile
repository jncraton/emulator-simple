all: test

processor: processor.c
	gcc -Wall -Wextra $< -o $@

run: processor
	./processor

test: processor
	./processor

clean:
	rm -f ./processor
