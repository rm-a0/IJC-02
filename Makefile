# Makefile
# Solution IJC-DU2, Task A, 25.4.2024
# Author: Michal Repčík, FIT
# Compiled: gcc 11.4.0

CC = gcc
CXX = g++
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
CXXFLAGS = -02 -Wall -Wextra -pedantic -std=c++11
LIBS =

HTAB_O = htab_create.o htab_destroy.o htab_erase.o htab_for_each.o htab_search.o htab_hash_function.o htab_statistics.o
TARGETS = tail wordcount wordcount-dynamic libhtab.a libhtab.so

.PHONY: all clean zip cleanzip

all: $(TARGETS)

tail: tail.o
	$(CC) $(CFLAGS) -o $@ $^ 

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o $@ $^  -static

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o $@ $^ 

libhtab.a: $(HTAB_O)
	ar rcs $@ $^

libhtab.so: $(HTAB_O)
	$(CC) $(CFLAGS) -shared -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

%.o: %.cc
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

clean:
	rm -f *.o tail wordcount wordcount-dynamic libhtab.a libhtab.so

zip:
	zip xrepcim00.zip *.c *.h *.cc Makefile

cleanzip:
	rm -f xrepcim00.zip