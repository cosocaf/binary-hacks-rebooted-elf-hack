#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {
  FILE* fp = fopen("/proc/self/maps", "r");
  if (!fp) {
    fprintf(stderr, "fopen: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  unsigned char buf[4096];
  size_t n;
  while ((n = fread(buf, 1, sizeof buf, fp)) > 0) {
    size_t written = fwrite(buf, 1, n, stdout);
    if (written != n) {
      fprintf(stderr, "fwrite: %s\n", strerror(errno));
      fclose(fp);
      return EXIT_FAILURE;
    }
  }

  if (ferror(fp)) {
    fprintf(stderr, "fread: %s\n", strerror(errno));
    fclose(fp);
    return EXIT_FAILURE;
  }

  fclose(fp);
  return EXIT_SUCCESS;
}

