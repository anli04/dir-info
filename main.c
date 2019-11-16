#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

int dirFunc(DIR * d, char * path);

int main(){
  DIR * d = opendir("Test");
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  char path[] = "Test/";
  int tsize = dirFunc(d, path);
  closedir(d);
  return 0;
}

int dirFunc(DIR * d, char * path){
  struct dirent *p;
  p = readdir(d);
  long int tsize = 0;
  while (p){
    printf("Name: %s. Type: %d. ", p->d_name, p->d_type);
    struct stat f;
    char s[256];
    strcpy(s, path);
    stat(strcat(s, p->d_name), &f);
    printf("Size: %ld.\n", f.st_size);
    if (p->d_type != 4 && strcmp(p->d_name, ".") != 0) tsize += f.st_size;
    else {
      DIR * d2 = opendir(s);
      tsize += dirFunc(d2, s);
      closedir(d2);
    }
    p = readdir(d);
  }
  return tsize;
}
