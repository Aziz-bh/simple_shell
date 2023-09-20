#include "shell.h"
/**
 * main - initializes the program's variables
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: environment variables received from the command line
 * Return: zero on success.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";
	inicialize_data(data, argc, argv, env);
	signal(SIGINT, handle_ctrl_c);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - prints the prompt on a new line
 * when the SIGINT signal (ctrl + c) is sent to the program
 * @UNUSED: unused parameter in the function prototype
 */

void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_data - initializes the struct with program information
 * @data: pointer to the data structure
 * @argv: array of arguments passed to the program's execution
 * @env: environment variables passed to the program's execution
 * @argc: number of values received from the command line
 */

void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;
	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * sisifo - an infinite loop that displays the prompt
 * @prompt: the prompt to be printed
 * @data: a data structure used in the infinite loop
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
