#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sortAlgorithms.h"


int main() {

	const data min = 0;
	const data max = 1000; 
	const long MaxDataSet = 100000000;

	long dataSetsSize = 9;
	long dataSets[] = {5 , 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

	printf("Speed of sorting algoritms \n");

	double startTime;
	double currTime;

	srand(time(NULL));
	data * value;
	data * mass;

	value = (data *)calloc(MaxDataSet, sizeof(data));
	if (value == NULL) {
		printf("Error: cannot allocate memory for value \n");
		exit(1);
	}

	mass = (data *)calloc(MaxDataSet, sizeof(data));
	if (mass == NULL) {
		printf("Error: cannot allocate memory for mass \n");
		exit(1);
	}

	for(int i = 0; i < MaxDataSet; i++) {
		value[i] = rand() % (max + 1); 
	}

	printf("CountSort:\n");
	for(int k = 0; k < dataSetsSize; k++) {
		long size = dataSets[k];

		for(int i = 0; i < size; i++) {
			mass[i] = value[i];
		}

		startTime = (double)clock();
		countSort(mass, size, min, max);
		currTime = ((double)clock() - startTime) / CLOCKS_PER_SEC;

		printf("%li: %lf \n", size, currTime);
	}

	printf("QuickSort:\n");
	for(int k = 0; k < dataSetsSize; k++) {
		long size = dataSets[k];

		for(int i = 0; i < size; i++) {
			mass[i] = value[i];
		}

		startTime = (double)clock();
		quickSort(mass, 0, size - 1);
		currTime = ((double)clock() - startTime) / CLOCKS_PER_SEC;

		printf("%li: %lf \n", size, currTime);
	}

	printf("MergeSort:\n");
	for(int k = 0; k < dataSetsSize; k++) {
		long size = dataSets[k];

		for(int i = 0; i < size; i++) {
			mass[i] = value[i];
		}

		startTime = (double)clock();
		mergeSort(mass, size);
		currTime = ((double)clock() - startTime) / CLOCKS_PER_SEC;

		printf("%li: %lf \n", size, currTime);
	}
	
	printf("BubleSort:\n");
	for(int k = 0; k < dataSetsSize; k++) {
		long size = dataSets[k];

		for(int i = 0; i < size; i++) {
			mass[i] = value[i];
		}

		startTime = (double)clock();
		bubleSort(mass, size);
		currTime = ((double)clock() - startTime) / CLOCKS_PER_SEC;

		printf("%li: %lf \n", size, currTime);
	}    

	free(value);
	free(mass);

	return 0;
}
