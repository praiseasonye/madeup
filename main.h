#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>
#include <stdlib.h>
#include <stddef.h>
#define PROMPT "$ "


/**
 * struct builtin_cmd - Defines the builtins functions.
 * @name: The name of the build in command.
 * @f: A pointer to the right builtin function.
 */
typedef struct builtin_cmd
{
	char *name;
	void (*f)(char *);
} builtin_t;

extern char **environ;

int built_in(char **, char *);
void (*builtin_selector(char *str))(char *str);
void exit_b(char *);
void env_b(char *);
void cd_b(char *);
char **token_interface(char *, const char *, int);
int count_token(char *, const char *);
char **tokenize(int, char *, const char *);
void create_child(char **, char *, int, char **);
void parse_line(char *, size_t, int, char **);
char *path_finder(char *);
int _strlen(char *);
int str_len(char *str);
int find_path(char *);
char **tokenize_path(int, char *);
char *search_directories(char **, char *);
char *build_path(char *, char *);
void double_free(char **);
void single_free(int, ...);

int _strcmp(char *, char *);
char *_strdup(char *);
void print_str(char *);
int print_digit(int);
int _write_char(char);
void _memcpy(void *newptr, const void *ptr, unsigned int size);

/* auxiliary functions*/
void error_printing(char *, int, char *);
void exec_error(char *, int, char *);

#endif
