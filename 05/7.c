#include "sys/wait.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int rc = fork();
  if (rc < 0) {
    // error
    perror("fork");
    exit(1);
  } else if (rc == 0) {
    // child
    if (close(STDOUT_FILENO)) {
      perror("close stdout");
      exit(1);
    };
    int r = printf("child\n");
    printf("r: %d\n", r);
    if (r) {
      perror("printing in child");
    }
    if (fflush(stdout) == EOF) {
      perror("flushing");
    };
    sleep(1);
    _exit(0);
  } else {
    // parent
    waitpid(rc, NULL, 0);
    printf("parent\n");
  }

  return 0;
}
