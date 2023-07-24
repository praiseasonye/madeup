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
#include <stddef.h>

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
void execute_cmd(char **argv);
ssize_t _getline(char **lineptr, size_t *n);
#endif /* main.h */
