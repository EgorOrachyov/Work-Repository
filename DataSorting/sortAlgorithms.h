#ifndef _SORTALGORITHMS_H_
#define _SORTALGORITHMS_H_

const int TRUE = 1;
const int FALSE = 0;
const int SPLITTING = 6; // used in merge sort

typedef int data;

// Sort algorithms
void countSort(data * a, long size, data min, data max);
void quickSort(data * a, long left, long right);
void bubleSort(data * a, long size);
void mergeSort(data * a, long size);

// Help-functions
void swap(data * a, data * b);
void mergeMass(data * a, int size_a, data * b, int size_b, data * res);


void swap(data * a, data * b) {
	data c = *a;
	*a = *b;
	*b = c;
}

void countSort(data * a, long size, data min, data max) {
	long numOfElements = max - min + 1;

	data * count = (data *)calloc(size, sizeof(data));
	if (count == NULL) {
		printf("Error: cannot allocate memory for count (countSort) \n");
		exit(1);
	}

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

void mergeMass(data * a, int size_a, data * b, int size_b, data * res) {
	int i = 0;
	int j = 0;
	int m = 0;

	while ((i < size_a) && (j < size_b)) {
		if (a[i] < b[j]) {
			res[m] = a[i];
			i++;
		}
		else {
			res[m] = b[j];
			j++;
		}
		m++;
	}

	if (i >= size_a) {
		while (j < size_b) {
			res[m] = b[j];
			j++;
			m++;
		}
	}
	else {
		while (i < size_a) {
			res[m] = a[i];
			i++;
			m++;
		}
	}
}

void mergeSort(data * a, long size) {
	if (size > 0) {
		if (size < SPLITTING) {
			bubleSort(a, size);
		}
		else {
			long size_left = size / 2;
			long size_right = size - size_left;

			mergeSort(&a[0], size_left);
			mergeSort(&a[size_left], size_right);

			data * tmp = (data *)calloc(size, sizeof(data));
			if (tmp == NULL) {
				printf("Error: cannot allocate memory for tmp(mergeSort) \n");
				exit(1);
			}

			mergeMass(&a[0], size_left, &a[size_left], size_right, tmp);

			for(long i = 0; i < size; i++) {
				a[i] = tmp[i];
			}

			free(tmp);
		}
	}
}

#endif  

