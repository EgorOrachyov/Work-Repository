//
// Created by Egor Orachyov on 16.02.2018.
//

#ifndef VITASM_PARSER_H
#define VITASM_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ASMformat.h"
#include "CommandStructure.h"

typedef struct
{
    char m_label[STRING_SIZE];
    long m_command_id;

} Label;

typedef struct {

    Label * m_labels;
    Label * m_label_args;
    CommandFormat * m_commands;

    long m_num_of_commands;
    long m_num_of_labels;
    long m_num_of_label_args;

    long m_labels_size;
    long m_commands_size;
    long m_label_args_size;

} ParserASM;

//----------------------------------------------------
// Allocates memory for parser and returns pointer
//----------------------------------------------------
ParserASM * CreateParserASM();

//----------------------------------------------------
// Deletes parser and all its internal data
//----------------------------------------------------
void DeleteParserASM(const ParserASM * parser);

//----------------------------------------------------
// Syntactic and semantic analysis fo file with
// file with filename
//----------------------------------------------------
int ParseASMFile(ParserASM * parser, const char * filename);

//----------------------------------------------------
// Returns list of commands with its arguments
//----------------------------------------------------
CommandFormat * GetListOfCommands(const ParserASM * parser, long * num_of_commands);

#endif //VITASM_PARSER_H
