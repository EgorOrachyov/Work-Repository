#include <string.h>
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
void printFloatInFormat(int,int,int);
// uses union of float and int
void firstMethod(const float f);
// uses union of float and struct with bit-fields
void secondMethod(const float f);
// uses pointer
void thirdMethod(const float f);
// asks method of printing and prints float in 1 of 3 ways
void definedPrintOfFloat(struct Method a[]);


int main() {
 
    struct Method methods[3];

    strcpy(methods[0].description,"uses union of float and int");
    methods[0].fPointer = firstMethod;

    strcpy(methods[1].description,"uses union of float and struct with bit-fields");
    methods[1].fPointer = secondMethod;

    strcpy(methods[2].description,"uses pointer");
    methods[2].fPointer = thirdMethod;

    definedPrintOfFloat(methods);

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
	    printf("(%i) * (%-25.24f) * (2^%i)", (int)pow(-1, sign), 1.0 + f, exp - 127);

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

void definedPrintOfFloat(struct Method a[]) {

	if (sizeof(float) != 4) {

		printf("Sorry, size of \"float\" is not equal \"4 byte\" on your platform \n");
	
	} 
	else {

		/*
		 *  Run our program in a loop
		 *  At each step we ask the user about the wanted action
		 *  Stop the loop and terminate the program if the flag is 0
		 */ 

        int flag = 4;
        float f, f1, f2;

        while (1) {

        	printf("\n===========================================\n");
        	printf("Methods of printing floating-point numbers:\n");
      
            for(int i = 0; i < 3; i++) {
            	printf("%i: %s \n", i + 1, a[i].description);
            }
            
            while ((flag > 3) || (flag < 0)) {

            	printf("Please, choose wanted method: 1 / 2 / 3 / 0 - to exit: ");
        	    scanf("%i", &flag);

        	    if (!flag) {
        	    	exit(0);
        	    }
        	    else if ((flag >= 1) || (flag <= 3)) {
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

		    flag = 4;

        }    

	}

}
