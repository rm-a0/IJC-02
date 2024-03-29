# Makefile
# Solution IJC-DU2, Task A, 29.3.2024
# Author: Michal Repčík, FIT
# Compiled: gcc 11.4.0

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

TARGETS = tail

.PHONY: all run clean zip

all: $(TARGETS)

tail: tail.o 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGETS) *.o

zip:
	zip xrepcim00.zip *.c *.h Makefile
