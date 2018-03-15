//
// Created by Egor Orachyov on 16.02.2018.
//

#include "Parser.h"

#define MEMORY_BASE     16  // Start stack size
#define MEMORY_FACTOR   2   // Factor for stack expanding

int IsCharResolved(const char c)
{
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') ||
        (c == '_') ||
        (c == '-'))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int IsLabelCorrect(const char * lbl)
{
    if (lbl[0] >= '0' && lbl[0] <= '9')
    {
        return FALSE;
    }
    else
    {
        int i = 0;
        while(lbl[i] != '\0')
        {
            if (lbl[i] == '-')
            {
                return FALSE;
            }
            i += 1;
        }

        return TRUE;
    }
}


int GetCommandID(const char * cmd)
{
    if (strcmp(RET_TXT, cmd) == 0)
    {
        return RET;
    }
    else if (strcmp(LD_TXT, cmd) == 0)
    {
        return LD;
    }
    else if (strcmp(ST_TXT, cmd) == 0)
    {
        return ST;
    }
    else if (strcmp(LDC_TXT, cmd) == 0)
    {
        return LDC;
    }
    else if (strcmp(ADD_TXT, cmd) == 0)
    {
        return ADD;
    }
    else if (strcmp(SUB_TXT, cmd) == 0)
    {
        return SUB;
    }
    else if (strcmp(CMP_TXT, cmd) == 0)
    {
        return CMP;
    }
    else if (strcmp(JMP_TXT, cmd) == 0)
    {
        return JMP;
    }
    else if (strcmp(BR_TXT, cmd) == 0)
    {
        return BR;
    }
    else
    {
        return -1;
    }
}

int GetArgument(const char * value, int * error)
{
    *error = FALSE;
    int i = 0;
    int result = 0;

    if (value[i] == '-')
    {
        i += 1;
        while(value[i] != '\0')
        {
            if (value[i] >= '0' && value[i] <= '9')
            {
                result = result * 10 - (value[i] - '0');
            }
            else
            {
                *error = TRUE;
                return result;
            }
            i += 1;
        }
    }
    else
    {
        while(value[i] != '\0')
        {
            if (value[i] >= '0' && value[i] <= '9')
            {
                result = result * 10 + (value[i] - '0');
            }
            else
            {
                *error = TRUE;
                return result;
            }
            i += 1;
        }
    }

    return result;
}

