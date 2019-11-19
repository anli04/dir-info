#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

long int dirFunc(DIR * d, char * path);
void printSize(long int size);

int main(int argc, char * argv[]){
  printf("Note: \"Readable format\" truncates the bytes when converting\n\n");
  DIR * d;
  char name[256];
  if (argc == 1){
    name[0] = '\0';
    while (!name[0]){
      printf("Enter a directory name (max 254 chars)\n");
      fgets(name, sizeof(name) - 1, stdin);
      if (name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = '\0';
      d = opendir(name);
      if (errno){
        printf("Error: %d - %s\n", errno, strerror(errno));
        name[0] = '\0';
      }
    }
  }
  else {
    strcpy(name, argv[1]);
    d = opendir(name);
    if (errno){
      printf("Error: %d - %s\n", errno, strerror(errno));
      name[0] = '\0';
    }
    while (!name[0]){
      printf("Enter a directory name (max 254 chars)\n");
      fgets(name, sizeof(name) - 1, stdin);
      if (name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = '\0';
      d = opendir(name);
      if (errno){
        printf("Error: %d - %s\n", errno, strerror(errno));
        name[0] = '\0';
      }
    }
  }
  printf("Statistics for directory %s\n", name);
  strcat(name, "/");
  long int tsize = dirFunc(d, name);
  closedir(d);
  printf("\nTotal Size (not including directories): ");
  printSize(tsize);
  return 0;
}

long int dirFunc(DIR * d, char * path){
  struct dirent *p;
  p = readdir(d);
  if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
  long int tsize = 0;
  while (p){
    printf("Name: %-30s | ", p->d_name);
    if (p->d_type == 4) printf("Type: %-20s | ", "directory");
    else printf("Type: %-20s | ", "regular file");
    struct stat f;
    char s[256];
    strcpy(s, path);
    strcat(s, p->d_name);
    stat(s, &f);
    if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
    printf("Size: ");
    printSize(f.st_size);
    if (p->d_type != 4) tsize += f.st_size;
    else if (strncmp(p->d_name, ".", 1) != 0) {
      DIR * d2 = opendir(s);
      if (errno) printf("Error: %d - %s\n", errno, strerror(errno));
      strcat(s, "/");
      tsize += dirFunc(d2, s);
      closedir(d2);
    }
    p = readdir(d);
  }
  return tsize;
}

void printSize(long int size){
  if (size > 1000000000000) printf("%ld TB\n", size / 1000000000000);
  else if (size > 1000000000) printf("%ld GB\n", size / 1000000000);
  else if (size > 1000000) printf("%ld MB\n", size / 1000000);
  else if (size > 1000) printf("%ld KB\n", size / 1000);
  else printf("%ld B\n",size);
}
