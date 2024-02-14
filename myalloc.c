#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

// define the struct block
struct block {
  int size;
  int in_use;
  struct block *next;
};

// define global variables
struct block *head = NULL;
int padded_block_size = PADDED_SIZE(sizeof(struct block));


void *myalloc(int size) {
  // flag to check if the heap is initialized
  static int initialized = 0;

  // check if the heap is initialized
  if (!initialized) {
    // Initialize the heap
    void *heap = mmap(NULL, 1024, PROT_READ|PROT_WRITE,
              MAP_ANON|MAP_PRIVATE, -1, 0); 

    // Initialize the head of the list
    head = heap;
    head->size = 1024 - padded_block_size;
    head->in_use = 0;
    head->next = NULL;

    initialized = 1;
  };

  // Find a free block and allocate the memory
  struct block *current = head;
  while (current != NULL) {
    if (current->in_use == 0 && current->size >= size) {
      // Calculate the pointer to the allocated memory
      int *ptr = PTR_OFFSET(current, padded_block_size);
      // Mark the block as in use
      current->in_use = 1;
      // Split the block if it's larger than the requested size
      if (current->size > size + padded_block_size) {
        struct block *new_block = PTR_OFFSET(ptr, size);
        new_block->size = current->size - size - padded_block_size;
        new_block->in_use = 0;
        new_block->next = current->next;
        current->next = new_block;
      }
      return ptr;
    }
    current = current->next;
  }
    return NULL;
}


void print_data(void) {
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}
