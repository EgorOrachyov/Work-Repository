#include <stdio.h>

// return max of a and b
int max(int a, int b) {
	return (a > b? a : b);
}

// return length of string
int strlen(char * s) {
	int i = 0; 
	while (s[i] != '\0') {
		i++;
	}
	return i;
}

// copy string source to string destination
void strcpy(char * dst, char * src) {	
	int i = 0;
	while (src[i] != '\0') {
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
}

// concatenation of strings destination and source
void strcat(char * dst, char * src) {
	int i = 0;
	while (dst[i] != '\0') {
		i++;
	}
	
	int j = 0;
	while (src[j] != '\0') {    	
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = src[j];

}

// comparison of strings s1 and s1: return 0 - are equal, <0 - first is smaller, >0 - first is bigger
int strcmp(char * s1, char * s2) {
	int i = 0;
	while ((s1[i] - s2[i] == 0) && (s1[i] != '\0') && (s2[i] != '\0')) {
	  i++;
	}
	return s1[i] - s2[i];
}

int main() {
   
	/*

	char s1[] = "abcd";
	char s2[] = "abcde";
	char s3[] = " hhhhh";
	char s4[] = "abcde";


	printf("%i \n", strlen(s1));

	strcpy(s2, s1);
	printf("%s \n", s2);

	strcat(s2, s3);
	printf("%s \n", s2);

	printf("%i \n", strcmp(s1, s4));

	*/
	
	return 0;
}