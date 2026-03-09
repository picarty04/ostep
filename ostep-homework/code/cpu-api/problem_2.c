// Program that opens a file and then calls fork() to create a new process. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_CHARS 25

int main (void)
{
    int status = EXIT_FAILURE;
    
    int file_descriptor = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);

    if (-1 == file_descriptor) // open failed. 
    {
        fprintf(stderr, "open failed\n"); 
        goto EXIT; 
    }

    int ret_val = fork();

    if (ret_val < 0) // fork failed. 
    {
        fprintf(stderr, "fork failed\n");
        goto EXIT;
    }

    else if (0 == ret_val) // Child Process. 
    {
        printf("File Descriptor: %i\n", file_descriptor);

        char buffer[MAX_CHARS];
        memset(buffer, '\0', MAX_CHARS);

        if (NULL == strncpy(buffer, "This is the child.\n", MAX_CHARS)) // strncpy failed. 
        {
            fprintf(stderr, "strncpy failed\n");
            goto EXIT; 
        }

        int written = write(file_descriptor, buffer, strnlen(buffer, MAX_CHARS)); 

        if (-1 == written) // write failed. 
        {
            fprintf(stderr, "write failed\n");
            goto EXIT; 
        }
    }

    else // Parent Process. 
    {
        if (-1 == wait(NULL)) // wait failed. 
        {
            fprintf(stderr, "wait failed\n"); 
            goto EXIT; 
        }

        printf("File Descriptor: %i\n", file_descriptor); 

        char buffer[MAX_CHARS];
        memset(buffer, '\0', MAX_CHARS);

        if (NULL == strncpy(buffer, "This is the parent.\n", MAX_CHARS)) // strncpy failed. 
        {
            fprintf(stderr, "strncpy failed\n");
            goto EXIT; 
        }

        int written = write(file_descriptor, buffer, strnlen(buffer, MAX_CHARS));

        if (-1 == written) // write failed. 
        {
            fprintf(stderr, "write failed\n"); 
            goto EXIT; 
        }
    }

    status = EXIT_SUCCESS; 

EXIT: 
    exit(status);  
}

// End of file problem_2.c
