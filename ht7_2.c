#include <stdio.h>

const int YES = 1;
const int NO = 0;

void other();
void input();

int main() {
    printf("It is main \n");
    input();

    return 0;
}

void other() {
    printf("It is other \n");
}

void input() {
    printf("It is input \n");
    printf("======================================== \n");

    int a[1] = {1};

    int stop = NO;
    while(!stop) {

        printf("address (main)  = 0x%x or %i \n", &main,  &main);
        printf("address (input) = 0x%x or %i \n", &input, &input);
        printf("address (other) = 0x%x or %i \n", &other, &other);
        printf("======================================== \n");

        int num = 0;
        int flag = NO;
        while(!flag) {
            printf("Enter number of stack elements for outputting: ");
            flag = scanf("%i",&num);
        }

        for(int i = 0; i<num; i++) {
            printf("a[%i] = 0x%x or %i \n",i,a[i],a[i]);
        }
 
        printf("======================================== \n");	

        flag = YES;
        while(flag) {
            printf("Enter i - index of array a and x - this value for replacement (-1 -1 to exit): ");
        	
            int i,x;
            int check = scanf("%i %i", &i, &x);
            
            // 2 is the number of arguments, scanned in scanf 
            if (check == 2) {
                if ((i == -1) && (x == -1)) {
                    flag = NO;
                } 
                else {
                    printf("a[%i] = 0x%x or %i  was replaced to a[%i] = 0x%x or %i \n", i, a[i], a[i], i, x, x);
                    a[i] = x;
                }
            }       
        }

        printf("======================================== \n");	

        flag = YES;
        while(flag) {
            printf("Enter 0 to leave \"input\" function or 1 (or another number) to go to the beginning \n");

            int x;
            int check = scanf("%i", &x);

            if (check) {
                if (!x) {
                    flag = NO;
                    stop = YES;
                }
                else {
                    flag = NO;
                } 
            }
        }

        printf("======================================== \n");	
    }
}