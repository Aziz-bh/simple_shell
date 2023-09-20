#ifndef HELPERS_H
#define HELPERS_H

#define PROMPT_MSG "$" 

#define UNUSED __attribute__((unused))

#define BUFFER_SIZE 1024

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change directory.\n\n"\
"	If no  interpreted\n"\
"	as cd $HOME.\n"\
"	(cd -), the command will be interpreted\n"\
"	$OLDPWD.\n\n"
#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"Exit of the simple-shell.\n\n"\
"If N is omitted, the exit status\n"\
"last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	ronment.\n\n"\
"	 a complete list of enviroment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Chvironment variable.\n\n"\
"	initient variable, or modify an existing one\n"\
"	When trect numbers of arguments print error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsedeletes one variable from the environment.\n\n"\
"	Wen ther of arguments print error message.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	 about builtin commands.\n\n"\
"	of builtin commands.  If BUILTIN_NAME is\n"\
"etailed help on all commands matching BUILTIN_NAME,\n"\
"ics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
