#include "shell.h"
/**
 * _strtok - separates strings using delimiters
 * @line: Pointer to the array received from getline.
 * @delim: Characters used to split the string into parts.
 * Return: A pointer to the created token.
 */
char *_strtok(char *line, char *delim)
{int j;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			break;
		}
		if (delim[j] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{	*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
