#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
 if (argc < 2) {
  printf("No arguement.\n");
  exit(1);
 }
 if (argc > 2) {
  printf("Too many arguements.\n");
 }
 char *p = argv[1];
 int flag = 1;
 while (*p) {
  if (*p < '0' || *p > '9') {
   flag = 0;
   break;
  }
  p++;
 }
 if (flag == 0) {
  printf("Error arguement.\n");
  exit(1);
 }

 uint time = atoi(argv[1]);
 sleep(time);

 exit(0);
}
