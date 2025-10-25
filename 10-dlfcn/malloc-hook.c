#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

static void* (*real_malloc)(size_t) = NULL;

void* malloc(size_t size) {
  if (real_malloc == NULL) {
    real_malloc = dlsym(RTLD_NEXT, "malloc");

    if (real_malloc == NULL) {
      fprintf(stderr, "dlsym error: %s\n", dlerror());
      exit(1);
    }
  }

  fprintf(stderr, "malloc: size=%zu\n", size);

  return real_malloc(size);
}
