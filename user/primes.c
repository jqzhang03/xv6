#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void calc_primes(int p[2]) {
 close(p[1]);
 int num;
 if (read(p[0], &num, 4) == 0) {
  close(p[0]);
  exit(0);
 }
 printf("prime %d\n", num);
 int pp[2];
 pipe(pp);
 int pid = fork();
 if (pid == 0) {
  calc_primes(pp);
 } else if (pid > 0) {
  int m;
  while (read(p[0], &m, 4)) {
   if (m % num != 0) {
    write(pp[1], &m, 4);
   }
  }
  close(p[0]);
  close(pp[0]);
  close(pp[1]);
  wait(0);
 } else {
  printf("Something went wrong!");
  close(p[0]);
  close(pp[1]);
  close(pp[0]);
  exit(1);
 }
 exit(0);
}

int main(){
 int p[2], i;
 pipe(p);

 for (i = 2; i <= 35; i++) {
  write(p[1], &i, 4);
 }
 
 calc_primes(p);

 exit(0);
}
