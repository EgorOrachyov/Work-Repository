#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAXLEN = 256;

int main() {

	char name[MAXLEN];
	printf("Введите имя файла: \n");
	gets(name);

	FILE * file = fopen(name, "r");
	if (!file) {
		printf("Cannot open file");
		exit(1);
	}

    char s[MAXLEN];
    char res[MAXLEN];

    strcpy(res, "");

    fgets(s, MAXLEN, file);
	while (!feof(file)) {
		int i = 0;
		while (i < strlen(s) - 1) {
			if ((s[i] == '/') && (s[i + 1] == '/')) {

                
				strcat(res, &s[i]);
				printf("%s", res); 
				strcpy(res, "");
				break;
			}

			i += 1;
		}
		
		fgets(s, MAXLEN, file);
	}

	fclose(file);

	return 0;
}