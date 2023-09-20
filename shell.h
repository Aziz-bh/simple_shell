#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

#include "example.h" /* for msg help and prompt */


/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;






void tokenize(data_of_program *data);

char *_strtok(char *line, char *delim);

int execute(data_of_program *data);

int builtins_list(data_of_program *data);

char **tokenize_path(data_of_program *data);

int find_program(data_of_program *data);


void free_array_of_pointers(char **directories);

void free_recurrent_data(data_of_program *data);

void free_all_data(data_of_program *data);



int builtin_exit(data_of_program *data);


int builtin_cd(data_of_program *data);


int set_work_directory(data_of_program *data, char *new_dir);

int builtin_help(data_of_program *data);

int builtin_alias(data_of_program *data);



int builtin_env(data_of_program *data);

int builtin_set_env(data_of_program *data);

int builtin_unset_env(data_of_program *data);



int aliasprint(data_of_program *data, char *alias);

char *get_alias(data_of_program *data, char *alias);

int set_alias(char *alias_string, data_of_program *data);
char *env_get_key(char *name, data_of_program *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Remove a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* prints the current environ */
void print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _printe(char *string);

/* Prints a string in the standar error */
int _print_error(int errorcode, data_of_program *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);


void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

void sisifo(char *prompt, data_of_program *data);

void handle_ctrl_c(int opr UNUSED);


int _getline(data_of_program *data);

int check_logic_ops(char *array_commands[], int i, char array_operators[]);


void expand_variables(data_of_program *data);

void expand_alias(data_of_program *data);
int buffer_add(char *buffer, char *str_to_add);


#endif /* SHELL_H */
