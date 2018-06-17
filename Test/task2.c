#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long getLong(char * s, int l) {
	long a = 0;
	for(int i = 0; i < l; i++) {
		a = a*2 + (s[i] - '0');
	}
	return a;
}

const int MAXLEN = 256;

int main() {

	char b1[MAXLEN];
	printf("Введите a: \n");
	gets(b1);
	
	char b2[MAXLEN];
	printf("Введите b: \n");
	gets(b2);
	
	long a = getLong(b1, strlen(b1)); 
	long b = getLong(b2, strlen(b2)); 

	if (a > b) {
		printf("a > b \n");
	}
	else if (a < b) {
		printf("a < b \n");
		}
	else {
		printf("a = b \n");
	}

	return 0;
}	