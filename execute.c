#include "shell.h"

/**
 * execute - Execute a command with its full path variables.
 * @data: Pointer to the program's data structure.
 * 
 * Return: If successful, return zero; otherwise, return -1.
 */
int execute(data_of_program *data)
{
    int retval = 0, status;
    pid_t child_pid;

    /* Check if the program is a built-in command. */
    retval = builtins_list(data);
    if (retval != -1) /* If the program was found in built-ins. */
        return (retval);

    /* Check if the program exists in the file system. */
    retval = find_program(data);
    if (retval)
    { /* If the program was not found. */
        return (retval);
    }
    else
    { /* If the program was found. */
        child_pid = fork(); /* Create a child process. */
        if (child_pid == -1)
        { /* If the fork call failed. */
            perror(data->command_name);
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        { /* If this is the child process, execute the program. */
            retval = execve(data->tokens[0], data->tokens, data->env);
            if (retval == -1)
            { /* If there was an error with execve. */
                perror(data->command_name);
                exit(EXIT_FAILURE);
            }
        }
        else
        { /* If this is the parent process, wait and check the exit status of the child. */
            wait(&status);
            if (WIFEXITED(status))
                errno = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                errno = 128 + WTERMSIG(status);
        }
    }
    return (0);
}
