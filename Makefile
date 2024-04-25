CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

all: tail

tail: tail.c
	$(CC) $(CFLAGS) -o tail tail.c

clean:
	rm -f tail