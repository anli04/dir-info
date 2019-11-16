#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

int main(){
  DIR * d = opendir("Test");
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  struct dirent *f;
  f = readdir(d);
  while (f){
    printf("Name: %s.Type: %d. ", f->d_name, f->d_type);
    struct stat s;
    stat(f->d_name, &s);
    printf("Size: %ld.\n", s.st_size);
    f = readdir(d);
  }
  closedir(d);
  return 0;
}
