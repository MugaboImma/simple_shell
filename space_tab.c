#include "shell.h"

/**
 * space_validate - A function that validates spaces, tabs and line break
 *
 * @i_stdin: input read of stdin
 *
 *
 * Return: 0 if not find spaces, tabs or line break
 * or 1 if find only spaces, tabs or line break
 */

int space_validate(char *i_stdin)
{
	int i = 0, flag = 1, n = 0;

	n = strlen(i_stdin);

	while (i_stdin[i] == ' ' || i_stdin[i] == '\n' || i_stdin[i] == '\t')
		i++;

	if (i != n)
		flag = 0;
	return (flag);
}
