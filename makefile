all: test

emulator: src/emulator.c src/emulator.h
	gcc -Wall -Wextra -Werror $< -o $@

run: emulator
	./emulator

test: emulator 
	./emulator

clean:
	rm -f emulator
