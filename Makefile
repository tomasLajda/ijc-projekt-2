# Author: Tomáš Lajda <xlajdat00>
# Date: 2024-04-25
# Description: Makefile for tail and wordcount program

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -fPIC
MODULES = htab_hash_function.c htab_init.c htab_lookup_add.c htab_clear.c htab_free.c htab_erase.c htab_bucket_count.c htab_find.c  htab_size.c htab_for_each.c htab_statistics.c io.c
TARGET = tail wordcount wordcount-dynamic libhtab.a libhtab.so
OBJS = $(MODULES:.c=.o) wordcount.o

all: $(TARGET)

wordcount: wordcount.o libhtab.a
	$(CC) $(CFLAGS) -static -o $@ wordcount.o -L. -lhtab

wordcount-dynamic: wordcount.o libhtab.so
	$(CC) $(CFLAGS) -o $@ wordcount.o -L. -lhtab

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libhtab.a: $(OBJS)
	ar rcs $@ $^
	ranlib $@

libhtab.so: $(MODULES)
	$(CC) $(CFLAGS) -shared -o $@ $^

tail: tail.c
	$(CC) $(CFLAGS) -o $@ tail.c

clean:
	rm -f *.o $(TARGET)

zip:
	zip xlajdat00.zip *.c *.h Makefile