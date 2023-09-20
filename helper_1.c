#include "shell.h"
/**
 * free_recurrent_data - frees the fields needed for each loop iteration
 * @data: struct containing the program's data
 * Return: void
 */
void free_recurrent_data(data_of_program *data)
{if (data->tokens)
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
 * free_all_data - frees all fields of the data struct
 * @data: struct containing the program's data
 * Return: Nothing
 */
void free_all_data(data_of_program *data)
{if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointer in an array of pointers and the
 * array itself
 * @array: array of pointers
 * Return: nothing
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
