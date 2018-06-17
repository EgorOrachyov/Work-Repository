//
// Created by Egor Orachyov on 16.02.2018.
//

#ifndef VITASM_STACK_H
#define VITASM_STACK_H

//----------------------------------------------------
// Stack Structure
//----------------------------------------------------
typedef struct
{
    int * m_elements;
    long m_size;
    long m_top;

} Stack;

//----------------------------------------------------
// Allocate memory for stack, initialize members
// and return pointer to that
//----------------------------------------------------
Stack * CreateStack();

//----------------------------------------------------
// Empty stack's array
//----------------------------------------------------
void FreeStack(Stack * stack);

//----------------------------------------------------
// Empty stack and delete memory for that
//----------------------------------------------------
void DeleteStack(const Stack * stack);

//----------------------------------------------------
// Push element on top of the stack
//----------------------------------------------------
void PushElement(Stack * stack, const int element);

//----------------------------------------------------
// Pop element from the top of the stack
//----------------------------------------------------
int PopElement(Stack * stack);

//----------------------------------------------------
// Return true if stack has no elements
//----------------------------------------------------
int IsStackEmpty(Stack * stack);

#endif //VITASM_STACK_H
