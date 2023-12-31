#include "shell.h"

/**
 * _print - writes an array of characters to standard output
 * @string: pointer to the array of characters
 * Return: the number of bytes written or -1 on error, with errno set appropriately.
 */

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}
/**
 * _printe - writes an array of characters to the standard error
 * @string: pointer to the array of characters
 * Return: the number of bytes written or -1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - writes an array of characters to the standard error
 * @data: a pointer to the program's data
 * @errorcode: error code to print
 * Return: the number of bytes written or -1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_error(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->tokens[0]);
		if (errorcode == 2)
			_printe(": this number is Illegal:");
		else
			_printe(": impossible to dc to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": doesn't exist\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
