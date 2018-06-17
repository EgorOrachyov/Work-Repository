//
// Created by Egor Orachyov on 16.02.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define MEMORY_BASE     16  // Start stack size
#define MEMORY_FACTOR   2   // Factor for stack expanding

Stack * CreateStack()
{
    Stack * stack = (Stack *)calloc(1, sizeof(Stack));
    if (stack == NULL)
    {
        printf("ERROR: Cannot allocate memory for Stack \n");
        exit(11);
    }
    stack->m_size = 0;
    stack->m_top = -1;

    return stack;
}

void FreeStack(Stack * stack)
{
    if (stack != NULL)
    {
        if (stack->m_elements != NULL)
        {
            free(stack->m_elements);
        }
        stack->m_size = 0;
        stack->m_top = -1;
    }
}

void DeleteStack(const Stack * stack)
{
    if (stack != NULL)
    {
        FreeStack(stack);
        free(stack);
    }
}

void PushElement(Stack * stack, int element)
{
    if (stack->m_top < 0)
    {
        stack->m_size = MEMORY_BASE;

        stack->m_elements = (int *)calloc(stack->m_size, sizeof(int));
        if (stack->m_elements == NULL)
        {
            printf("ERROR: Cannot allocate memory for stack's array \n");
            exit(11);
        }
        stack->m_top = 0;
    }
    else
    {
        if (stack->m_size <= stack->m_top + 1)
        {
            stack->m_size *= MEMORY_FACTOR;

            stack->m_elements = (int *)realloc(stack->m_elements, sizeof(int) * stack->m_size);
            if (stack->m_elements == NULL)
            {
                printf("ERROR: Cannot allocate memory for stack's array \n");
                exit(11);
            }
        }

        stack->m_top += 1;
    }
    stack->m_elements[stack->m_top] = element;
}

int PopElement(Stack * stack)
{
    if (stack->m_top < 0)
    {
        printf("ERROR: Attempt to pop from empty stack \n");
        exit(11);
    }
    else
    {
        int val = stack->m_elements[stack->m_top];
        stack->m_top -= 1;

        return val;
    }
}

int IsStackEmpty(Stack * stack)
{
    return (stack->m_top < 0);
}