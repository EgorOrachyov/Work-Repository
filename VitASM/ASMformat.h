//
// Created by Egor Orachyov on 16.02.2018.
//

#ifndef VITASM_ASMFORMAT_H
#define VITASM_ASMFORMAT_H

#define FALSE   0
#define TRUE    1

#define RET     0
#define LD      1
#define ST      2
#define LDC     3
#define ADD     4
#define SUB     5
#define CMP     6
#define JMP     7
#define BR      8

#define SAFE_MODE   0
#define FAST_MODE   1

#define RET_TXT "ret"
#define LD_TXT  "ld"
#define ST_TXT  "st"
#define LDC_TXT "ldc"
#define ADD_TXT "add"
#define SUB_TXT "sub"
#define CMP_TXT "cmp"
#define JMP_TXT "jmp"
#define BR_TXT  "br"

#define STRING_SIZE 256

#define FORMAT_C        1
#define FORMAT_LC_OR_CA 2
#define FORMAT_LCA      3

#define DATA_SIZE       262144
#define MIN_DATA_INDEX  0
#define MAX_DATA_INDEX  262143

#endif //VITASM_ASMFORMAT_H
