#include "shell.h"

/**
 * shell_cd - A function that changes directory
 * @args: argument array
 * @i_stdin: input of stdin
 * @exit_status: exit status
 *
 * Return: 1 (success)
 */

int shell_cd(char **args, char *i_stdin, int *exit_status)
{
	int status;
	char str[128];
	(void)i_stdin;
	(void)exit_status;
	getcwd(str, sizeof(str));

	if (args[1] == NULL)
		status = chdir(getenv("HOME"));
	else if (strcmp(args[1], "-") == 0)
		status = chdir(getenv("OLDPWD"));
	else if (strcmp(args[1], "~") == 0)
		status = chdir(getenv("HOME"));
	else
		status = chdir(args[1]);

	if (status == -1)
		perror("cd has an error");
	setenv("OLDPWD", str, 1);
	setenv("PWD", getcwd(str, sizeof(str)), 1);
	return (1);
}

/**
 * shell_environ - A function that prints enviromental
 *
 * @args: arguments
 * @i_stdin: input of stdin
 * @exit_status: exit status
 *
 * Return: Always 1 (success)
 */

int shell_environ(char **args, char *i_stdin, int *exit_status)
{
	int i = 0;
	(void)args;
	(void)i_stdin;
	(void)exit_status;

	if (environ[i] == NULL)
	{
		printf("%s", "The builtin environ is empty");
		return (1);
	}
	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
	return (1);
}

/**
 * shell_builtin - A function that executes a correct builtin command
 * @args: arguments
 * @i_stdin: input of stdin
 * @argv: arg vector
 * @e_status: exit status
 *
 * Return: execute function of the chosen builtin command
 * or return shell_execute
 */

int shell_builtin(char **args, char *i_stdin, char **argv, int *e_status)
{
	int i = 0;
	builtin_t options[] = {
		{"exit", shell_exit},
		{"environ", shell_environ},
		{"cd", shell_cd},
		{"setenvir", shell_setenvir},
		{"unsetenvir", shell_unsetenvir},
		{NULL, NULL}
	};

	while (options[i].name_builtin)
	{
		if (strcmp(options[i].name_builtin, args[0]) == 0)
		{
			return ((int)((*options[i].func)(args, i_stdin, e_status)));
		}
		i++;
	}
	return (shell_execute(args, argv, e_status));
}

/**
 * shell_exit - A function that exit builtin command
 *
 * @args: arguments
 * @i_stdin: input of stdin
 * @exit_status: exit status
 *
 * Return: Exit success
 */

int shell_exit(char **args, char *i_stdin, int *exit_status)
{
	int exit_output = 0;
	(void)args;
	(void)i_stdin;
	(void)exit_status;

	if (args[1] == NULL)
	{
		free(args);
		free(i_stdin);
		exit(*exit_status);
	}

	if (args[2] != NULL)
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (0);
	}
	exit_output = atoi(args[1]);
	free(args);
	free(i_stdin);
	exit(exit_output);
}
