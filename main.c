#include "shell.h"

void sig_handler(int sig);
int execute(char **args, char **front);

/**
 * sig_handler - Handles the SIGINT signal (Ctrl+C) to print a new prompt.
 * @sig: The signal number.
 */
void sig_handler(int sig)
{
    char *new_prompt = "\n$ ";

    (void)sig;  // Avoid "unused parameter" warning
    signal(SIGINT, sig_handler); // Re-establish the signal handler
    write(STDIN_FILENO, new_prompt, 3); // Print a new prompt
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         Otherwise - The exit value of the last executed command.
 */
int execute(char **args, char **front)
{
    pid_t child_pid;
    int status, flag = 0, ret = 0;
    char *command = args[0];

    // Check if the command is an absolute or relative path
    if (command[0] != '/' && command[0] != '.')
    {
        flag = 1;
        command = get_location(command);
    }

    if (!command || (access(command, F_OK) == -1))
    {
        // Handle command not found or permission denied errors
        if (errno == EACCES)
            ret = create_error(args, 126);
        else
            ret = create_error(args, 127);
    }
    else
    {
        // Create a child process and execute the command
        child_pid = fork();
        if (child_pid == -1)
        {
            if (flag)
                free(command);
            perror("Error child:");
            return 1;
        }
        if (child_pid == 0)
        {
            execve(command, args, environ);
            if (errno == EACCES)
                ret = create_error(args, 126);
            free_env();
            free_args(args, front);
            free_alias_list(aliases);
            _exit(ret);
        }
        else
        {
            wait(&status);
            ret = WEXITSTATUS(status);
        }
    }

    if (flag)
        free(command);
    return ret;
}

/**
 * main - The main function of the simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
    int ret = 0, retn;
    int *exe_ret = &retn;
    char *prompt = "$ ", *new_line = "\n";

    name = argv[0];
    hist = 1;
    aliases = NULL;
    signal(SIGINT, sig_handler); // Set up the signal handler for SIGINT (Ctrl+C)

    *exe_ret = 0;
    environ = _copyenv();
    if (!environ)
        exit(-100);

    if (argc != 1)
    {
        // If there are arguments, process a file and exit
        ret = proc_file_commands(argv[1], exe_ret);
        free_env();
        free_alias_list(aliases);
        return *exe_ret;
    }

    if (!isatty(STDIN_FILENO))
    {
        // If not running in interactive mode, process commands from input
        while (ret != END_OF_FILE && ret != EXIT)
            ret = handle_args(exe_ret);
        free_env();
        free_alias_list(aliases);
        return *exe_ret;
    }

    while (1)
    {
        // Interactive mode: continuously prompt for and execute commands
        write(STDOUT_FILENO, prompt, 2);
        ret = handle_args(exe_ret);
        if (ret == END_OF_FILE || ret == EXIT)
        {
            if (ret == END_OF_FILE)
                write(STDOUT_FILENO, new_line, 1);
            free_env();
            free_alias_list(aliases);
            exit(*exe_ret);
        }
    }

    free_env();
    free_alias_list(aliases);
    return *exe_ret;
}
