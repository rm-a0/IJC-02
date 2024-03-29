// tail.c
// Solution IJC-DU2, Task A, 28.3.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 2047
#define DEFAULT_LEN 10

typedef struct {
    char **buffer;
    unsigned size;
    unsigned head;
    unsigned tail;
} CBuf;

// Function that allocates memory for buffer inside CBuf
void cbuf_create(CBuf *cbuf, unsigned length) {
    // Alocate memory for buffer
    cbuf->buffer = (char**)malloc(length*sizeof(char*));

    if (cbuf->buffer == NULL) {
        fprintf(stderr, "Memory allocation for buffer failed\n");
        exit(EXIT_FAILURE);
    }
    // Alocate memory for buffer cells
    for (unsigned i = 0; i < length; i++) {
        cbuf->buffer[i] = (char*)malloc(MAX_LINE_LEN*sizeof(char));

        if (cbuf->buffer[i] == NULL) {
            fprintf(stderr, "Memory allocation for line %u failed\n", i);
            for (unsigned j = 0; j < i; j++) {
                free(cbuf->buffer[j]);
            }
            free(cbuf->buffer);
            exit(EXIT_FAILURE);
        }
        // Initialize buffer with \0 for printf compatibility
        memset(cbuf->buffer[i], '\0', MAX_LINE_LEN);
    }

    cbuf->size = length;
    cbuf->head = 0;
    cbuf->tail = 0;
}

// Function that frees allocated memory for CBuf
void cbuf_free(CBuf *cbuf) {
    for (unsigned i = 0; i < cbuf->size; i++) {
        if (cbuf->buffer[i] != NULL) {
            free(cbuf->buffer[i]);
        }
    }
    free(cbuf->buffer);
}

// Function that adds line to the buffer
void cbuf_put(CBuf *cbuf, char *line) {
    strcpy(cbuf->buffer[cbuf->head], line);
    // Increment head and create circular behavior
    cbuf->head = (cbuf->head + 1) % cbuf->size;
}

// Function that returns line from the buffer
char* cbuf_get(CBuf *cbuf) {
    if (cbuf->head == cbuf->tail) {
        printf("Buffer is empty\n");
        return NULL;
    }
    
    char *line = cbuf->buffer[cbuf->tail];
    cbuf->tail = (cbuf->tail + 1) % cbuf->size;

    return line;
}

// Function that fills CBuf with an input
void cbuf_fill(CBuf *cbuf, FILE *fp) {
    int c;
    unsigned i = 0;
    char line[MAX_LINE_LEN];

    while ((c = fgetc(fp)) != EOF) {
        // Leave space for \0 at the end
        if (i < MAX_LINE_LEN) {
            line[i] = (char)c;
        }
        else if (i == MAX_LINE_LEN) {
            fprintf(stderr, "Maximum line length exceeded\n");
        }
        i++;

        if (c == '\n') {
            cbuf_put(cbuf, line);
            memset(line, 0, sizeof(line));
            i = 0;
        }
    }

    // Process last line
    if (i > 0) {
        cbuf_put(cbuf, line);
    }
}

// Function that prints last lines from file
void cbuf_print(CBuf *cbuf) {
    unsigned index = cbuf->head;

    for (unsigned i = 0; i < cbuf->size; i++) {
        printf("%s", cbuf->buffer[index]);
        index = (index + 1) % cbuf->size;
    }
}

// Function that processes command line arguments and returns pointer to a file or stdin
FILE* process_arguments(int argc, char *argv[], unsigned *lenght) {
    FILE *fp = NULL;

    if (argc > 4) {
        fprintf(stderr, "Maximum of 3 arguments supported\n");
        exit(EXIT_FAILURE);
    }

    // Handle -n switch
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        if (argc > 2) {
            if (atoi(argv[2]) <= 0) {
                fprintf(stderr, "Line length must be a number greater than 0\n");
                exit(EXIT_FAILURE);
            }
            *lenght = atoi(argv[2]);
        }
        else {
            fprintf(stderr, "After '-n' an argument is expected\n");
            exit(EXIT_FAILURE);
        }
    }
    
    // Handle pointer to file/stdin
    if (argc == 2 || argc == 4) {
        fp = fopen(argv[argc - 1], "r");
        if (fp == NULL) {
            fprintf(stderr, "Failed to read from the file\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 1 || argc == 3) {
        fp = stdin;
    }
    else {
        fprintf(stderr, "Unexpected error occured while parsing arguments\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

// Main function
int main(int argc, char *argv[]) {
    unsigned length = DEFAULT_LEN;
    FILE *fp;
    
    fp = process_arguments(argc, argv, &length);

    CBuf cbuf;
    cbuf_create(&cbuf, length);
    cbuf_fill(&cbuf, fp);
    cbuf_print(&cbuf);
    cbuf_free(&cbuf);

    fclose(fp);
    return 0;
}