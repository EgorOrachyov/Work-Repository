//
// Created by Egor Orachyov on 19.02.2018.
//

#ifndef VITASM_COMMANDSTRUCTURE_H
#define VITASM_COMMANDSTRUCTURE_H

//----------------------------------------------------
// Command with its id and long argument
// (if it has no argument the last one equals 0)
//----------------------------------------------------
typedef struct {

    long m_command_id;
    long m_argument;

} CommandFormat;

#endif //VITASM_COMMANDSTRUCTURE_H
