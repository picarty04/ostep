// Program that reads a file specified by the user and prints its contents. 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LINE 200

int main (int argc, char * argv[])
{
    int status = 1; 

    if (argc < 2)
    {
        status = 0;
        goto EXIT; 
    }

    for (int idx = 1; idx < argc; idx++)
    {
        if (NULL == argv[idx])
        {
            fprintf(stderr, "wcat: cannot open file\n"); 
            goto EXIT; 
        }
    }

    // Open the file, print each line, and close the file. 
    for (int idx = 1; idx < argc; idx++)
    {
        FILE * p_file = fopen(argv[idx], "r"); 

        if (NULL == p_file)
        {
            printf("wcat: cannot open file\n"); 
            goto EXIT; 
        }

        char buffer[LINE]; 
        memset(buffer, '\0', LINE); 

        char * p_line = fgets(buffer, LINE, p_file); 

        while (NULL != p_line)
        {
            printf("%s", p_line); 

            memset(buffer, '\0', LINE); 
            p_line = fgets(buffer, LINE, p_file); 
        }

        if (-1 == fclose(p_file))
        {
            goto EXIT; 
        }
    }

    status = 0; 

EXIT: 
    return status; 
}

// End of file wcat.c
