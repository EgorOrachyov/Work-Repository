#include "Parser.h"
#include "Interpreter.h"

#define INTERPRETER_F 1
#define EXIT_F        2

int main()
{
    Interpreter * interpreter = CreateInterpreter();

    int is_done = FALSE;
    while (!is_done)
    {
        printf("*********** VitASM Interpreter ***********\n");

        int mode = SAFE_MODE;
        char filename[STRING_SIZE] = "\0";
        int scanned_args = 0;

        char buffer = 0;
        int key = 0;
        int flag = FALSE;
        while (!flag)
        {
            printf("1. Interpret from file \n");
            printf("2. Exit Application \n");
            printf("Enter num of action: ");
            fscanf(stdin, "%c", &buffer);
            if (buffer >= '1' && buffer <= '2')
            {
                flag = TRUE;
                key = buffer - '0';
            }
        }

        if (key == EXIT_F)
        {
            is_done = TRUE;
        }
        else if (key == INTERPRETER_F)
        {
            flag = FALSE;
            while (!flag)
            {
                printf("Enter filename: ");
                scanned_args = fscanf(stdin, "%s", filename);
                if (scanned_args)
                {
                    flag = TRUE;
                }
            }

            buffer = 0;
            flag = FALSE;
            while (!flag)
            {
                printf("Enter mode (0 - SAFE mode / 1 - FAST mode): ");
                fscanf(stdin, "%c", &buffer);
                if (buffer >= '0' && buffer <= '1')
                {
                    flag = TRUE;
                    mode = buffer - '0';
                }
            }

            ParserASM * parser = CreateParserASM();
            int is_ok = ParseASMFile(parser, filename);

            if (is_ok)
            {
                CommandFormat * commands;
                long num_of_commands;
                commands = GetListOfCommands(parser, &num_of_commands);

                SetCommandsList(interpreter, commands, num_of_commands);
                InitMainLoop(interpreter, mode);
            }

            DeleteParserASM(parser);
        }
    }

    DeleteInterpreter(interpreter);

    return 0;
}