// Program that uses wait(). 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void)
{
    int status = EXIT_FAILURE; 

    int fork_ret_val = fork(); 

    if (fork_ret_val < 0) // Fork Failed. 
    {
        fprintf(stderr, "fork failed\n"); 
        goto EXIT; 
    }

    else if (0 == fork_ret_val) // Child Process. 
    {
        // wait() fails in the child process unless it has a child of its own. 
        printf("Child Process: %i.\n", getpid());
    }

    else // Parent Process. 
    {
        int wait_ret_val = wait(NULL); // Returns the pid of the terminated child. 
        
        if (-1 == wait_ret_val) // Wait Failed
        {
            fprintf(stderr, "wait failed\n"); 
            goto EXIT; 
        }

        printf("Parent Process PID: %i. Wait Ret Val: %i\n", getpid(), wait_ret_val); 
    }

    status = EXIT_SUCCESS; 

EXIT: 
    exit(status); 
}

// End of file problem_5.c
