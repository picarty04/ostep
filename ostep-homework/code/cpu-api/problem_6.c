// Program that uses waitpid(). 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void)
{
    int status = EXIT_FAILURE;

    int fork_ret_val = fork();

    if (fork_ret_val < 0) // fork failed.
    {
        fprintf(stderr, "fork failed\n");
        goto EXIT; 
    }

    else if (0 == fork_ret_val) // Child Process. 
    {
        printf("Child Process\n"); 
    }

    else // Parent Process. 
    {
        int pid = getpid(); 

        // waitpid is useful when we want to wait for a specific child process. 
        if (-1 == waitpid(pid + 1, NULL, WNOHANG)) // waitpid failed.
        {
            fprintf(stderr, "waitpid failed\n"); 
            goto EXIT;
        }

        printf("Parent Process\n");
    }

    status = EXIT_SUCCESS;

EXIT: 
    exit(status); 
}

// End of file problem_6.c
