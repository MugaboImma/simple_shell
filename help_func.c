
#include "shell.h"

/**
 * sigint_handler - A function that handles SIGINT (CTRL + C)
 * @n_sign: The signal number caught by signal, 2 for SIGINIT
 *
 * Return: void
 */

void sigint_handler(int n_sign)
{
	if (n_sign == SIGINT)
	{
		write(2, "\n#Shell$ ", 11);
	}
}

/**
 * str_cat - A funcion that concatenates two strings
 * @str1: array number 1
 * @str2: array number 2
 *
 * Return: pointer to two strings concatenates
 */

char *str_cat(char *str1, char *str2)
{
	char *str;
	unsigned int n;
	unsigned int m;
	unsigned int l;

	if (str1 == NULL)
		str1 = "";

	if (str2 == NULL)
		str2 = "";
	for (n = 0; str1[n] != '\0'; n++)
		continue;
	for (m = 0; str2[m] != '\0'; m++)
		continue;
	m = m + 1;
	str = malloc((n + m) * sizeof(char));

	if (str == NULL)
		return (0);

	for (l = 0; l < (n + m) ; l++)
	{
		if (l < n)
			str[l] = str1[l];
		if (l >= n)
			str[l] = str2[l - n];
	}
	return (str);
}

/**
 * _getenvir - S function that finds a specific variable name
 * @var: environment variable
 *
 * Return: pointer to the corresponding value string
 */

char *_getenvir(char *var)
{
	int n = 0;

	while (environ[n])
	{
		if (strcmp(environ[n], var) == 0)
			return (environ[n]);
		++n;
	}
	return (NULL);
}
