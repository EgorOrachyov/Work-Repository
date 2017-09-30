#include<stdio.h>
#include<stdlib.h>

union {
  int i;
  char c[4];
} myU;

/*
  big-endian: c[0] , c[1], c[2], c[3] ~ i
  little-endian: c[3], c[2], c[1], c[0] ~ i
*/

int main() {
  
  myU.i = 0;
  myU.c[3] = 1;
  
  printf("Endiannes: %s \n",(char *)(myU.c[3] == myU.i ? "Big-Endian" : "Little-Endian"));

  return 0;
}
