#include "functions.h"
#include "helpers.h"
#include <stdio.h>

int main() {

    void *p;

    myalloc(10);     print_data();
    p = myalloc(20); print_data();
    myalloc(30);     print_data();
    myfree(p);       print_data();
    myalloc(40);     print_data();
    myalloc(10);     print_data();

    return 0;
}