# Add additional compiler flags here
CFLAGS=-O2 -Wall -Wextra -Wpedantic -g -std=c11

all: bf
brainfuck: bf.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f bf

