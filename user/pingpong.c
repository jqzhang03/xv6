#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
 int p[2];
 pipe(p);
 int child = fork();
 if (child == 0) {
  read(p[0], &child, 1);
  printf("%d: received ping\n", getpid());
 } else {
  write(p[1], &child, 1);
  wait(0);
  printf("%d: received pong\n", getpid());
 }

 exit(0);
}
