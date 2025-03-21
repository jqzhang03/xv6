#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
 char *p[MAXARG]; //char *p[32]
 int i;
 for (i = 1; i < argc; i++) {
  p[i - 1] = argv[i];
 }
 p[argc - 1] = malloc(512);
 p[argc] = '\0';
 while (gets(p[argc - 1], 512)) {
  if (strlen(p[argc - 1]) == 0) {
   break;
  }
  if (p[argc - 1][strlen(p[argc - 1]) - 1] == '\n') {
   p[argc - 1][strlen(p[argc - 1]) - 1] = '\0';
  }
  if (fork() == 0) {
   exec(argv[1], p);
  } else {
   wait(0);
  }
 }

 exit(0);
}
