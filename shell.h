#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

/* Global environment */
extern char **environ;

/**
 * struct builtin_str - A struct type that defines a builtin string command
 * @name_builtin: The name of the builtin command
 * @func: The function to point to the builtin command's function
 */

typedef struct builtin_str
{
	char *name_builtin;
	int (*func)(char **argv, char *, int *);
} builtin_t;

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int shell_execute(char **args, char **argv, int *exit_status);
char *str_tok(char *buffer_str, char *delim);
char *str_cat(char *str1, char *str2);
int shell_exit(char **args, char *i_stdin, int *status_exit);
int shell_builtin(char **args, char *i_stdin, char **argv, int *exit_status);
int shell_environ(char **args, char *i_stdin, int *status_exit);
int shell_cd(char **args, char *i_stdin, int *status_exit);
int shell_setenvir(char **args, char *i_stdin, int *status_exit);
int shell_unsetenvir(char **args, char *i_stdin, int *status_exit);
char *input_validate(char **args, char **argv);
char *get_envir(const char *var);
void sigint_handler(int n_sign);
int space_validate(char *i_stdin);
char **get_token_path(char *input);
char **shell_tokens(char *input);
#endif /* SHELL_H */

