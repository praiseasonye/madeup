#include "main.h"

/**
 * aux_help_alias - Help information for the builtin alias.
 *
 * Return: no return
 */

void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
