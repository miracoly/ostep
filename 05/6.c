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
    sleep(1);
    printf("child\n");
  } else {
    // parent
    waitpid(rc, NULL, 0);
    printf("parent\n");
  }

  return 0;
}
