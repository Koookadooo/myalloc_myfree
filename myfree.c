#include "helpers.h"
#include <stdlib.h>
#include <unistd.h>

void myfree(void *ptr) {
    if (ptr == NULL) {
        return;
    }
    // Calculate the address of the block metadata
    struct block *block_ptr = (struct block *)((char *)ptr - padded_block_size);

    // Mark the block as not in use
    block_ptr->in_use = 0;
}