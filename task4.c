#include<stdio.h>

const int Num = 100;

int main() {

	long res = 0;

	for(int i = 1; i <= Num; i++) {
		for(int j = 1; j < i; j++) {
			res += i * j;
		}
		for(int j = i + 1; j <= Num; j++) {
			res += i * j;
		}
	}

	printf("%li \n", res);

    return 0;
}