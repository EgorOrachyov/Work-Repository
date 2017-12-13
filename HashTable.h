#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <string.h>
#include "LinkedList.h"

// typedef char * data1; Defined in linkedList.h
// typedef long data2;   Defined in linkedList.h

typedef char * string;
typedef void (*iterateType)(data1, data2);
typedef long (*hashType)(data1, int, long);

typedef struct {
	long size;
	long numOfElements;
	LinkedList ** table;
	int simple;
	hashType hash;
} HashTable;

// Allocate memory for table and each linked list
int allocMemoryForTable(HashTable * HT, long size) {
	HT->table = (LinkedList **)calloc(size, sizeof(LinkedList *));
	
	if (HT->table != NULL) {
		for(long i = 0; i < size; i++) {
			HT->table[i] = lCreateLinkedList();
			
			if (HT->table[i] == NULL) {
				return FALSE;
			} 
		}   

		HT->size = size;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// Clear the lists of table
void clearHashTable(HashTable * HT) {
	for(long i = 0; i < HT->size; i++) {
		freeLinkedList(HT->table[i]);
	}
	
	HT->numOfElements = 0;	
}

// Free memory used for Hash Table
void freeHashTable(HashTable * HT) {
	if (HT->size != 0) {
		
		for(long i = 0; i < HT->size; i++) {
			deleteLinkedList(HT->table[i]);
		}
	
		HT->numOfElements = 0;	

		free(HT->table);
		HT->size = 0; 
	}
}

// Delete hash table and free its allocated memory
void deleteHashTable(HashTable * HT) {
	freeHashTable(HT);
	free(HT); 
}


// Create HashTable and returns TRUE if it is ok 
HashTable * createHashTable(long size, hashType hashFunction, int simple, int * isOk) {
	HashTable * HT = (HashTable *)calloc(1, sizeof(HashTable));

	if (HT != NULL) {
		*isOk = allocMemoryForTable(HT, size);

		if (*isOk) {
			HT->hash = hashFunction;
			HT->simple = simple;
			HT->numOfElements = 0; 
		}
	} 

	return HT;
}

// Add element is list and returns TRUE or FALSE if cannot add element
int addElement(HashTable * HT, data1 key, data2 value) {
	long hash = HT->hash(key, HT->simple, HT->size);
	Node * node = getElementFromList(HT->table[hash], key);

	if (node != NULL) { 
		node->value = value;
		return TRUE;
	}  
	else {
		int isOk = addIntoEnd(HT->table[hash], key, value);
		
		if (isOk) {
			HT->numOfElements += 1;
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}

// Iterate by keys and values any input function
void iterateByKeyValue(HashTable * HT, iterateType iterateFunction) {
	for(long i = 0; i < HT->size; i++) {
		Node * current = HT->table[i]->head;

		for(long j = 0; j < HT->table[i]->length; j++) {
			iterateFunction(current->key, current->value);
			current = current->next;
		}
	}
}

// Return TRUE and element value if it is in table or return FALSE
int getElement(HashTable * HT, data1 key, data2 * value) { 
	long hash = HT->hash(key, HT->simple, HT->size);
	data2 result;
	int isIn = getValueFromList(HT->table[hash], key, &result);

	if (isIn) {
		*value = result;
		return TRUE;
	}    
	else {
		*value = 0;
		return FALSE;
	}
}

// Return max length of table's list
long getMaxListLength(HashTable * HT) {
	long max = 0;

	for(long i = 0; i < HT->size; i++) {
		if (HT->table[i]->length > max) {
			max = HT->table[i]->length;
		}
	}

	return max;
}

// Return min length of table's list
long getMinListLength(HashTable * HT) {
	long min = 0;

	if (HT->size > 0) {
		min = HT->numOfElements;

		for(long i = 0; i < HT->size; i++) {
			if ((HT->table[i]->length < min) && (HT->table[i]->length >= 1)) {
				min = HT->table[i]->length;
			}
		}
	}

	return min;
}

// Return num of empty lists
long getNumOfEmptyLists(HashTable * HT) {
	long num = 0;

	for(long i = 0; i < HT->size; i++) {
		if (HT->table[i]->length == 0) {
			num += 1;
		}
	}

	return num;
}

// Return num of not empty lists
long getNumOfNotEmptyLists(HashTable * HT) {
	long num = 0;

	for(long i = 0; i < HT->size; i++) {
		if (HT->table[i]->length != 0) {
			num += 1;
		}
	}

	return num;
}

// Print statistic of Hash Table
void printHashTableStat(HashTable * HT) {
	long numOfKeys = HT->numOfElements;
	long maxListLength = getMaxListLength(HT);
	long minListLength = getMinListLength(HT);
	long numOfEmptyLists = getNumOfEmptyLists(HT);
	long numOfNotEmptyLists = getNumOfNotEmptyLists(HT);
	double averageListLength = (double)HT->numOfElements / (double)numOfNotEmptyLists;

	printf("Size: %li \n", HT->size);
	printf("Num of keys: %li \n", numOfKeys);
	printf("Num of empty lists: %li \n", numOfEmptyLists);
	printf("Num of not empty lists: %li \n", numOfNotEmptyLists);
	printf("Max list length: %li \n", maxListLength);
	printf("Min list length: %li \n", minListLength);
	printf("Average list length: %lf \n", averageListLength);
}

#endif