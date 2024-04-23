// tail.c
// Solution IJC-DU2, Task A, 29.3.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 2047
#define DEFAULT_LEN 10

typedef struct c_buf {
    char **buffer;
    unsigned size;
    unsigned head;
    unsigned tail;
} c_buf_t;

// Function that allocates memory for buffer inside c_buf
void c_buf_create(c_buf_t *c_buf, unsigned length) {
    // Alocate memory for buffer
    c_buf->buffer = (char**)malloc(length*sizeof(char*));

    if (c_buf->buffer == NULL) {
        fprintf(stderr, "Memory allocation for buffer failed\n");
        exit(EXIT_FAILURE);
    }
    // Alocate memory for buffer cells
    for (unsigned i = 0; i < length; i++) {
        // Allocate one extra space for /0
        c_buf->buffer[i] = (char*)malloc((MAX_LINE_LEN + 1)*sizeof(char));

        if (c_buf->buffer[i] == NULL) {
            fprintf(stderr, "Memory allocation for line %u failed\n", i);
            for (unsigned j = 0; j < i; j++) {
                free(c_buf->buffer[j]);
            }
            free(c_buf->buffer);
            exit(EXIT_FAILURE);
        }
        // Initialize buffer with \0 for printf compatibility
        memset(c_buf->buffer[i], '\0', MAX_LINE_LEN);
    }

    c_buf->size = length;
    c_buf->head = 0;
    c_buf->tail = 0;
}

// Function that frees allocated memory for c_buf
void c_buf_free(c_buf_t *c_buf) {
    for (unsigned i = 0; i < c_buf->size; i++) {
        if (c_buf->buffer[i] != NULL) {
            free(c_buf->buffer[i]);
        }
    }
    free(c_buf->buffer);
}

// Function that adds line to the buffer
void c_buf_put(c_buf_t *c_buf, char *line) {
    strcpy(c_buf->buffer[c_buf->head], line);
    // Increment head and create circular behavior
    c_buf->head = (c_buf->head + 1) % c_buf->size;
}

// Function that returns line from the buffer
char* c_buf_get(c_buf_t *c_buf) {
    if (c_buf->head == c_buf->tail) {
        printf("Buffer is empty\n");
        return NULL;
    }
    
    char *line = c_buf->buffer[c_buf->tail];
    c_buf->tail = (c_buf->tail + 1) % c_buf->size;

    return line;
}

// Function that fills c_buf with an input
void c_buf_fill(c_buf_t *c_buf, FILE *fp) {
    int c;
    unsigned i = 0;
    char line[MAX_LINE_LEN];

    while ((c = fgetc(fp)) != EOF) {
        // Leave space for \n at the end
        if (i < MAX_LINE_LEN) {
            line[i] = (char)c;
        }
        else if (i == MAX_LINE_LEN) {
            fprintf(stderr, "Maximum line length exceeded\n");
            line[i] = '\n';
        }
        i++;

        if (c == '\n') {
            c_buf_put(c_buf, line);
            memset(line, 0, sizeof(line));
            i = 0;
        }
    }

    // Process last line
    if (i > 0) {
        c_buf_put(c_buf, line);
    }
}

// Function that prints last lines from file
void c_buf_print(c_buf_t *c_buf) {
    unsigned index = c_buf->head;

    for (unsigned i = 0; i < c_buf->size; i++) {
        printf("%s", c_buf->buffer[index]);
        index = (index + 1) % c_buf->size;
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

    c_buf_t c_buf;
    c_buf_create(&c_buf, length);
    c_buf_fill(&c_buf, fp);
    c_buf_print(&c_buf);
    c_buf_free(&c_buf);

    fclose(fp);
    return 0;
}