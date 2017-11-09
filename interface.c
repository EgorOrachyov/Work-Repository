#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

const int NUMBEROFCOMMANDS = 12; 

// Options for user interface
const int CREATE = 0;
const int PRINT = 1;
const int LENGTH = 2;
const int ADDBEGINNING = 3;
const int ADDEND = 4;
const int ADDAFTER = 5;
const int REMOVE = 6;
const int FREE = 7;
const int REVERSE = 8;
const int CREATELOOP = 9;
const int ISLOOPED = 10;
const int END = 11;


int main() {

	int isListCreated = FALSE;
	LinkedList * list;

	int isDone = FALSE;
	while (!isDone) {

		printf("=============== Linked List =============== \n");
		printf("Options: \n");
		printf("0. Create \n");
		printf("1. Print \n");
		printf("2. Length \n");
		printf("3. Add in the beginning \n");
		printf("4. Add in the end \n");
		printf("5. Add after \n");
		printf("6. Remove with value \n");
		printf("7. Free \n");
		printf("8. Reverese \n");
		printf("9. Create Loop \n");
		printf("10. Is looped \n");        
		printf("11. End \n");
		
		int command;
		int isCorrect = FALSE;
		while (!isCorrect) {
			printf("Enter number of command: \n");
			int x = scanf("%i", &command);

			if (x) {
				if ((command >= 0) && (command < NUMBEROFCOMMANDS)) {
					isCorrect = TRUE;
				}
			}
		}

		printf("=========================================== \n");

		if (command == CREATE) {
			if (!isListCreated) {
				list = lCreateLinkedList();

				if (!list) {
					printf("Error: cannot create linkedList \n");
					exit(1);
				}  
				else {
					isListCreated = TRUE;
					printf("List has been created \n");
				}
			}
			else {
				printf("List has been already created \n");
			}
		}
		else if (command == END) {
			printf("Exit the application \n");
			isDone = TRUE;
		}
		else if (isListCreated) {

			if (command == PRINT) {
				printLinkedList(list);
			}
			else if (command == LENGTH) {
				printf("List length = %li \n", list->length);
			}
			else if (command == ADDBEGINNING) {
				data value;
				isCorrect = FALSE;

				while (!isCorrect) {
					printf("Enter value of new element \n");
					int x = scanf("%i", &value);

					if (x) {
					   int ok = addIntoBeginning(list, value);
					   if (ok) {
							printf("Element has been added \n");
					   }
					   else {
							printf("Element hasn't been added \n");
					   }
					   isCorrect = TRUE;
					}
				}
			}            
			else if (command == ADDEND) {
				data value;
				isCorrect = FALSE;

				if (!isListLooped(list)) {
					while (!isCorrect) {
						printf("Enter value of new element \n");
						int x = scanf("%i", &value);

						if (x) {
							int ok = addIntoEnd(list, value);
							if (ok) {
								printf("Element had been added \n");
							}
							else {
								printf("Element hasn't been added \n");
							}
							isCorrect = TRUE;
						}
					}
				}
				else {
					printf("You couldn't add elements into end \n");
				}
			}
			else if (command == ADDAFTER) {
				data value;
				long index;
				isCorrect = FALSE;

				while (!isCorrect) {
					printf("Enter value of new element and index to put after \n");
					int x = scanf("%i %li", &value, &index);

					if (x == 2) {
						int ok = addAfterI(list, index, value);
						if (ok) {
							printf("Element has been added \n");
						}
						else {
							printf("Element hasn't been added \n");
						}
						isCorrect = TRUE;
					}
				}
			}    
			else if (command == REMOVE) {
				data value;
				isCorrect = FALSE;

				if (!isListLooped(list)) {
					while (!isCorrect) {
						printf("Enter value to find and remove elements by this value: \n");
						int x = scanf("%i", &value);

						if (x) {
							int count = deleteElementByValue(list, value);
							printf("Were elements deleted: %i \n", count);
							isCorrect = TRUE;
						}
					}
				}
				else {
					printf("You couldn't remove elements \n");
				}
			}
			else if (command == FREE) {
				freeLinkedList(list);
				printf("Linked list has been cleaned \n");
			}
			else if (command == REVERSE) {

				if (!isListLooped(list)) {
					reverseLinkedList(list);
					printf("List is reversed \n");
				}
				else {
					printf("You couldn't reverse list \n");
				}
			}
			else if (command == CREATELOOP) {
				isCorrect = FALSE;
				long index;

				if (!isListLooped(list)) {
					while (!isCorrect) {
						printf("Enter number of element to create a loop \n");
						int x = scanf("%li", &index);

						if (x) {
							int ok = createLoop(list, index);

							if (ok) {
								printf("Loop has been created \n");
							}
							else {
								printf("Loop hasn't been created \n");
							}
							isCorrect = TRUE;
						}
					}
				}
				else {
					printf("You couldn't create another loop \n");
				}
			}
			else if (command == ISLOOPED) {
				int isLooped = isListLooped(list);

				if (isLooped) {
					printf("List is looped \n");
				}
				else {
					printf("List is not looped \n");
				}
			}

		}
		else {
			printf("List hasn't been already created \n");
		}
	}    

	if (isListCreated) {
		freeLinkedList(list);
		free(list);
	}    

	return 0;
}

