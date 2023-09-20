# Shell Project

## Objectives

### This project has three main objectives:

- To provide a hands-on experience with the Linux programming environment.

- To explore the concepts of process creation, management, and destruction.

- To gain familiarity with fundamental shell functionalities.

## Overview

- In this project, we have implemented a command line interpreter, commonly known as a shell. The shell follows this basic workflow: when a user enters a command in response to its prompt, the shell creates a child process to execute the entered command and then waits for more user input when the execution is complete.

- The shells we've developed are similar to the everyday Unix shell you use. You can identify your current shell by running the command "echo $SHELL" at a prompt. You may consult the manual pages for 'csh' or your shell of choice (probably tcsh, bash, or, for those with unique preferences, zsh or ksh) to explore advanced functionalities. However, for this project, we've focused on creating a simple shell with basic features.

## Program Specification

### Basic Shell

#### Simple Shell 0.1

- Develop a UNIX command line interpreter.

    - Usage: simple-shell
    - Your Shell should:

        - Display a prompt and wait for the user to enter a command. Each command line ends with a new line.
        - Redisplay the prompt after executing each command.
        - Only handle simple command lines with no semicolons, pipes, redirections, or advanced features.
        - Process command lines consisting of a single word; no arguments are passed to programs.
        - Print an error message and display the prompt again if an executable cannot be found.
        - Handle errors gracefully.
        - Address the "end of file" condition (Ctrl+D).
    - You are not required to:

        - Use the PATH environment variable.
        - Implement built-in commands.
        - Handle special characters such as `", ', , \, *, &, #`.
        - Implement cursor movement.
        - Process commands with arguments.

#### Simple Shell 0.2

- Simple Shell 0.1 plus:

    - Handle command lines with arguments.

#### Simple Shell 0.3

- Simple Shell 0.2 plus:

    - Manage the PATH environment variable.
    - Avoid calling fork if the command does not exist.

#### Simple Shell 0.4

- Simple Shell 0.3 plus:

    - Implement the exit built-in command for exiting the shell.
    - Usage: exit
    - You do not need to handle any arguments for the built-in exit.

#### Simple Shell 1.0

- Simple Shell 0.4 plus:

    - Implement the env built-in command to print the current environment.

#### Simple Shell 0.1.1

- Simple Shell 0.1 plus:

    - Implement your own getline function.
    - Use a buffer to read multiple characters at once, minimizing read system calls.
    - Utilize static variables.
    - You are prohibited from using getline.
    - Cursor movement is not required.

#### Simple Shell 0.2.1

- Simple Shell 0.2 plus:

    - You are prohibited from using strtok.

#### Simple Shell 0.4.1

- Simple Shell 0.4 plus:

    - Handle arguments for the built-in exit command.
    - Usage: exit status, where status is an integer used to exit the shell.

#### Built-in Commands: setenv and unsetenv

- Simple Shell 1.0 plus:

- Implement the setenv and unsetenv built-in commands.

##### setenv

- Initialize a new environment variable or modify an existing one.
- Command syntax: setenv VARIABLE VALUE
- Provide appropriate error messages on failure.

##### unsetenv

- Remove an environment variable.
- Command syntax: unsetenv VARIABLE
- Provide appropriate error messages on failure.

#### Built-in Command: cd

- Simple Shell 1.0 plus:

- Implement the built-in command cd, which changes the current directory of the process.
- Command syntax: cd [DIRECTORY]
- If no argument is given to cd, interpret it as `cd $HOME`.
- Handle the `cd -` command.
- Update the environment variable PWD when changing directories.
- Reference: `man chdir`, `man getcwd`

#### Command Separator: ;

- Simple Shell 1.0 plus:

- Handle the command separator `;`.

#### Logical Operators: && and ||

- Simple Shell 1.0 plus:

- Handle the `&&` and `||` shell logical operators.

#### Built-in Command: alias

- Simple Shell 1.0 plus:

- Implement the alias built-in command.
- Usage: alias [name[='value'] ...]
- alias: Print a list of all aliases, one per line, in the form name='value'.
- alias name [name2 ...]: Print the aliases name, name2, etc., one per line, in the form name='value'.
- alias name='value' [...]: Define an alias for each name with the given value. Replace the value if name is already an alias.

#### Comments

- Simple Shell 1.0 plus:

- Handle comments (`#`).

#### File as Input

- Simple Shell 1.0 plus:

- Usage: simple_shell [filename]
- Your shell can accept a file as a command line argument.
- The file contains all the commands that your shell should run before exiting.
- Each line in the file represents one command.
- In this mode, the shell should not print a prompt or read from stdin.
