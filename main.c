#include "functions.h"
#include <stdio.h>

int main() {
    void *pointers[3] = {NULL}; // Initialize an array to store pointers
    int values[3] = {10, 20, 30}; // Values to assign to allocated memory

    for (int i = 0; i < 3; i++) {
        pointers[i] = myalloc(sizeof(int)); // Allocate memory using myalloc
        print_data(); // Print the memory status after each allocation
        if (pointers[i] != NULL) {
            *(int *)pointers[i] = values[i]; // Assign value to allocated memory
            printf("Pointer %c holds the value %d\n", 'p' + i, *(int *)pointers[i]);
        } else {
            printf("Memory allocation failed for pointer %c\n", 'p' + i);
        }
    }

    return 0;
}