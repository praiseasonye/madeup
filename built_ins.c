#include "main.h"

/**
 * env_b - Prints all the environmental variables in the current shell.
 *
 *
 * @line: A string representing the input from the user.
 *
 */


void env_b(__attribute__((unused))char *line)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}


/**
 * cd_b - Changes the current working directory to the parameter passed to cd.
 *
 *
 * if no parameter is passed it will change directory to HOME.
 *
 *
 * @line: A string representing the input from the user.
 *
 */


void cd_b(char *line)
{
	int index;
	int token_count;
	char **param_array;
	const char *delim = "\n\t ";

	token_count = 0;
	param_array = token_interface(line, delim, token_count);
	if (param_array[0] == NULL)
	{
		single_free(2, param_array, line);
		return;
	}
	if (param_array[1] == NULL)
	{
		index = find_path("HOME");
		chdir((environ[index]) + 5);
	}
	else if (_strcmp(param_array[1], "-") == 0)
		print_str(param_array[1], 0);

	else
		chdir(param_array[1]);
	double_free(param_array);
}


/**
 * myexit - exits the shell
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: exits with a give exit status
 * (0) if info.argv[0] != "exit"
 *
 */
int myexit(ShellInfo *info)
{
	int exitcheck;

	if (info->argv[1]) 
	{
		exitcheck = erratoi_(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			printerror(info, "Illegal number: ");
			eputs(info->argv[1]);
			eputchar('\n');
			return (1);
		}

		info->err_num = erratoi_(info->argv[1]);
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * mycd - changes the current directory of the process
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function protype.
 *
 * Return: Always 0
 */
int mycd(ShellInfo *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		puts_("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getenv_(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be" */
				chdir((dir = getenv_(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strcmp_(info->argv[1], "-") == 0)
	{
		if (!getenv_(info, "OLDPWD="))
		{
			puts_(s);
			putchar_('\n');
			return (1);
		}
		puts(getenv_(info, "OLDPWD=")), putchar_('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = getenv_(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printerror(info, "can't cd to ");
		eputs_(info->argv[1]), eputchar('\n');
	}
	else
	{
		setenv_(info, "OLDPWD", getenv_(info, "PWD="));
		setenv_(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
