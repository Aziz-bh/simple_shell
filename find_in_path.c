#include "shell.h"

/**
 * find_program - Find a program in the PATH directories.
 * @data: A pointer to the program's data.
 * 
 * This function searches for the specified program in the directories listed
 * in the PATH environment variable. If found, it updates the token with the
 * full path to the program.
 *
 * Return: 0 if success, an error code otherwise.
 */
int find_program(data_of_program *data)
{
    int i = 0, ret_code = 0;
    char **directories;

    if (!data->command_name)
        return (2);

    // If it's a full path or an executable in the same path, return result
    if (data->command_name[0] == '/' || data->command_name[0] == '.')
        return (check_file(data->command_name));

    free(data->tokens[0]);
    data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
    
    if (!data->tokens[0])
        return (2);

    directories = tokenize_path(data);

    if (!directories || !directories[0])
    {
        errno = 127;
        return (127);
    }

    for (i = 0; directories[i]; i++)
    {
        // Append the command_name to the path
        directories[i] = str_concat(directories[i], data->tokens[0]);
        ret_code = check_file(directories[i]);

        if (ret_code == 0 || ret_code == 126)
        {
            errno = 0;
            free(data->tokens[0]);
            data->tokens[0] = str_duplicate(directories[i]);
            free_array_of_pointers(directories);
            return (ret_code);
        }
    }

    free(data->tokens[0]);
    data->tokens[0] = NULL;
    free_array_of_pointers(directories);
    return (ret_code);
}

/**
 * tokenize_path - Tokenize the PATH environment variable into directories.
 * @data: A pointer to the program's data.
 * 
 * This function tokenizes the PATH environment variable into an array of
 * directory paths.
 *
 * Return: An array of path directories.
 */
char **tokenize_path(data_of_program *data)
{
    int i = 0;
    int counter_directories = 2;
    char **tokens = NULL;
    char *PATH;

    // Get the PATH value
    PATH = env_get_key("PATH", data);

    if ((PATH == NULL) || PATH[0] == '\0')
    {
        return (NULL); // PATH not found
    }

    PATH = str_duplicate(PATH);

    // Find the number of directories in the PATH
    for (i = 0; PATH[i]; i++)
    {
        if (PATH[i] == ':')
            counter_directories++;
    }

    // Reserve space for the array of pointers
    tokens = malloc(sizeof(char *) * counter_directories);

    // Tokenize and duplicate each token of path
    i = 0;
    tokens[i] = str_duplicate(_strtok(PATH, ":"));
    
    while (tokens[i++])
    {
        tokens[i] = str_duplicate(_strtok(NULL, ":"));
    }

    free(PATH);
    PATH = NULL;
    return (tokens);
}

/**
 * check_file - Check if a file exists, is not a directory, and has execute permissions.
 * @full_path: Pointer to the full file name.
 * 
 * This function checks if a file exists, is not a directory, and has execute permissions.
 *
 * Return: 0 on success, or an error code if it doesn't exist or doesn't meet the criteria.
 */
int check_file(char *full_path)
{
    struct stat sb;

    if (stat(full_path, &sb) != -1)
    {
        if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
        {
            errno = 126;
            return (126); // File is a directory or lacks execute permissions
        }
        
        return (0); // File exists and is executable
    }

    // File does not exist
    errno = 127;
    return (127);
}
