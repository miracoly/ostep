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
    pid_t w = wait(NULL);
    printf("child wait() returned %d\n", w); // likely -1
    sleep(1);
    printf("child\n");
  } else {
    // parent
    wait(NULL);
    printf("parent\n");
  }

  return 0;
}
