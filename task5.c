#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXLEN = 256;

int main() {

    char **data = NULL;

    char name[MAXLEN];
    printf("Введите имя файла: \n");
    gets(name);
    
    FILE * file = fopen(name, "r");
    if (file == NULL) {
        printf("Error: cannot open the file\n");
        exit(1);
    }

    int n = 0;
    char **value;
    while (!feof(file)) {
        value = (char**)realloc(data, (n+1)*sizeof(char*));
        if (value == NULL) {
            printf("Error: cannot realloc memory \n");
            exit(1);
        } 
        else {    
            data = value;
        }    
        data[n] = (char*)calloc(MAXLEN, sizeof(char));
        fgets(data[n], MAXLEN, file);
        n += 1;
    }

    fclose(file);

    int cmp;
    char * individual = "#";
    for(int i = 0; i < n; i++) {
        cmp = 0;
        for(int j = 0; j < n; j++) {
            if (i != j) {
                cmp = strcmp(data[i], data[j]);
                if (!cmp) {
                    break;
                } 
            }
        }
        if (cmp) {
            individual = data[i];;
            break;
        }
    }

    printf("%s", individual);
     
    for(int i = 0; i < n; i++) {
        free(data[i]);}
    free(data);
  
    return 0;
}