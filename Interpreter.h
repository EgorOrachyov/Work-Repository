//
// Created by Egor Orachyov on 19.02.2018.
//

#ifndef VITASM_INTERPRETER_H
#define VITASM_INTERPRETER_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "ASMformat.h"
#include "CommandStructure.h"

//----------------------------------------------------
// Interpreter
//----------------------------------------------------
typedef struct
{
    CommandFormat * m_commands;
    long m_num_of_commands;

} Interpreter;

//----------------------------------------------------
// Allocates memory for interpreter and returns
// pointer to that
//----------------------------------------------------
Interpreter * CreateInterpreter();

//----------------------------------------------------
// Deletes interpreter data
//----------------------------------------------------
void DeleteInterpreter(Interpreter * obj);

//----------------------------------------------------
// Sets interpreter's internal list of commands
// (could be achieved by any way)
//----------------------------------------------------
void SetCommandsList(Interpreter * obj, CommandFormat * commands, long num_of_commands);

//----------------------------------------------------
// Loop of interpretation
// (mode: SAFE - all cautions will be checked)
// (mode: FAST - ignore all warnings)
//----------------------------------------------------
void InitMainLoop(Interpreter * obj, int mode);

#endif //VITASM_INTERPRETER_H
