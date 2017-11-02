#ifndef _LINKEDLIST_H_
  #define _LINKEDLIST_H_

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

const int TRUE = 1;
const int FALSE = 0;

typedef int data;


struct _Node {
	data value;    // Data value
	struct _Node * next;   // Pointer to the next list element
};

typedef struct _Node Node;

struct _LinkedList {
	long length; // Size of list
	Node * head;   // Pointer to the head of the list
	//Node * end;  // Pointer to last list element
};

typedef struct _LinkedList LinkedList;


// Undefined behaviour, avoid using
// Create LinkedList
int iCreateLinkedList(LinkedList * list) {
	list = (LinkedList *)calloc(1, sizeof(LinkedList));
	if (list != NULL) {
		list->length = 0;
		return TRUE;
	} 
	else {
		return FALSE;
	}
}


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


// Undefined behaviour , avoid using
// Create node and get error message
int iCreateNode(Node * node, data value) {
	node = (Node *)calloc(1, sizeof(Node));
	if (node != NULL) {
		node->value = value;
		node->next = NULL;
		return TRUE;
	}
	else {
		return FALSE;
	}
}


// Create node
Node * nCreateNode(data value) {
	Node * node = (Node *)calloc(1, sizeof(Node));
	if (node) {
		node->value = value;
		node->next = NULL;
		return node;
	}
	else {
		return NULL;
	}    
}


// Add element in the beginning of list
int addIntoBeginning(LinkedList * list, data value) {
	Node * node;
	node = nCreateNode(value);
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
int addIntoEnd(LinkedList * list, data value) {
	Node * node;
	node = nCreateNode(value); 
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
int addAfterN(LinkedList * list, Node * prev, data value) {
	Node * current = list->head;
	Node * node = nCreateNode(value);

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
int addAfterI(LinkedList * list, long index, data value) {
	Node * current = list->head;
	Node * node = nCreateNode(value);

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
    
	for(int i = 0; i < list->length; i++) {	
		tmp = current->next;
		free(current);
		current = tmp;
		i += 1;
	}
	list->head = NULL;
	list->length = 0;
}


// Delete elements, which have this value
int deleteElementByValue(LinkedList * list, data value) {
	Node * ptr1 = NULL;
	Node * ptr2 = list->head;
	Node * ptr3 = ptr2->next;
	int count = 0;

	while (ptr2) { 
		if (ptr2->value == value) {
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


// Print value of each element of linked list
// Actual for looped list
void printLinkedList(LinkedList * list) {
	Node * current = list->head;
	long i = 0;

	while (i < list->length) {
		printf("element[%li]->value = %i \n", i, current->value);
		current = current->next;		
		i += 1;
	}
}

#endif