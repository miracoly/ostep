#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    err(EXIT_FAILURE, "pipe");
  }

  int rc1 = fork();
  if (rc1 < 0) {
    // error
    perror("fork");
    exit(1);
  }

  /* child 1 */
  if (rc1 == 0) {
    if (close(pipefd[0]) == -1) {
      err(EXIT_FAILURE, "close read end");
    }
    char *msg = "Hi from child 1";
    int len = strlen(msg);
    if (write(pipefd[1], msg, len) != len) {
      err(EXIT_FAILURE, "write child 1");
    }
    if (close(pipefd[1]) == -1) {
      err(EXIT_FAILURE, "close write end");
    }
    _exit(EXIT_SUCCESS);
  }

  int rc2 = fork();
  if (rc2 < 0) {
    // error
    perror("fork");
    exit(1);
  }

  /* child 2 */
  if (rc2 == 0) {
    // close write end
    if (close(pipefd[1]) == -1) {
      err(EXIT_FAILURE, "close write end");
    }
    sleep(1);

    char buf;
    while (read(pipefd[0], &buf, 1) > 0) {
      if (write(STDOUT_FILENO, &buf, 1) != 1) {
        err(EXIT_FAILURE, "write child 2");
      }
    }
    if (write(STDOUT_FILENO, "\n", 1) != 1) {
      err(EXIT_FAILURE, "write \\n child 2");
    }
    if (close(pipefd[0]) == -1) {
      err(EXIT_FAILURE, "close child 2");
    }
    _exit(EXIT_SUCCESS);
  }

  /* parent */
  if (close(pipefd[0]) == -1) {
    err(EXIT_FAILURE, "close read parent");
  }
  if (close(pipefd[1]) == -1) {
    err(EXIT_FAILURE, "close write parent");
  }
  if (waitpid(rc1, NULL, 0) == -1) {
    err(EXIT_FAILURE, "wait");
  }
  if (waitpid(rc2, NULL, 0) == -1) {
    err(EXIT_FAILURE, "wait");
  }
  return EXIT_SUCCESS;
}
