#include <stdio.h>

void foo_1() {
  printf("foo_1\n");
}

void foo_2() {
  printf("foo_2\n");
}

void foo(void) __attribute__((ifunc("resolve_foo")));

void* resolve_foo() {
  printf("resolve_foo\n");

  if (false) {
    return foo_1;
  } else {
    return foo_2;
  }
}

int main() {
  foo();
  return 0;
}

