// Program that implements fork() and wait(). 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void)
{
    int status = EXIT_FAILURE;

    int ret_val = fork();

    if (ret_val < 0) // fork failed.
    {
        fprintf(stderr, "fork failed\n"); 
        goto EXIT; 
    }

    else if (0 == ret_val) // Child Process. 
    {
        printf("Child says hello\n");
    }

    else // Parent Process. 
    {
        int ret_val_wait = wait(NULL);

        if (-1 == ret_val_wait) // wait failed. 
        {
            fprintf(stderr, "wait failed\n");
            goto EXIT; 
        }

        printf("Parent says hello\n"); 
    }

    status = EXIT_SUCCESS;

EXIT: 
    exit(status); 
}

// End of file problem_3.c
