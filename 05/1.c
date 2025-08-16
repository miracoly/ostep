#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child
    x = 1;
    printf("x in child: %d\n", x);
  } else {
    // parent
    x = 2;
    printf("x in parent: %d\n", x);
  }
  return 0;
}
