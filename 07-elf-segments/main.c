#include <stdio.h>

int global_var = 0xaaaa;
const int const_global_var = 0xbbbb;
thread_local int thread_local_var = 0xcccc;
thread_local const int const_thread_local_var = 0xdddd;

int main() {
  puts("hello, world!\n");
  return 0;
}
