#define _GNU_SOURCE

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(void) {
  const int iterations = 10000;
  struct timeval before;
  struct timeval after;
  struct timeval diff;

  int fd = open("/dev/null", O_RDONLY);
  if (fd == -1) {
    err(EXIT_FAILURE, "opening file");
  }

  gettimeofday(&before, NULL);
  char buf;
  for (int i = iterations; i; i--) {
    if (read(fd, &buf, 0) != 0) {
      err(EXIT_FAILURE, "reading");
    }
  }
  gettimeofday(&after, NULL);

  if (close(fd) != 0) {
    err(EXIT_FAILURE, "closing file");
  };

  timersub(&after, &before, &diff);
  long long total_ns =
      (long long)diff.tv_sec * 1000000000LL + (long long)diff.tv_usec * 1000LL;
  long long ns = (total_ns + iterations / 2) / iterations;
  printf("nanosec: %lld", ns);

  return 0;
}
