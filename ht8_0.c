#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sortAlgorithms.h"

typedef struct {
	double t;
	data * a;
} DataSet;

int main() {

	const data min = 0;
	const data max = 1000; 
	const long MaxDataSet = 100000000;

	long numOfDataSets = 3;
	long dataSetsSize = 9;
	long dataSets[] = {5 , 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

	DataSet dataSet[numOfDataSets];
	
	for(int i = 0; i < numOfDataSets; i++) {
		dataSet[i].a = (data*)calloc(MaxDataSet, sizeof(data));
		if (dataSet[i].a == NULL) {
			printf("Error: cannot allocate memory for dataSet \n");
			exit(1);
		}
	}

	printf("Speed of sorting algoritms \n");

	double startTime;
	srand(time(NULL));
	data * value;

	value = (data *)calloc(MaxDataSet, sizeof(data));
	if (value == NULL) {
		printf("Error: cannot allocate memory for dataSet \n");
		exit(1);
	}

	for(int i = 0; i < MaxDataSet; i++) {
		value[i] = rand() % (max + 1); 
	}

	printf("CountSort:\n");
	for(int k = 0; k < dataSetsSize; k++) {
		long size = dataSets[k];

		for(int i = 0; i < size; i++) {
			dataSet[0].a[i] = value[i];
		}

		startTime = (double)clock();
		countSort(dataSet[0].a, size, min, max);
		dataSet[0].t = ((double)clock() - startTime) / CLOCKS_PER_SEC;

		printf("%li: %lf \n", size, dataSet[0].t);
	}

	printf("QuickSort:\n");
	for(int k = 0; k < dataSetsSize; k++) {
		long size = dataSets[k];

		for(int i = 0; i < size; i++) {
			dataSet[0].a[i] = value[i];
		}

		startTime = (double)clock();
		quickSort(dataSet[1].a, 0, size-1);
		dataSet[1].t = ((double)clock() - startTime) / CLOCKS_PER_SEC;

		printf("%li: %lf \n", size, dataSet[1].t);
	}
	
	printf("BoubleSort:\n");
	for(int k = 0; k < dataSetsSize; k++) {
		long size = dataSets[k];

		for(int i = 0; i < size; i++) {
			dataSet[2].a[i] = value[i];
		}

		startTime = (double)clock();
		bubleSort(dataSet[2].a, size);
		dataSet[2].t = ((double)clock() - startTime) / CLOCKS_PER_SEC;

		printf("%li: %lf \n", size, dataSet[2].t);
	}    

	free(value);
	for(int i = 0; i < numOfDataSets; i++) {
		free(dataSet[i].a);   	
	}

	return 0;
}
