#include "shell.h"

/**
 * builtin_env - Display the environment where the shell runs.
 * @data: Pointer to the program's data structure.
 * 
 * Return: 0 if successful, or an error code if specified in the arguments.
 */
int builtin_env(data_of_program *data)
{
    int i;
    char cpname[50] = {'\0'};
    char *var_copy = NULL;

    /* If no arguments are provided. */
    if (data->tokens[1] == NULL)
        print_environ(data);
    else
    {
        for (i = 0; data->tokens[1][i]; i++)
        {
            /* Check if there is a '=' character. */
            if (data->tokens[1][i] == '=')
            {
                /* Check if there is a variable with the same name and temporarily change its value. */
                var_copy = str_duplicate(env_get_key(cpname, data));
                if (var_copy != NULL)
                    env_set_key(cpname, data->tokens[1] + i + 1, data);

                /* Print the environment. */
                print_environ(data);

                if (env_get_key(cpname, data) == NULL)
                {
                    /* Print the variable if it does not exist in the environment. */
                    _print(data->tokens[1]);
                    _print("\n");
                }
                else
                {
                    /* Restore the old value of the variable. */
                    env_set_key(cpname, var_copy, data);
                    free(var_copy);
                }
                return (0);
            }
            cpname[i] = data->tokens[1][i];
        }
        /* Handle the case when no '=' character is found. */
        errno = 2;
        perror(data->command_name);
        errno = 127;
    }
    return (0);
}

/**
 * builtin_set_env - Set or update an environment variable.
 * @data: Pointer to the program's data structure.
 * 
 * Return: 0 if successful, or an error code if specified in the arguments.
 */
int builtin_set_env(data_of_program *data)
{
    /* Validate arguments. */
    if (data->tokens[1] == NULL || data->tokens[2] == NULL)
        return (0);

    if (data->tokens[3] != NULL)
    {
        /* Handle the case when too many arguments are provided. */
        errno = E2BIG;
        perror(data->command_name);
        return (5);
    }

    /* Set or update the environment variable. */
    env_set_key(data->tokens[1], data->tokens[2], data);

    return (0);
}

/**
 * builtin_unset_env - Unset or remove an environment variable.
 * @data: Pointer to the program's data structure.
 * 
 * Return: 0 if successful, or an error code if specified in the arguments.
 */
int builtin_unset_env(data_of_program *data)
{
    /* Validate arguments. */
    if (data->tokens[1] == NULL)
        return (0);

    if (data->tokens[2] != NULL)
    {
        /* Handle the case when too many arguments are provided. */
        errno = E2BIG;
        perror(data->command_name);
        return (5);
    }

    /* Unset or remove the environment variable. */
    env_remove_key(data->tokens[1], data);

    return (0);
}
