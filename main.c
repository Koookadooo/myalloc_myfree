#include "functions.h"
#include <stdio.h>

int main() {

  void *p;
  void *q;

  print_data();
  p = myalloc(128);
  print_data();
  printf("%p\n", p);
  q = myalloc(16);
  print_data();
  printf("%p\n", q);

}