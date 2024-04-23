// htab_hash_function.c
// Solution IJC-DU2, Task B, 22.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include "htab.h"
#include <stdint.h>

// Function that creates hashes
size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // must have 32 bits
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}