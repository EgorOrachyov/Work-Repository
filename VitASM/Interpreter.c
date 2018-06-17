//
// Created by Egor Orachyov on 17.03.2018.
//

#include "Interpreter.h"

Interpreter * CreateInterpreter()
{
    Interpreter * obj = (Interpreter *)calloc(1, sizeof(Interpreter));
    if (obj == NULL)
    {
        printf("ERROR: Cannot allocate memory for Interpreter \n");
        exit(11);
    }
    obj->m_num_of_commands = 0;

    return obj;
}

void DeleteInterpreter(Interpreter * obj)
{
    if (obj != NULL)
    {
        free(obj);
    }
}

void SetCommandsList(Interpreter * obj, CommandFormat * commands, long num_of_commands)
{
    if (obj != NULL)
    {
        obj->m_commands = commands;
        obj->m_num_of_commands = num_of_commands;
    }
    else
    {
        printf("WARNING: Interpreter is null pointer \n");
    }
}

void InitMainLoop(Interpreter * obj, int mode)
{
    if (obj->m_commands == NULL)
    {
        return;
    }

    int is_done = FALSE;
    long IP = 0;
    Stack * stack = CreateStack();
    int data[DATA_SIZE];

    double work_time = (double)clock();

    if (mode == SAFE_MODE)
    {
        int is_ret_found = FALSE;

        for(long i = 0; i < obj->m_num_of_commands; i++)
        {
            if (obj->m_commands[i].m_command_id == LD || obj->m_commands[i].m_command_id == ST)
            {
                obj->m_commands[i].m_argument %= DATA_SIZE;

                while(obj->m_commands[i].m_argument < 0)
                {
                    obj->m_commands[i].m_argument = (obj->m_commands[i].m_argument + DATA_SIZE) % DATA_SIZE;
                }
            }
            else if (obj->m_commands[i].m_command_id == RET)
            {
                is_ret_found = TRUE;
            }

            // printf("%li %li %li \n", i, obj->m_commands[i].m_command_id, obj->m_commands[i].m_argument);
        }

        if (!is_ret_found)
        {
            printf("ERROR: Ret command is not found \n");
            return;
        }

        while(IP < obj->m_num_of_commands && !is_done)
        {
            switch (obj->m_commands[IP].m_command_id)
            {
                case LD:
                    PushElement(stack, data[obj->m_commands[IP].m_argument]);
                    break;

                case ST:
                    if (!IsStackEmpty(stack))
                    {
                        data[obj->m_commands[IP].m_argument] = PopElement(stack);
                    }
                    else
                    {
                        printf("ERROR: Stack is empty \n");
                        is_done = TRUE;
                    }
                    break;

                case LDC:
                    PushElement(stack, (int)obj->m_commands[IP].m_argument);
                    break;

                case ADD:
                    if (stack->m_top >= 1)
                    {
                        PushElement(stack, stack->m_elements[stack->m_top] + stack->m_elements[stack->m_top - 1]);
                    }
                    else
                    {
                        printf("ERROR: Add requires 2 arguments but stack has not it \n");
                        is_done = TRUE;
                    }
                    break;

                case SUB:
                    if (stack->m_top >= 1)
                    {
                        PushElement(stack, stack->m_elements[stack->m_top] - stack->m_elements[stack->m_top - 1]);
                    }
                    else
                    {
                        printf("ERROR: Sub requires 2 arguments but stack has not it \n");
                        is_done = TRUE;
                    }
                    break;

                case CMP:
                    if (stack->m_top >= 1)
                    {
                        if (stack->m_elements[stack->m_top] > stack->m_elements[stack->m_top - 1])
                        {
                            PushElement(stack, 1);
                        }
                        else if (stack->m_elements[stack->m_top] < stack->m_elements[stack->m_top - 1])
                        {
                            PushElement(stack, -1);
                        }
                        else
                        {
                            PushElement(stack, 0);
                        }
                    }
                    else
                    {
                        printf("ERROR: Cmp requires 2 arguments but stack has not it \n");
                        is_done = TRUE;
                    }
                    break;

                case JMP:
                    IP = obj->m_commands[IP].m_argument - 1;
                    break;

                case BR:
                    if (stack->m_elements[stack->m_top])
                    {
                        IP = obj->m_commands[IP].m_argument - 1;
                    }
                    break;

                case RET:
                    is_done = TRUE;
                    break;

                default:
                    break;
            }

            IP += 1;
        }
    }
    else
    {
        while(IP < obj->m_num_of_commands && !is_done)
        {
            switch (obj->m_commands[IP].m_command_id)
            {
                case LD:
                    PushElement(stack, data[obj->m_commands[IP].m_argument]);
                    break;

                case ST:
                    data[obj->m_commands[IP].m_argument] = PopElement(stack);
                    break;

                case LDC:
                    PushElement(stack, (int)obj->m_commands[IP].m_argument);
                    break;

                case ADD:
                    PushElement(stack, stack->m_elements[stack->m_top] + stack->m_elements[stack->m_top - 1]);
                    break;

                case SUB:
                    PushElement(stack, stack->m_elements[stack->m_top] - stack->m_elements[stack->m_top - 1]);
                    break;

                case CMP:
                    if (stack->m_elements[stack->m_top] > stack->m_elements[stack->m_top - 1])
                    {
                        PushElement(stack, 1);
                    }
                    else if (stack->m_elements[stack->m_top] < stack->m_elements[stack->m_top - 1])
                    {
                        PushElement(stack, -1);
                    }
                    else
                    {
                        PushElement(stack, 0);
                    }
                    break;

                case JMP:
                    IP = obj->m_commands[IP].m_argument - 1;
                    break;

                case BR:
                    if (stack->m_elements[stack->m_top])
                    {
                        IP = obj->m_commands[IP].m_argument - 1;
                    }
                    break;

                case RET:
                    is_done = TRUE;
                    break;

                default:
                    break;
            }

            IP += 1;
        }
    }

    printf("\n");
    work_time = ((double)clock() - work_time) / CLOCKS_PER_SEC;
    printf("INFO: Total working time %lf \n", work_time);

    printf("INFO: Stack status:\n");
    for(long i = stack->m_top; i >= 0; i--)
    {
        printf("[%li] %i \n", i, stack->m_elements[i]);
    }

    DeleteStack(stack);
}