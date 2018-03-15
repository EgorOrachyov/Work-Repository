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
        int scanned_ards = 0;

        int key;
        int flag = FALSE;
        while (!flag)
        {
            printf("1. Interpret from file \n");
            printf("2. Exit Application \n");
            printf("Enter num of action: ");
            scanned_ards = scanf("%i", &key);
            if (scanned_ards && key >= 1 && key <= 2)
            {
                flag = TRUE;
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
                scanned_ards = scanf("%s", filename);
                if (scanned_ards)
                {
                    flag = TRUE;
                }
            }

            flag = FALSE;
            while (!flag)
            {
                printf("Enter mode (0 - SAFE mode / 1 - FAST mode): ");
                scanned_ards = scanf("%i", &mode);
                if (scanned_ards && mode >= 0 && mode <= 1)
                {
                    flag = TRUE;
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