int IsCommandWithLabelArg(int command_id)
{
    if (command_id == BR || command_id == JMP)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int IsCommandWithIntArg(int command_id)
{
    if (command_id == LDC || command_id == LD || command_id == ST)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void ExpandLabelsArray(ParserASM * parser)
{
    if (parser->m_labels_size <=0 )
    {
        parser->m_labels_size = MEMORY_BASE;
        parser->m_labels = (Label *)calloc(parser->m_labels_size, sizeof(Label));
        if (parser->m_labels == NULL)
        {
            printf("ERROR: Cannot allocate memory for labels' array \n");
            exit(11);
        }
    }
    else if (parser->m_labels_size <= parser->m_num_of_labels)
    {
        parser->m_labels_size *= MEMORY_FACTOR;
        parser->m_labels = (Label *)realloc(parser->m_labels, sizeof(Label) * parser->m_labels_size);
        if (parser->m_labels == NULL)
        {
            printf("ERROR: Cannot allocate memory for labels' array \n");
            exit(11);
        }
    }
}

void ExpandLabelArgsArray(ParserASM * parser)
{
    if (parser->m_label_args_size <=0 )
    {
        parser->m_label_args_size = MEMORY_BASE;
        parser->m_label_args = (Label *)calloc(parser->m_label_args_size, sizeof(Label));
        if (parser->m_label_args == NULL)
        {
            printf("ERROR: Cannot allocate memory for labels' array \n");
            exit(11);
        }
    }
    else if (parser->m_label_args_size <= parser->m_num_of_label_args)
    {
        parser->m_label_args_size *= MEMORY_FACTOR;
        parser->m_label_args = (Label *)realloc(parser->m_label_args, sizeof(Label) * parser->m_label_args_size);
        if (parser->m_label_args == NULL)
        {
            printf("ERROR: Cannot allocate memory for labels' array \n");
            exit(11);
        }
    }
}

void ExpandCommandsArray(ParserASM * parser)
{
    if (parser->m_commands_size <=0 )
    {
        parser->m_commands_size = MEMORY_BASE;
        parser->m_commands = (CommandFormat *)calloc(parser->m_commands_size, sizeof(CommandFormat));
        if (parser->m_commands == NULL)
        {
            printf("ERROR: Cannot allocate memory for commands' array \n");
            exit(11);
        }
    }
    else if (parser->m_commands_size <= parser->m_num_of_commands)
    {
        parser->m_commands_size *= MEMORY_FACTOR;
        parser->m_commands = (CommandFormat *)realloc(parser->m_commands, sizeof(CommandFormat) * parser->m_commands_size);
        if (parser->m_commands == NULL)
        {
            printf("ERROR: Cannot allocate memory for commands' array \n");
            exit(11);
        }
    }
}

ParserASM * CreateParserASM()
{
    ParserASM * parser = (ParserASM *)calloc(1, sizeof(ParserASM));
    if (parser == NULL)
    {
        printf("ERROR: Cannot allocate memory for parser \n");
        exit(11);
    }
    parser->m_num_of_labels = 0;
    parser->m_num_of_commands = 0;
    parser->m_num_of_label_args = 0;

    parser->m_labels_size = 0;
    parser->m_commands_size = 0;
    parser->m_label_args_size = 0;

    return parser;
}

void DeleteParserASM(const ParserASM * parser)
{
    if (parser != NULL)
    {
        if (parser->m_commands != NULL)
        {
            free(parser->m_commands);
        }
        if (parser->m_labels != NULL)
        {
            free(parser->m_labels);
        }
        if (parser->m_label_args != NULL)
        {
            free(parser->m_label_args);
        }

        free(parser);
    }
}

int ParseASMFile(ParserASM * parser, const char * filename)
{
    if (parser == NULL)
    {
        printf("WARNING: Parser is null pointer \n");
        return FALSE;
    }

    if (filename != NULL)
    {
        FILE * file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("ERROR: Cannot open file with name %s \n", filename);
            exit(11);
        }

        int has_error = FALSE;
        int has_error_in_iteration = FALSE;

        long line_index = 1;
        char buffer[STRING_SIZE];

        while (!feof(file))
        {
            has_error_in_iteration = FALSE;

            char last_c = '#';
            int colon_count;
            int words_count;
            int current_word_len;
            char words[3][STRING_SIZE];

            // read new line from file
            fgets(buffer, STRING_SIZE, file);

            colon_count = 0;
            words_count = 0;
            current_word_len = 0;

            words[0][0] = '\0';
            words[1][0] = '\0';
            words[2][0] = '\0';

            int i = 0;
            while (buffer[i] != '\n' && buffer[i] != '\0')
            {
                i += 1;
            }
            if (buffer[i] == '\n')
            {
                buffer[i] = '\0';
            }

            ////////////////////// PARSING ///////////////////////
            /// parse line to find command, label, argument and
            /// exclude unresolved symbols and mistakes in file

            i = 0;
            while(buffer[i] != '\0' && buffer[i] != ';')
            {
                // if current char is part of command or label name
                if (IsCharResolved(buffer[i]))
                {
                    if (last_c == '#')
                    {
                        last_c = '%';
                    }

                    if (words_count >= 3)
                    {
                        printf("ERROR: Incorrect format in line %li \n -> \"%s\"\n", line_index, buffer);
                        has_error_in_iteration = TRUE;
                        break;
                    }

                    words[words_count][current_word_len] = buffer[i];
                    current_word_len += 1;
                }
                // if current char closes previous word or not
                else if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
                {
                    if (last_c == '%')
                    {
                        words[words_count][current_word_len] = '\0';
                        last_c = '#';
                        words_count += 1;
                        current_word_len = 0;
                    }
                }
                // if current char closes label name
                else if (buffer[i] == ':')
                {
                    if (last_c == '%' && colon_count == 0)
                    {
                        words[words_count][current_word_len] = '\0';
                        last_c = '#';
                        words_count += 1;
                        current_word_len = 0;
                        colon_count += 1;
                    }
                    else
                    {
                        printf("ERROR: Unresolved symbol \"%c\" in line %li \n -> \"%s\"\n", buffer[i], line_index, buffer);
                        has_error_in_iteration = TRUE;
                        break;
                    }
                }
                // if it is unresolved char
                else
                {
                    printf("ERROR: Unresolved symbol \"%c\" in line %li \n -> \"%s\"\n", buffer[i], line_index, buffer);
                    has_error_in_iteration = TRUE;
                    break;
                }

                i += 1;
            }
            if (last_c == '%')
            {
                words[words_count][current_word_len] = '\0';
                words_count += 1;
            }

            // if we has error we break the loop and
            // leave function with FALSE flag
            if (has_error_in_iteration)
            {
                line_index += 1;
                has_error = has_error_in_iteration;
                continue;
            }

            ///////////////// COMMANDS ANALYSIS //////////////////
            /// Look through read commands and test different
            /// situations:
            /// 1) label: command argument
            /// 2) label: command
            /// 3) command argument
            /// 4) command
            /// And check correct names of commnads and
            /// formats of arguments and its relevance for
            /// concrete command

            // printf("%s %s %s \n", words[0], words[1], words[2]);

            if (words_count == FORMAT_LCA)
            {
                if (IsLabelCorrect(words[0]))
                {
                    ExpandLabelsArray(parser);
                    char is_copied = FALSE;
                    for(long j = 0; j < parser->m_num_of_labels; j++)
                    {
                        if (strcmp(words[0], parser->m_labels[j].m_label) == 0)
                        {
                            is_copied = TRUE;
                            break;
                        }
                    }

                    if (is_copied)
                    {
                        printf("ERROR: duplicated label in line %li \n -> \"%s\"\n", line_index, buffer);
                        has_error = TRUE;
                    }
                    else
                    {
                        memcpy(parser->m_labels[parser->m_num_of_labels].m_label, words[0], sizeof(char) * STRING_SIZE);
                        parser->m_labels[parser->m_num_of_labels].m_command_id = parser->m_num_of_commands;
                        parser->m_num_of_labels += 1;
                    }
                }
                else
                {
                    printf("ERROR: Label has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                    has_error = TRUE;
                }

                int command_id = GetCommandID(words[1]);
                if (command_id >= 0)
                {
                    ExpandCommandsArray(parser);
                    parser->m_commands[parser->m_num_of_commands].m_command_id = command_id;

                    if (IsCommandWithLabelArg(command_id))
                    {
                        if (IsLabelCorrect(words[2]))
                        {
                            ExpandLabelArgsArray(parser);
                            memcpy(parser->m_label_args[parser->m_num_of_label_args].m_label, words[2], sizeof(char) * STRING_SIZE);
                            parser->m_label_args[parser->m_num_of_label_args].m_command_id = parser->m_num_of_commands;
                            parser->m_num_of_label_args += 1;
                        }
                        else
                        {
                            printf("ERROR: Argument has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                            has_error = TRUE;
                        }
                    }
                    else if (IsCommandWithIntArg(command_id))
                    {
                        int error;
                        int value = GetArgument(words[2], &error);
                        if (error)
                        {
                            printf("ERROR: Argument has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                        }
                        else
                        {
                            parser->m_commands[parser->m_num_of_commands].m_argument = value;
                        }
                    }
                    else
                    {
                        printf("ERROR: This command do not get any argument line %li \n -> \"%s\"\n", line_index, buffer);
                        has_error = TRUE;
                    }

                    parser->m_num_of_commands += 1;
                }
                else
                {
                    printf("ERROR: Command has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                    has_error = TRUE;
                }
            }
            else if (words_count == FORMAT_LC_OR_CA)
            {
                int command_id = GetCommandID(words[0]);
                if (command_id >= 0)
                {
                    ExpandCommandsArray(parser);
                    parser->m_commands[parser->m_num_of_commands].m_command_id = command_id;

                    if (IsCommandWithLabelArg(command_id))
                    {
                        if (IsLabelCorrect(words[2]))
                        {
                            ExpandLabelArgsArray(parser);
                            memcpy(parser->m_label_args[parser->m_num_of_label_args].m_label, words[1], sizeof(char) * STRING_SIZE);
                            parser->m_label_args[parser->m_num_of_label_args].m_command_id = parser->m_num_of_commands;
                            parser->m_num_of_label_args += 1;
                        }
                        else
                        {
                            printf("ERROR: Argument has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                            has_error = TRUE;
                        }
                    }
                    else if (IsCommandWithIntArg(command_id))
                    {
                        int error;
                        int value = GetArgument(words[1], &error);
                        if (error)
                        {
                            printf("ERROR: Argument has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                        }
                        else
                        {
                            parser->m_commands[parser->m_num_of_commands].m_argument = value;
                        }
                    }
                    else
                    {
                        printf("ERROR: This command do not get any argument line %li \n -> \"%s\"\n", line_index, buffer);
                        has_error = TRUE;
                    }

                    parser->m_num_of_commands += 1;
                }
                else if ((command_id = GetCommandID(words[1])) >= 0)
                {
                    if (IsLabelCorrect(words[0]))
                    {
                        ExpandLabelsArray(parser);
                        char is_copied = FALSE;
                        for(long j = 0; j < parser->m_num_of_labels; j++)
                        {
                            if (strcmp(words[0], parser->m_labels[j].m_label) == 0)
                            {
                                is_copied = TRUE;
                                break;
                            }
                        }

                        if (is_copied)
                        {
                            printf("ERROR: duplicated label in line %li \n -> \"%s\"\n", line_index, buffer);
                            has_error = TRUE;
                        }
                        else
                        {
                            memcpy(parser->m_labels[parser->m_num_of_labels].m_label, words[0], sizeof(char) * STRING_SIZE);
                            parser->m_labels[parser->m_num_of_labels].m_command_id = parser->m_num_of_commands;
                            parser->m_num_of_labels += 1;
                        }
                    }
                    else
                    {
                        printf("ERROR: Label has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                        has_error = TRUE;
                    }

                    if (IsCommandWithIntArg(command_id) || IsCommandWithLabelArg(command_id))
                    {
                        printf("ERROR: Command requires argument in line %li \n -> \"%s\"\n", line_index, buffer);
                        has_error = TRUE;
                    }
                    else
                    {
                        ExpandCommandsArray(parser);
                        parser->m_commands[parser->m_num_of_commands].m_command_id = command_id;
                        parser->m_num_of_commands += 1;
                    }
                }
                else
                {
                    printf("ERROR: Command has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                    has_error = TRUE;
                }
            }
            else if (words_count == FORMAT_C)
            {
                int command_id = GetCommandID(words[0]);
                if (command_id >= 0)
                {
                    if (IsCommandWithIntArg(command_id) || IsCommandWithLabelArg(command_id))
                    {
                        printf("ERROR: Command requires argument in line %li \n -> \"%s\"\n", line_index, buffer);
                        has_error = TRUE;
                    }
                    else
                    {
                        ExpandCommandsArray(parser);
                        parser->m_commands[parser->m_num_of_commands].m_command_id = command_id;
                        parser->m_num_of_commands += 1;
                    }
                }
                else
                {
                    printf("ERROR: Command has wrong format in line %li \n -> \"%s\"\n", line_index, buffer);
                    has_error = TRUE;
                }
            }

            line_index += 1;
        }

        fclose(file);

        /////////// ASSOCIATION OF COMANDS WITH LABEL ARGS AND COMMANDS ID /////////
        /// Go through parser's labels and label_args arrays
        /// to associate a command and command, which
        /// links to the last one, or give an error,
        /// that link was not found

        if (!has_error)
        {
            for(long i = 0; i < parser->m_num_of_label_args; i++)
            {
                int is_found = FALSE;
                for(long j = 0; j < parser->m_num_of_labels; j++)
                {
                    if (strcmp(parser->m_label_args[i].m_label, parser->m_labels[j].m_label) == 0)
                    {
                        is_found = TRUE;
                        parser->m_commands[parser->m_label_args[i].m_command_id].m_argument = parser->m_labels[j].m_command_id;
                        break;
                    }
                }

                if (!is_found)
                {
                    printf("ERROR: Label is not found -> %s ->\n", parser->m_label_args[i].m_label);
                    has_error = TRUE;
                    break;
                }
            }
        }

        if (has_error)
        {
            printf("INFO: file \"%s\" parsing is interrupted \n", filename);
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        printf("WARNING: Filename is null pointer \n");
        return FALSE;
    }
}

CommandFormat * GetListOfCommands(const ParserASM * parser, long * num_of_commands)
{
    if (parser->m_commands != NULL)
    {
        *num_of_commands = parser->m_num_of_commands;
        return parser->m_commands;
    }
    else
    {
        printf("WARNING: List of commands is empty \n");
        return NULL;
    }
}
