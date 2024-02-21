// helpers.h
#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

struct block {
    int size;
    int in_use;
    struct block *next;
};

extern struct block *head;
extern int padded_block_size;

void initialize_heap();
void split_block(struct block *current, int size);
void print_data(void);

#endif // HELPERS_H