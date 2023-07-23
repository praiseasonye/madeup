#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);

void execute_cmd(char **argv);
char *get_cmddir(char *cmd);
void double_free(char **to_be_freed);

/* define a structure to handle built-in commands */
typedef struct builtin_t{
	char *name;
	void (*func)(char **argv);
}builtin_command;

/* built-in functions */
void shell_exit(char **argv);
#endif /* main.h */
