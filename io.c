// io.c
// Solution IJC-DU2, Task B, 23.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <ctype.h>
#include "io.h"

#define MAX_LEN 255

// Function that reads word from a file and returns its length
int read_word(char *s, int max, FILE *f) {
    if (max > MAX_LEN) {
        fprintf(stderr, "Length of the word is out of the limit");
        max = MAX_LEN;
    }

    int c;
    int len = 0;

    // Skip spaces
    while ((c = fgetc(f)) != EOF && isspace(c));

    // Read characters
    while(c != EOF && len < max) {
        s[len] = c;
        len++;
        c = fgetc(f);
        if (isspace(c)) {
            break;
        }
    }

    if (c == EOF) {
        return c;
    }

    // Discard remaining characters
    if (len == max) {
        while (c != EOF && !isspace(c)) {
            c = fgetc(f);
        }
    }

    s[len] = '\0';

    return len;
}