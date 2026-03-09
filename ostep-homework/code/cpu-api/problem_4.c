// Program that implements exec(). 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CHARS 20

int main (int argc, char * argv[])
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

        int num_args = 3; 

        char ** lsargs = calloc(num_args, sizeof(char *));

        if (NULL == lsargs) // calloc failed. 
        {
            fprintf(stderr, "calloc failed\n"); 
            goto EXIT; 
        }
        
        lsargs[0] = strdup("/bin/ls"); 
        lsargs[1] = strdup("../cpu-intro");
        lsargs[2] = NULL; 

        if (NULL == lsargs[0]) // strdup failed. 
        {
            fprintf(stderr, "strdup failed\n"); 
            goto EXIT; 
        }

        else if (NULL == lsargs[1]) // strdup failed. 
        {
            fprintf(stderr, "strdup failed\n"); 
            goto EXIT; 
        }

        if (-1 == execvp(lsargs[0], lsargs)) // exec failed. 
        {
            fprintf(stderr, "exec failed\n");
            goto EXIT; 
        }

        printf("This should not print\n"); 
    }

    else // Parent Process. 
    {
        int wait_ret_val = wait(NULL);

        if (-1 == wait_ret_val) // wait failed.
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

// End of file problem_4.c
