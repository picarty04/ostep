// Program that calls fork().

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void)
{
    int status = EXIT_SUCCESS; 
    int var_x = 100;

    int ret_val = fork();

    if (ret_val < 0) // Fork Failed. 
    {
        fprintf(stderr, "fork failed\n"); 
        status = EXIT_FAILURE;   
        goto EXIT; 
    }

    else if (0 == ret_val) // Child Process. 
    {
        var_x = 50;

        printf("Value of the variable x in the child process: %i\n", var_x); 
    }

    else // Parent Process.  
    {
        var_x = 75; 

        printf("Value of the variable x in the parent process: %i\n", var_x); 
    }

EXIT: 
    exit(status); 
}

// End of file problem_1.c
