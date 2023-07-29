#include "main.h"

/**
 * hsh - main shell loop
 *
 * @info: the parametr & return info struct
 *
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error or error code
 */

int hsh(Shell  *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clearinfo(info);
		if (interactive(info))
			puts_("#cisfun$ ");
		eputchar(BUFF_FLUSH);
		r = getinput(info);
		if (r != -1)
		{
			setinfo(info, av);
			builtin_ret = findbuiltin(info);
			if (builtin_ret == -1)
				findcmd(info);
		}
		else if (interactive(info))
			putchar_('\n');
		freeinfo(info, 0);
	}
	writehistory(info);
	freeinfo(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * findbuiltin - find a builtin command
 * @info: the paramet & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int findbuiltin(Shell  *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myexit},
		{"env", myenv_},
		{"help",myhelp},
		{"history", myhistory},
		{"setenv", mysetenv_},
		{"unsetenv", myunsetenv_},
		{"cd", mycd},
		{"alias", myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (strcmp_(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}


/**
 * findcmd - finds a command in PAT
 *
 * @info: the parameter & return info struct
 *
 * Return: void
 */

void findcmd(Shell  *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isdelim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = findpath(info, getenv_(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkcmd(info);
	}
	else
	{
		if ((interactive(info) || getenv_(info, "PATH=")
			|| info->argv[0][0] == '/') && iscmd(info, info->argv[0]))
			forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printerror(info, "not found\n");
		}
	}
}


/**
 * forkcmd - forks an exec thread to run cmd
 *
 * @info: the parameter & return info struct
 *
 * Return:
 * void
 */
void forkcmd(Shell  *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getenviron(info)) == -1)
		{
			freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printerror(info, "Permission denied\n");
		}
	}
}
