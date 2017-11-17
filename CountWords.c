#include "HashFunctions.h"
#include "HashTable.h"
#include <string.h>
#include <time.h>

const long KByte = 1024;
const long MByte = 1024 * 1024;
const long GByte = 1024 * 1024 * 1024;

int simple = 17;
long size;

long getHash(char * string) {
	return getHash2(string, simple, size);
}

data1 mostPopularWord;
data2 mostPopularWordCount;

void getMostCommonWord(data1 key, data2 value) {
	if (value > mostPopularWordCount) {
		mostPopularWordCount = value;
		mostPopularWord = key;
	}
}

void printTable(data1 key, data2 value) {
	printf("Key: %s  Value: %li \n", key, value);
}

int main() {

	char fileName[KByte];
	printf("Enter file name to count words: \n");
	gets(fileName);

	size = 200000;

	double startTime;
	double currTime;

	int isOk;
	HashTable * HT = createHashTable(size, getHash, &isOk);
	if ((HT == NULL) || (isOk == 0)) {
		printf("Error: cannnot create Hash Table \n");
		exit(1);
	} 

	FILE * file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Error: cannot open file");
		exit(1);
	}	

	char * buffer = (char *)calloc(MByte, sizeof(char));
	if (buffer == NULL) {
		printf("Error: cannot allocate memory for buffer");
		exit(1);
	}

	char * string = (char *)calloc(KByte, sizeof(char));
	if (string == NULL) {
		printf("Error: cannot allocate memory for string");
		exit(1);
	}  

	data1 key;
	data2 value;

	buffer[0] = '\0';
	long currentPos = 0;
	char deltaCase = 'a' - 'A';

	startTime = (double)clock();
	
	while (!feof(file)) {
		fgets(string, KByte, file);


		long i = 0;
		char last = '\0';

		while (string[i] != '\0') {
			if ((string[i] >= 'a') && (string[i] <= 'z')) {
				buffer[currentPos] = string[i];

				if (last == '\0') {
					key = &buffer[currentPos];
					last = '#';
				}

				currentPos += 1;
			} 
			else if ((string[i] >= 'A') && (string[i] <= 'Z')) {
				buffer[currentPos] = string[i] + deltaCase;

				if (last == '\0') {
					key = &buffer[currentPos];
					last = '#';
				}

				currentPos += 1;
			} 
			else if (last == '#') {
				buffer[currentPos] = '\0';
				currentPos += 1;
				last = '\0';

				isOk = getElement(HT, key, &value);
				value += 1;
				addElement(HT, key, value);
			} 

			i++;
		}
	}

	currTime = ((double)clock() - startTime) / CLOCKS_PER_SEC;

	printf("------ Hash table element ------ \n");
	iterateByKeyValue(HT, printTable);
	printf("------- Most common word ------- \n");
	mostPopularWordCount = 0;
	iterateByKeyValue(HT, getMostCommonWord);
	printf("word: %s used: %li \n", mostPopularWord, mostPopularWordCount);
	printf("----- Hash Table Statistic ----- \n");
	printHashTableStat(HT);
	printf("Used time: %lf \n", currTime);
	printf("-------------------------------- \n");

	deleteHashTable(HT);
	fclose(file);
	free(buffer);
	free(string);
 
	return 0;
}