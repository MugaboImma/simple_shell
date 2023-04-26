#include "shell.h"
/**
 * get_token_path - A function that is used to tokenizer the path
 *
 * @input: the path to be tokenize
 *
 * Return: A double pointer to the tokens of path
 */

char **get_token_path(char *input)
{
	int data_buf1 = 64, data_buf2 = 0, loc = 0;
	char **new_token = malloc(data_buf1 * sizeof(char *));
	char **cp_token1;
	char delim[] = ":";

	if (!new_token)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	while ((new_token[loc] = strtok(input, delim)) != NULL)
	{
		loc++;

		if (loc >= data_buf1)
		{
			data_buf2 = data_buf1 * 2;
			cp_token1 = new_token;
			new_token = _realloc(new_token, data_buf1, data_buf2 * sizeof(char *));

			if (!new_token)
			{
				free(cp_token1);
				free(new_token);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		input = NULL;
	}
	new_token[loc] = NULL;
	return (new_token);
}

/**
 * input_validate - A function that validates if path exists
 *
 * @args: arguments for command
 * @argv: Array that contains the string values
 *
 * Return: new arguments with complete path
 */

char *input_validate(char **args, char **argv)
{
	char *new_args, *init, *slash_arg = "/";
	char **token_path, hold_env[1024];
	int i = 0;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		new_args = args[0];
		if ((access(new_args, F_OK) == -1))
		{
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
			return ("Fail access");
		}
	}
	else
	{
		strcpy(hold_env, getenv("PATH"));
		token_path = get_token_path(hold_env);
		while (token_path[i])
		{
			init = str_cat(slash_arg, args[0]);
			new_args = str_cat(token_path[i], init);

			if ((access(new_args, F_OK) == -1))
			{
				free(new_args);
				free(init);
			}
			else
			{
				free(token_path);
				free(init);
				return (new_args);
			}
			i++;
		}
		free(token_path);
		fprintf(stderr, "%s: No such file or directory\n", argv[0]);
		return ("Fail access");
	}
	return (new_args);
}

/**
 * shell_execute - A function that executes the commands in a child process
 *
 * @args: the tokens that were previously separated with delimiters
 * @argv: argument vector
 * @exit_status: The exit status
 *
 * Return: Always 1 (success).
 *
 */

int shell_execute(char **args, char **argv, int *exit_status)
{
	pid_t pid;
	int status;
	char *new_args;

	new_args = input_validate(args, argv);

	if (strcmp(new_args, "Fail access") == 0)
		return (1);
	pid = fork();

	if (pid == 0)
	{
		if (execve(new_args, args, environ) == -1)
		{
			perror("execve fail");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error forking");
		free(new_args);
		return (1);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
			*exit_status = WEXITSTATUS(status);
		if (args[0][0] != '/' && args[0][0] != '.')
			free(new_args);
		return (1);
	}
	return (1);
}

/**
 * shell_tokens - A function that splits commands with delimiters
 * @input: string that comes from the input
 *
 * Return: A double pointer to the tokens
 */
char **shell_tokens(char *input)
{
	int data_buf1 = 64, data_buf2 = 0, loc = 0;
	char **token = malloc(data_buf1 * sizeof(char *));
	char **cp_token;
	char delim[] = " \n\t";

	if (!token)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	while ((token[loc] = strtok(input, delim)) != NULL)
	{
		loc++;

		if (loc >= data_buf1)
		{
			data_buf2 = data_buf1 * 2;
			cp_token = token;
			token = _realloc(token, data_buf1, data_buf2 * sizeof(char *));

			if (!token)
			{
				free(cp_token);
				free(token);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		input = NULL;
	}
	token[loc] = NULL;
	return (token);
}
