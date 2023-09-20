#include "shell.h"

/**
 * free_recurrent_data - Free the fields needed for each loop iteration.
 * @data: A struct containing the program's data.
 * 
 * This function frees memory for the data fields that need to be reset or
 * cleared at the end of each loop iteration.
 *
 * Return: Nothing.
 */
void free_recurrent_data(data_of_program *data)
{
    if (data->tokens)
        free_array_of_pointers(data->tokens);
    if (data->input_line)
        free(data->input_line);
    if (data->command_name)
        free(data->command_name);

    data->input_line = NULL;
    data->command_name = NULL;
    data->tokens = NULL;
}

/**
 * free_all_data - Free all fields of the program's data.
 * @data: A struct containing the program's data.
 * 
 * This function frees memory for all fields within the program's data struct,
 * including tokens, input_line, command_name, env, and alias_list.
 *
 * Return: Nothing.
 */
void free_all_data(data_of_program *data)
{
    if (data->file_descriptor != 0)
    {
        if (close(data->file_descriptor))
            perror(data->program_name);
    }
    free_recurrent_data(data);
    free_array_of_pointers(data->env);
    free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - Free an array of pointers and each individual pointer.
 * @array: An array of pointers.
 * 
 * This function frees memory for an array of pointers and each individual
 * pointer within the array.
 *
 * Return: Nothing.
 */
void free_array_of_pointers(char **array)
{
    int i;

    if (array != NULL)
    {
        for (i = 0; array[i]; i++)
            free(array[i]);

        free(array);
        array = NULL;
    }
}
