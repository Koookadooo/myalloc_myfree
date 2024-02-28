#ifndef functions_h
#define functions_h

#include <stdlib.h>
#include "helpers.h"

// Function prototypes
void *myalloc(int size);
void myfree(void *ptr);
void coalesce(struct block *head);
void print_data(void);

#endif // functions_h