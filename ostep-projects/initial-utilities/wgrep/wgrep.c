/*
* Program that looks through a file for a user-specified
* search term in a line. If the word is found, it prints 
* the line. 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHARS 5000
#define MAX_STR_LEN 25

// Function Prototype. 
bool found_str(char * p_line, int line_size, char * p_str, int str_len);

int main (int argc, char * argv[])
{
    int status = 0; 

    if (1 == argc)
    {
        printf("wgrep: searchterm [file ...]\n");
        status = 1; 
        goto EXIT; 
    }

    for (int idx = 1; idx < argc; idx++)
    {
        if (NULL == argv[idx])
        {
            goto EXIT; 
        }
    }

    int str_len = strnlen(argv[1], MAX_STR_LEN);

    if (MAX_STR_LEN == str_len)
    {
        goto EXIT; 
    }

    for (int idx_i = 2; idx_i < argc; idx_i++)
    {
        FILE * p_file = fopen(argv[idx_i], "r");

        if (NULL == p_file)
        {
            printf("wgrep: cannot open file\n"); 
            status = 1; 
            break; 
        }

        size_t line_size = MAX_CHARS; 
        char * p_line = calloc(MAX_CHARS, sizeof(char)); 

        if (NULL == p_line)
        {
            goto CLOSE_FILE; 
        }

        for (int read = getline(&p_line, &line_size, p_file); read != -1; read = getline(&p_line, &line_size, p_file))
        {
            if (true == found_str(p_line, read, argv[1], str_len))
            {
                printf("%s", p_line); 
            }
        }

        free(p_line); 

    CLOSE_FILE: 
        if (-1 == fclose(p_file))
        {
            break; 
        }
    }

EXIT:
    return status; 
}

// Function that searches a line from a file for a specified string. 
bool found_str(char * p_line, int line_size, char * p_str, int str_len)
{
    bool b_found_str = false;
    
    if ((NULL != p_line) && (NULL != p_str))
    {
        char buf[str_len + 1];
        memset(buf, '\0', str_len + 1); 

        int temp_idx = 0; 

        for (int idx = 0; idx < line_size; idx++)
        {
            if (p_str[temp_idx] == p_line[idx])
            {
                buf[temp_idx] = p_line[idx]; 
                temp_idx++; 
            }

            else
            {
                temp_idx = 0; 
            }

            if (0 == strncmp(buf, p_str, MAX_STR_LEN))
            {
                b_found_str = true; 
                break; 
            }
        }
    }

    return b_found_str; 
}

// End of file wgrep.c
