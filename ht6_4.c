#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// structure of an floating point value
const int signLength = 1;
const int expLength = 8;
const int mantissaLength = 23;


typedef void (* funcPointer)(const float);

struct Method {
	char description[255]; 
	funcPointer fPointer;
};


// print float value in standart way (sign, exp, mantissa)
void printFloatInFormat(int sign, int exp, int mantissa);
// uses union of float and int
void firstMethod(const float f);
// uses union of float and struct with bit-fields
void secondMethod(const float f);
// uses pointer
void thirdMethod(const float f);
// asks method of printing and prints float in 1 of 3 ways
void definedPrintOfFloat(struct Method a[], int methodsCount);


int main() {
 
    struct Method methods[] = {{"uses union of float and int", firstMethod}, 
                               {"uses union of float and struct with bit-fields", secondMethod}, 
                               {"uses pointer", thirdMethod}};

    int methodsCount = sizeof(methods) / sizeof(struct Method);

    definedPrintOfFloat(methods, methodsCount);

	return 0;

}


void printFloatInFormat(const int sign,const int exp,const int mantissa) {

    // does value equal to +Inf or -Inf
    if ((exp == 255) && (mantissa == 0)) {

    	if (sign) {
    		printf("-Inf");
    	}
    	else {
    		printf("+Inf");
    	}

    } 
    // does value equal NaN
    else if ((exp == 255) && (((mantissa+1) >> mantissaLength == 1) || (mantissa >> (mantissaLength - 1) == 1))) {

    	printf("NaN");

    }
    // print an normal value
    else {

    	double f = pow(2, mantissaLength); 
        f = (double)mantissa / f;   
       
        /*
           This part release an additional alignment of number,
           which is got from mantissa (evaluating of accuracy)
        */

        int accuracy = 0;
        int zeros = (mantissa - 1) & (~mantissa);
        while (zeros & accuracy < 23) {

        	accuracy++;
        	zeros = zeros >> 1;

        }  
        accuracy = mantissaLength - accuracy;
         
	    printf("(%i) * (%.*f) * (2^%i)", (int)pow(-1, sign), accuracy, 1.0 + f, exp - 127);

    }

}

void firstMethod(const float f) {

	union { 
		int i;
		float f;
	} un;

	un.f = f;

	int sign = (un.i >> 31) & 1;
	int exp = (un.i >> mantissaLength) & 255;
	int mantissa = ((1 << mantissaLength) - 1) & un.i;

    printFloatInFormat(sign, exp, mantissa);

}

void secondMethod(const float f) {

    union {
    	float f;
    	struct {
    	    unsigned int mantissa: 23; 
    	    unsigned int exp: 8;  
    	    unsigned int sign: 1;  
        } s;
    } un;

    un.f = f;
	printFloatInFormat(un.s.sign, un.s.exp, un.s.mantissa);

}

void thirdMethod(const float f) {

	const float * p = &f;
    int i = *((int *)p);

    int sign = (i >> 31) & 1;
	int exp = (i >> mantissaLength) & 255;
	int mantissa = ((1 << mantissaLength) - 1) & i;

    printFloatInFormat(sign, exp, mantissa);

}

void definedPrintOfFloat(struct Method a[], int methodsCount) {

	if (sizeof(float) != 4) {

		printf("Sorry, size of \"float\" is not equal \"4 byte\" on your platform \n");
	
	} 
    else if (!methodsCount) {

        printf("Sorry, has no method for formated printing of floating-point value \n");

    }
	else {

		/*
		   Run our program in a loop
		   At each step we ask the user about the wanted action
		   Stop the loop and terminate the program if the flag is 0
		*/ 

        int flag = -1;
        float f, f1, f2;

        while (1) {

        	printf("\n===========================================\n");
        	printf("Methods of printing floating-point numbers:\n");
      
            for(int i = 0; i < methodsCount; i++) {

            	printf("%i: %s \n", i + 1, a[i].description);

            }
            
            while ((flag > methodsCount) || (flag < 0)) {

            	printf("Please, choose wanted method: 1 to %i / 0 - to exit: ", methodsCount);
        	    scanf("%i", &flag);

        	    if (!flag) {
        	    	exit(0);
        	    }
        	    else if ((flag >= 1) && (flag <= methodsCount)) {
        	    	break;
        	    }

            }
        	
	        printf("Please, write 2 floating-point numbers:\n");
		    printf("First number: ");
		    scanf("%f", &f1);
		    printf("Second number: ");
		    scanf("%f", &f2);

		    f = f1 / f2;

		    printf("first number / second number = %f \n", f);
		    printf("Formated view: ");
		    a[flag - 1].fPointer(f); 
		    printf("\n...........................................\n");

		    flag = -1;

        }    

	}

}
