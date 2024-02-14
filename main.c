#include "functions.h"
#include <stdio.h>

int main() {

  void *p;
  void *q;

  print_data();
  p = myalloc(1009);
  print_data();
  q = myalloc(16);
  print_data();
  
  if (p != NULL) {
    *(int *)p = 10;
    printf("p holds the value %d", *(int *)p);
  }
  else if (q != NULL) {
    *(int *)q = 20;
    printf("q holds the value %d\n", *(int *)q);
  }
  else {
    printf("Both allocations failed\n");
  }

  return 0;

}