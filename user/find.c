#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char *get_filename(char *path) {
 char *p;
 for (p = path + strlen(path); p >= path && *p != '/'; p--);
 p++;
 return p;
}

void find(char *path, char *str) {
 char buf[512];
 struct dirent de;
 struct stat st;
 int fd = open(path, 0);
 if (fd < 0) {
  fprintf(2, "find: cannot open %s\n", path);
  return;
 }

 if (fstat(fd, &st) < 0) {
  fprintf(2, "find: cannot stat %s\n", path);
  close(fd);
  return;
 }
 
 switch(st.type) {
  case 2:
   if (strcmp(str, get_filename(path)) == 0) {
    printf("%s\n", path, str);
   }
   break;
  case 1:
   if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
    printf("find:path too long\n");
    break;
   }

   strcpy(buf, path);
   char *p = buf + strlen(buf);
   *p = '/';
   p++;
   while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0) {
     continue;
    }
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    if (stat(buf, &st) < 0) {
     printf("find:cannot stat %s\n", buf);
     continue;
    }
    if (st.type == 2 || st.type == 3) {
     if (strcmp(str, get_filename(buf)) == 0) {
      printf("%s\n", buf);
     }
    } else if (st.type == 1 && strcmp(".", get_filename(buf)) != 0 && strcmp("..", get_filename(buf)) != 0) {
     find(buf, str);
    }
   }

   break;
 }


 close(fd);
 return;
}


int main(int argc, char *argv[]) {
 if (argc == 3) {
  find(argv[1], argv[2]);
 } else {
  printf("Please input valid params\n");
  exit(1);
 }

 exit(0);
}
