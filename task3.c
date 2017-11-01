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

	while (!feof(file)) {
		fgets(s, MAXLEN, file);
        
        // Если убрать этот if, то он выведет
        // последнюю строку комментария 2 раза ???
		if (feof(file)) {
			break;
		}

		int i = 0;
		while (i < strlen(s) - 1) {
			if ((s[i] == '/') && (s[i + 1] == '/')) {

                strcpy(res, "");
				strcat(res, &s[i]);
				printf("%s", res); 
				break;
			}

			i += 1;
		}
	}

	fclose(file);

	return 0;
}