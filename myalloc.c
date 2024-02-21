#include "functions.h"
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

void *myalloc(int size) {
  // flag to check if the heap is initialized
  static int initialized = 0;
  extern struct block *head;
  extern int padded_block_size;

  // pad the size
  size = PADDED_SIZE(size);

  // check if the heap is initialized
  if (!initialized) {
    // Initialize the heap
    initialize_heap();
    initialized = 1;
  };

  // Find a free block and allocate the memory
  struct block *current = head;
  while (current != NULL) {
    if (current->in_use == 0 && current->size >= size) {
      // Calculate the pointer to the allocated memory
      int *ptr = PTR_OFFSET(current, padded_block_size);
      // Mark the block as in use
      if (current->size == size || current->size < size + padded_block_size + ALIGNMENT){
        current->in_use = 1;
      }
      // Split the block if it's larger than the requested size
      else {
        split_block(current, size);
      }
      return ptr;
    }
    current = current->next;
  }
    printf("No available memory\n");
    return NULL;
}
