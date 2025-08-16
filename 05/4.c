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
    printf("child\n");
    char *args[] = {"ls", "-la", NULL};
    if (execvp(args[0], args)) {
      perror("exec ls");
      exit(1);
    };
  } else {
    // parent
    wait(NULL);
    printf("parent\n");
  }

  return 0;
}
