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
  struct dirent *p;
  p = readdir(d);
  while (p){
    printf("Name: %s. Type: %d. ", p->d_name, p->d_type);
    struct stat f;
    char s[] = "Test/";
    stat(strcat(s, p->d_name), &f);
    printf("Size: %ld.\n", f.st_size);
    p = readdir(d);
  }
  closedir(d);
  return 0;
}
/*
int main(){
  DIR * d = opendir("directory1");
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  struct dirent *p = readdir(d);
  while (p){
    struct stat f;
    char s[256];
    sprintf(s, "directory1/%s", p->d_name);
    stat(s, &f);
    printf("File name: %s. Type: %d. Size: %ld\n", p->d_name, p->d_type, f.st_size);
    p = readdir(d);
  }
  closedir(d);
  return 0;
}
*/
