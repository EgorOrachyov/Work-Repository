#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const int TRUE = 1;
const int FALSE = 0;

typedef char * data1;
typedef long data2;


struct _Node {
	data1 key;            // Pointer to buffer string
	data2 value;          // Number of words
	struct _Node * next;  // Pointer to the next list element
};

typedef struct _Node Node;

struct _LinkedList {
	long length;   // Size of list
	Node * head;   // Pointer to the head of the list
	//Node * end;  // Pointer to last list element
};

typedef struct _LinkedList LinkedList;


// Create LinkedList
LinkedList * lCreateLinkedList() {
	LinkedList * list = (LinkedList *)calloc(1, sizeof(LinkedList));
	if (list != NULL) {
		list->length = 0;
		list->head = NULL;
		return list;
	} 
	else {
		return NULL;
	}
}


// Create node
Node * nCreateNode(data1 key, data2 value) {
	Node * node = (Node *)calloc(1, sizeof(Node));
	if (node) {
		node->key = key;
		node->value = value;
		node->next = NULL;
		return node;
	}
	else {
		return NULL;
	}    
}


// Add element in the beginning of list
int addIntoBeginning(LinkedList * list, data1 key, data2 value) {
	Node * node;
	node = nCreateNode(key, value);
	if (node) {
		node->next = list->head;
		list->head = node;
		list->length += 1;
		return TRUE;
	}
	else {
		return FALSE;
	}
}


// Add element is the end of list
int addIntoEnd(LinkedList * list, data1 key, data2 value) {
	Node * node;
	node = nCreateNode(key, value);
	if (node) {
		if (list->head == NULL) { 
			list->head = node;
		}
		else {
			Node * current = list->head;
			for(int i = 1; i < list->length; i++) {
				current = current->next;
			}
			current->next = node;          
		}
		list->length += 1;
		return TRUE;
	}	
	else {
		return FALSE;
	}	
}


// Add element in the list after node prev
int addAfterN(LinkedList * list, Node * prev, data1 key, data2 value) {
	Node * current = list->head;
	Node * node = nCreateNode(key, value);

	if (node) {
		while (current) {
			if (current == prev) {
				Node * tmp = current->next;
				current->next = node;
				node->next = tmp;
				list->length += 1;

				return TRUE;
			}
		}
		return FALSE;
	}
	else {
		return FALSE;
	}
}


// Add element in the list after alement with n = index 
int addAfterI(LinkedList * list, long index, data1 key, data2 value) {
	Node * current = list->head;
	Node * node = nCreateNode(key, value);

	if (node) {
		if (index == -1) {
			Node * tmp = list->head;
			list->head = node;
			node->next = tmp;
		} 
		else {
			long i = 0;
			while (current) {
				if (index == i) {
					Node * tmp = current->next;
					current->next = node;
					node->next = tmp;
					list->length += 1;

					return TRUE;
				}
				
				i += 1;
				current = current->next;
			}
			return FALSE;
		}
	}
	else {
		return FALSE;
	}
}


// Free memory used by Linked List
void freeLinkedList(LinkedList * list) {
	Node * current = list->head;
	Node * tmp;
	
	for(long i = 0; i < list->length; i++) {	
		tmp = current->next;
		free(current);
		current = tmp;
	}
	
	list->head = NULL;
	list->length = 0;
}

// Delete linked list and free its allocated memory
void deleteLinkedList(LinkedList * list) {
	freeLinkedList(list);
	free(list);
}

// Delete elements, which have this value
int deleteElementByValue(LinkedList * list, data1 key) {
	Node * ptr1 = NULL;
	Node * ptr2 = list->head;
	Node * ptr3 = ptr2->next;
	int count = 0;

	while (ptr2) { 
		if (ptr2->key == key) {
			if (ptr1 == NULL) {
				list->head = ptr3;
			} 
			else {
				ptr1->next = ptr3;
			} 

			free(ptr2);
			count += 1;
			list->length -= 1;
			ptr2 = ptr3;
			
			if (ptr3) {
				ptr3 = ptr3->next;
			}
		}
		else {
			ptr1 = ptr2;
			ptr2 = ptr3;

			if (ptr3) {
				ptr3 = ptr3->next;
			}
		}
	}

	return count;
}


// Finds node in list by key
Node * getElementFromList(LinkedList * list, data1 key) {
	Node * node = NULL;
	Node * current = list->head;

	long i = 0;
	while (i < list->length) {
		if (strcmp(current->key, key) == 0) { 
			node = current;
			break;
		}

		i = i + 1;
		current = current->next;
	}

	return node;
} 

int getValueFromList(LinkedList * list, data1 key, data2 * value) {
	int isIn = FALSE;
	Node * current = list->head;

	long i = 0;
	while (i < list->length) {
		if (strcmp(current->key, key) == 0) {
			*value = current->value; 
			isIn = TRUE;
			break;
		}

		i = i + 1;
		current = current->next;
	}

	return isIn;
}


// Print value of each element of linked list
// Actual for looped list
void printLinkedList(LinkedList * list) {
	Node * current = list->head;
	long i = 0;

	while (i < list->length) {
		printf("element[%li]: key = %s; value = %li;\n", i, current->key, current->value);
		current = current->next;		
		i += 1;
	}
}


// Reverse linked list (head is tail and tail is head)
int reverseLinkedList(LinkedList * list) {
	if (list->length == 1) {
		return TRUE;
	}
	else {
		Node * next = list->head->next;
		Node * current = list->head; 
		current->next = NULL;

		while (next) {
			Node * tmp = next;
			next = next->next;
			tmp->next = current;
			current = tmp;
		}

		list->head = current;

		return TRUE;    	
	}
}


// Returns TRUE if list looped else returns FALSE
int isListLooped(LinkedList * list) {
	int isLooped = FALSE;
	
	Node * ptr1 = list->head;
	Node * ptr2 = list->head;

	while (ptr2) {
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;

		if (ptr2) {
			ptr2 = ptr2->next;
		}	

		if (ptr1 == ptr2) {
			isLooped = TRUE;
			break;
		}
	}

	return isLooped;
}


// Create loop in list
int createLoop(LinkedList * list, long index) {
	Node * current = list->head;
	Node * tmp = NULL;
	Node * prev;

	if (!isListLooped(list)) {
		long i = 0;
		while (current) {
			if (i == index) {
				tmp = current;
			}
			i += 1;
			prev = current;
			current = current->next;
		}

		if (tmp == NULL) {
			return FALSE;
		}
		else {
			prev->next = tmp;
			return TRUE;
		}
	}
	else {
		return FALSE;
	}
}

#endif