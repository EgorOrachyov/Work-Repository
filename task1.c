#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAXLEN = 256;

int main() {

	char c;
	char string[MAXLEN];
  
	printf("Строка: \n");
	gets(string);
	printf("Символ: \n");
	c = getchar();

	int i = 0;
	int len = strlen(string);
	while (i < len) {
		if (string[i] == c) {
			
			int j = i;
			while (j < len + 1) {
				string[j] = string[j + 1];
				j += 1;
			}
		}
		i += 1;	
	}

	printf("%s\n", string);

	return 0;
}