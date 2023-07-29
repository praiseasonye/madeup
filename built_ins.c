#include "main.h"


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
int myexit(Shell *info)
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
int mycd(Shell *info)
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
		eputs(info->argv[1]), eputchar('\n');
	}
	else
	{
		setenv_(info, "OLDPWD", getenv_(info, "PWD="));
		setenv_(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
