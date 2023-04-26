#include "shell.h"

/**
 * shell_setenvir - A command that sets a environment variable.
 * @args: argument array
 * @i_stdin: input of stdin
 * @exit_status: exit status
 *
 * Return: Return 1 if use a function, 0 otherwise.*
 */

int shell_setenvir(char **args,  char *i_stdin, int *exit_status)
{
	int n_token = 0;
	(void)i_stdin;
	(void)exit_status;

	while (args[n_token] != NULL)
	{
		n_token++;
	}

	if (n_token == 3)
		setenv(args[1], args[2], 1);
	else if (n_token < 3)
		fprintf(stderr, "Try use \"setenv [KEY] [VALUE]\"\n");
	else
		fprintf(stderr, "Try use \"setenv [KEY] [VALUE]\"\n");

	return (1);
}
/**
 * shell_unsetenvir - A command that eliminates an environment variable.
 * @args: argument array
 * @i_stdin: input of stdin
 * @exit_status: exit status
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int shell_unsetenvir(char **args,  char *i_stdin, int *exit_status)
{
	int n_token = 0;
	(void)i_stdin;
	(void)exit_status;

	while (args[n_token] != NULL)
	{
		n_token++;
	}

	if (n_token == 2)
		unsetenv(args[1]);
	else
		fprintf(stderr, "Try use \"unsetenv [KEY]\"\n");

	return (1);
}

