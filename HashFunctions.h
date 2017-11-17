#ifndef _HASHFUNCTIONS_H_
#define _HASHFUNCTIONS_H_

#include <string.h>


long getHash1(char * string, int simple, long limit) {
	long p = 1L;
	long hash = 0L;
	int length = strlen(string);

	for(int i = 0; i < length; i++) {
		hash = (hash + string[i] * p) % limit;
		p = p * simple;
	}

	return hash;
}


long getHash2(char * string, int simple, long limit) {
	long hash = 0L;
	int length = strlen(string);

	for(int i = 0; i < length; i++) {
		hash = (hash * simple + string[i]) % limit;
	}

	return hash;
}


long getHash3(char * string, int simple, long limit) {
	long hash = 0L;
	int length = strlen(string);

	for(int i = 0; i < length; i++) {
		hash = (hash * simple + ((string[i] << 8) ^ simple)) % limit;
	}

	return hash;
}

#endif