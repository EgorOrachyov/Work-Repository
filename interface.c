#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

const int NUMBEROFCOMMANDS = 12; 

int main() {

    int isListCreated = FALSE;
    LinkedList * list;

    int isDone = FALSE;
    while (!isDone) {

        printf("==========Linked List========== \n");
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
        printf("9. End \n");
        
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

        printf("=============================== \n");

        if (command == 0) {
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
        else if (command == 9) {
            printf("Exit the application \n");
            isDone = TRUE;
        }
        else if (isListCreated) {

            if (command == 1) {
                printLinkedList(list);
            }
            else if (command == 2) {
                printf("List length = %li \n", list->length);
            }
            else if (command == 3) {
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
            else if (command == 4) {
                data value;
                isCorrect = FALSE;

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
            else if (command == 5) {
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
            else if (command == 6) {
                data value;
                isCorrect = FALSE;

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
            else if (command == 7) {
                freeLinkedList(list);
                printf("Linked list has been cleaned \n");
            }
            else if (command == 8) {
                reverseLinkedList(list);
                printf("List is reversed \n");
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

