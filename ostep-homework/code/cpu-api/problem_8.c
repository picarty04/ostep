// Program that uses the pipe system call. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CHARS 25

int main (int argc, char * argv[])
{
    int status = EXIT_FAILURE;

    if ((2 != argc) || (NULL == argv[1]))
    {
        fprintf(stderr, "Usage: %s \"Hello, World\"\n", argv[0]); 
        goto EXIT; 
    }

    int count = strnlen(argv[1], MAX_CHARS); 

    if (MAX_CHARS == count)
    {
        fprintf(stderr, "Max String Length: %i Characters\n", MAX_CHARS - 1);
        goto EXIT; 
    }

    int cpid_1 = fork(); 

    if (-1 == cpid_1)
    {
        fprintf(stderr, "fork failed\n"); 
        goto EXIT; 
    }

    else if (0 == cpid_1) // Child Process #1. 
    {
        printf("Child Process: %i\n", getpid()); 

        int pipefd[2]; 
        memset(pipefd, '\0', 2 * sizeof(int)); 

        if (-1 == pipe(pipefd))
        {
            fprintf(stderr, "pipe failed\n"); 
            goto EXIT; 
        }

        int cpid_2 = fork();

        if (-1 == cpid_2)
        {
            fprintf(stderr, "fork failed\n"); 
            goto EXIT; 
        }

        else if (0 == cpid_2) // Child Process #2. 
        {
            // Child reads from pipe. 
            if (-1 == close(pipefd[1])) // Close write end. 
            {
                fprintf(stderr, "close failed\n"); 
                goto EXIT; 
            }

            char buffer[MAX_CHARS];
            memset(buffer, '\0', MAX_CHARS); 
            
            if (count != read(pipefd[0], &buffer, count)) // Read from read end. 
            {
                fprintf(stderr, "read failed\n");
                goto EXIT; 
            }

            printf("Child Process (%i): %s\n", getpid(), buffer); 

            if (-1 == close(pipefd[0])) // Close read end. 
            {
                fprintf(stderr, "close failed\n");
                goto EXIT; 
            }
        }

        else // Child Process #1 (aka Parent of Child Process #2). 
        {
            // Parent writes to pipe. 
            if (-1 == close(pipefd[0])) // Close read end. 
            {
                fprintf(stderr, "close failed\n"); 
                goto EXIT; 
            }

            if (count != write(pipefd[1], argv[1], count)) // Write to write end. 
            {
                fprintf(stderr, "write failed\n"); 
                goto EXIT; 
            }

            if (-1 == close(pipefd[1])) // Close write end. 
            {
                fprintf(stderr, "close failed\n");
                goto EXIT; 
            }

            if (-1 == wait(NULL)) // Wait for child to execute. 
            {
                fprintf(stderr, "wait failed\n");
                goto EXIT; 
            }
        }
    }

    else // Parent Process. 
    {
        if (-1 == wait(NULL))
        {
            fprintf(stderr, "wait failed\n"); 
            goto EXIT; 
        }
        
        printf("Parent Process: %i\n", getpid()); 
    }

    status = EXIT_SUCCESS; 

EXIT: 
    exit(status); 
}