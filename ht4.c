#include <stdio.h>

// return max of a and b
int max(int a, int b) {
	return (a > b? a : b);
}

// return length of string
int strlen(char *s) {
  int i = 0; 
  while (s[i] != '\0') {
	i++;
  }
  return i;
}

// copy string source to string destination
void strcpy(char *dst, char *src) {
	int length = strlen(src);
	
	for(int i = 0; i < length + 1; i++){
		dst[i] = src[i];
	}
}

// concatenation of strings destination and source
void strcat(char *dst, char *src) {
	int dstLen = strlen(dst); 
	int srcLen = strlen(src); 

	for (int i = 0; i < srcLen + 1; i++) {
		dst[dstLen + i] = src[i];
	}
}

// comparison of strings s1 and s1: return 0 - are equal, <0 - first is smaller, >0 - first is bigger
int strcmp(char *s1, char *s2) {
	int i = 0;
	int length = max(strlen(s1), strlen(s2));
 
	while ((s1[i] - s2[i] == 0) && (i < length)) {
	  i++;
	}
	return s1[i] - s2[i];
}

int main() {

	return 0;
}