// wordcount.c
// Solution IJC-DU2, Task B, 25.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"
#include "io.h"

#define HTAB_SIZE 28657 // prime number close to power of 2 is ideal
#define MAX_LEN 255

// Function that prints word from hash table and number of its occurences
void htab_print(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

// Function that returns pointer to file or stdin
FILE* parse_args(int argc, char *argv[]) {
    FILE *fp = NULL;

    if (argc > 2) {
        fprintf(stderr, "Only one argument supported\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 1) {
        fp = stdin;
    }
    else if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "Error reading from a file\n");
            exit(EXIT_FAILURE);
        }
    }

    return fp;
}

// Main function
int main(int argc, char *argv[]) {
    // Create file pointer
    FILE *fp;
    fp = parse_args(argc, argv);

    // Create hash table
    htab_t* htab = htab_init(HTAB_SIZE);
    if (htab == NULL) {
        fprintf(stderr, "Memory allocation for hash table failed.\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    // Create buffer to read data into
    char buffer[MAX_LEN];

    // Append items to the hash table from fp
    while (read_word(buffer, MAX_LEN, fp) != EOF) {
        htab_pair_t *htab_pair = htab_lookup_add(htab, buffer);
        if (htab_pair == NULL) {
            fprintf(stderr, "Memory allocation for hash table item failed.\n");
            htab_free(htab);
            fclose(fp);
            return EXIT_FAILURE;
        }
        ++htab_pair->value;
    }

    // Print info about every item
    htab_for_each(htab, htab_print);

    // Display statistics
    #ifdef STATISTCIS
        htab_statistics(htab);
    #endif // STATISTICS

    // Free alocated memory
    htab_free(htab);
    fclose(fp);
    return 0;
}