#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int fd = open("tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (write(fd, "before\n", 7) != 7) {
    perror("write before");
    exit(1);
  }

  int rc = fork();
  if (rc < 0) {
    // error
    perror("fork");
    exit(1);
  } else if (rc == 0) {
    // child
    if (write(fd, "child\n", 6) != 6) {
      perror("write child");
      exit(1);
    };
  } else {
    // parent
    if (write(fd, "parent\n", 7) != 7) {
      perror("write parent");
      exit(1);
    }
  }

  close(fd);
  return 0;
}
