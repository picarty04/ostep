// Program that closes stdout. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char * argv[])
{
    int status = EXIT_FAILURE; 

    int fork_ret_val = fork(); 

    if (fork_ret_val < 0) // fork failed. 
    {
        fprintf(stderr, "fork failed\n"); 
        goto EXIT; 
    }

    else if (0 == fork_ret_val)
    {
        // This prints. 
        printf("This is the child process before closing stdout\n"); 

        if (-1 == close(STDOUT_FILENO)) // close failed. 
        {
            fprintf(stderr, "close failed\n"); 
            goto EXIT; 
        }

        // This does not print. 
        printf("This is the child process after closing\n"); 
    }

    else
    {
        if (-1 == wait(NULL)) // wait failed. 
        {
            fprintf(stderr, "wait failed\n"); 
            goto EXIT; 
        }

        printf("Parent Process\n"); 
    }

    status = EXIT_SUCCESS;

EXIT: 
    exit(status); 
}

// End of file problem_7.c
