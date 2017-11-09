#ifndef _SORTALGORITHMS_H_
#define _SORTALGORITHMS_H_

const int TRUE = 1;
const int FALSE = 0;

typedef int data;

void swap(data * a, data * b);
void countSort(data * a, long size, data min, data max);
void quickSort(data * a, long left, long right);
void bubleSort(data * a, long size);


void swap(data * a, data * b) {
	data c = *a;
	*a = *b;
	*b = c;
}

void countSort(data * a, long size, data min, data max) {
	long numOfElements = max - min + 1;
	data * count = (data *)calloc(numOfElements, sizeof(data));
	
	for(long i = 0; i < size; i++) {
		count[a[i] - min] += 1; 
	}

	long k = 0;
	for(long i = 0; i < numOfElements; i++) {
		for(long j = 0; j < count[i]; j++) {
			a[k] = i + min;
			k += 1;
		}
	}

	free(count);
}

void quickSort(data * a, long left, long right) {
	if (right - left > 0) {
		data centre = a[(left + right) / 2];
		long i = left;
		long j = right;
		while (i <= j) {
			while (a[i] < centre) {
				i += 1;
			}
			while (a[j] > centre) {
				j -= 1;
			}
			if (i <= j) {
				swap(&a[i], &a[j]);
				i += 1;
				j -= 1;
			}
		}
		quickSort(a, left, j);
		quickSort(a, i, right);
	} 
}

void bubleSort(data * a, long size) { 
	long flag = FALSE; 
	long i = 0;
	while (!flag) {
		flag = TRUE;
		for(long j = 0; j < size - (i + 1); j++) {
			if (a[j] > a[j+1]) {
				swap(&a[j], &a[j+1]);
				flag = FALSE;
			}
		}
		i += 1;
	}
}

#endif  

