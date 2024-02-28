#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

struct block *head = NULL;
int padded_block_size = PADDED_SIZE(sizeof(struct block));

//function to initialize the heap
void initialize_heap() {
    void *heap = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
    head = (struct block *)heap;
    head->size = 1024 - padded_block_size;
    head->in_use = 0;
    head->next = NULL;
}

// Function to split a block if necessary
void split_block(struct block *current, int size) {
    struct block *new_block = (struct block *)((char *)current + sizeof(struct block) + size);
    new_block->size = current->size - size - sizeof(struct block);
    new_block->in_use = 0;
    new_block->next = current->next;

    current->size = size;
    current->in_use = 1;
    current->next = new_block;
}

// Function to coalesce free blocks
void coalesce(struct block *head) {
    struct block *current = head;
    struct block *next = current->next;
    while (next != NULL) {
        if (current->in_use == 0 && next->in_use == 0) {
            // merge the sizes of the two blocks
            current->size += next->size + padded_block_size; // Include the size of the block structure itself in the merge
            current->next = next->next;
            next = current->next;
        } else {
            current = next;
            next = next->next;
        }
    }
}

// Print the data regarding allocated and free blocks
void print_data(void) {
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }
    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        printf("[%d, %s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }
        b = b->next;
    }
    printf("\n");
}