#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAXLEN = 256;

int main() {

	char b1[MAXLEN];
	printf("first: \n");
	gets(b1);
	
	char b2[MAXLEN];
	printf("second: \n");
	gets(b2);

	int len1 = strlen(b1);
	int len2 = strlen(b2);


	if (len1 > len2) {
		printf("1 больше чем 2 \n");
	}
	else if (len2 > len1) {
		printf("2 больше чем 1 \n");
	}
	else {
		int i = 0;
		char delta = 0; 
		while ((delta == 0) && (i < len1)) {
			delta = b1[i] - b2[i];
			i += 1;	
		}

		if (delta == 0) {
			printf("1 равно 2 \n");
		}
		else if (delta > 0) {
			printf("1 больше чем 2 \n");
		}
		else {
			printf("2 больше чем 1 \n");
		}
	}

	return 0;
}