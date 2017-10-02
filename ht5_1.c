#include<stdio.h>

int bitAnd(int x, int y) {

	return ~((~x)|(~y));
}

bitXor(int x, int y) {

	return ~( ( ~( (~x)&y ) ) & ( ~( x&(~y) ) ) );
}

int thirdBits(void) {
   
    int a = 36;   // 0000 0000 0000 0000 0000 0000 0010 0100
    int b = a;    // 0000 0000 0000 0000 0000 0000 0010 0100
    a = a << 6;   // 0000 0000 0000 0000 0000 1001 0000 0000
    a = a | b;    // 0000 0000 0000 0000 0000 1001 0010 0100
    b = a;        // 0000 0000 0000 0000 0000 1001 0010 0100
    a = a << 12;  // 0000 0000 1001 0010 0100 0000 0000 0000
    a = a | b;    // 0000 0000 1001 0010 0100 1001 0010 0100
    a = a << 6;   // 0010 0100 1001 0010 0100 1001 0000 0000
    a = a | 36;   // 0010 0100 1001 0010 0100 1001 0010 0100

	return a;
}

int fitsBits(int x, int n) {

    int a = (~n) + 1;
    a = a + 32;
    int b = ( (x << a) >> a );

    return !( b ^ x );
}

int sign(int x) {

    int a = !(!x);

	return ((x >> 31) | a);
}

int getByte(int x, int y) {
    
    int a = y << 3;
    int mask = 255;
    x = x >> a;
    x = x & mask;
 
	return x;
}

int logicalShift(int x, int n) {

	int a = (~n) + 1;
	a = 32 + a;
	int mask = ~0;
	mask = mask << a;
	mask = ~mask;
	x = x >> n;
	x = x & mask;
 
	return x;
}

int addOK(int x, int y) {

	int mask = ~(255 << 24);
	int a = (x & mask) + (y & mask);
    a = a >> 24;
    x = (x >> 24) & 255;
    y = (y >> 24) & 255;
    a = (a + x + y) >> 8;

	return (!a);
}

int bang(int x) {

	int y = (~x) + 1;
    int a = ( x | y ) >> 31;

	return a + 1;
}

int conditional(int x, int y, int z) {
   
    int a = !(!x);   // x>0: 1 x=0: 0

    int b = a << 1;  // 10
    b = b | a;       // 11
    a = b;           // 11
    b = b << 2;      // 1100
    b = b | a;       // 1111
    a = b;           // 1111
    b = b << 4;      // 11110000
    b = b | a;       // 11111111
    a = b;           // 11111111
    b = b << 8;      // 1111111100000000
    b = b | a;       // 1111111111111111
    a = b;           // 1111111111111111
    b = b << 16;     // 11111111111111110000000000000000
    b = b | a;       // 11111111111111111111111111111111
    a = b;           // 11111111111111111111111111111111



	return ( a&y ) | ( (~a)&z ) ;
} 

int isPower2(int x) {

    int a = 1;
    a = (~a) + 1;
   
	return ( x && !( x & (x + a)) );
}

int main() {

	/*

    printf("bitAnd: %i \n", bitAnd(6,5));

    printf("bitXor: %i \n", bitXor(4,5));

    printf("thirdBits: %x \n", thirdBits());

    printf("fitsBits: %i %i\n", fitsBits(5,3), fitsBits(-4,3));

    printf("sign: %i %i %i \n", sign(130), sign(-23), sign(0));

    printf("getByte: %x %x \n", 0x123445678, getByte(0x123445678,1));

    printf("logicalShift: %x \n", logicalShift(0x87654321,4));

    printf("addOK: %i %i \n",addOK(0x80000000,0x80000000), addOK(0x80000000, 0x70000000));
 
    printf("bang: %i %i \n", bang(3), bang(0));

    printf("conditional: %i \n", conditional(2,4,5));

    printf("isPower2: %i %i %i %i \n", isPower2(33), isPower2(16), isPower2(0), isPower2(-4));

    */

	return 0;
}