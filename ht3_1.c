#include<stdio.h>

union {
  int i;
  char c[sizeof(int)];
 } myU;

int main() {
  
  myU.i = 0;
  myU.c[sizeof(int)-1] = 1;
  
  printf("Endiannes: %s \n",(char *)(myU.c[sizeof(int)-1] == myU.i ? "Big-Endian" : "Little-Endian"));

  return 0;
}
