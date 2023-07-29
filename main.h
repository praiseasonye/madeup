#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define BUFF_SIZE 1024
#define BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for command chaining */
#define CMDNORM 0
#define CMDOR 1
#define CMDAND 2
#define CMDCHAIN 3

/* for convert_number() */
#define CONVERTLOWERCASE 1
#define CONVERTUNSIGNED 2

/* 1 if using system getline() */
#define USEGETLINE 0
#define USESTRTOK 0

#define HISTFILE ".shell_history"
#define HISTMAX 4096

extern char **environ;

/**
 * struct liststring - singly linked list
 *
 * @num: the number field
 *
 * @str: a string
 *
 * @next: points to the next node
 *
 */

typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} list_t;

/**
 * struct Shell  - Structure to store information passed into functions,
 *
 * allowing uniform prototype for function pointer struct
 *
 * @arg: a string generated from getline containing arguments
 *
 * @argv: an array of strings generated from arg
 *
 * @path: a string path for the current command
 *
 * @argc: the argument count
 *
 * @line_count: the error count
 *
 * @err_num: the error code for exit()
 *
 * @linecount_flag: if on count this line of input
 *
 * @fname: the program filename
 *
 * @env: linked list local copy of environ
 *
 * @environ: custom modified copy of environ from LL env
 *
 * @history: the history node
 *
 * @alias: the alias node
 *
 * @env_changed: on if environ was changed
 *
 * @status: the return status of the last exec'd command
 *
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 *
 * @cmd_buf_type: CMD_type ||, &&, ;
 *
 * @readfd: the fd from which to read line input
 *
 * @histcount: the history line number count
 *
 */

typedef struct Shell_mad
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} Shell;

#define INFOINIT                                                         \
	{                                                                     \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, \
			NULL, 0, 0, 0                                                 \
	}

/**
 * struct builtin - contains a builtin string and related function
 *
 * @type: the builtin command flag
 *
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(Shell *);
} builtin_table;


int hsh(Shell *, char **);
int findbuiltin(Shell *);
void findcmd(Shell *);
void forkcmd(Shell *);

int iscmd(Shell *, char *);
char *dupchars(char *, int, int);
char *findpath(Shell *, char *, char *);

int loophsh(char **);

void eputs(char *);
int eputchar(char);
int putfd(char c, int fd);
int putsfd(char *str, int fd);

int strlen_(char *);
int strcmp_(char *, char *);
char *startswith(const char *, const char *);
char *strcat_(char *, char *);

char *strcpy_(char *, char *);
char *strdup_(const char *);
void puts_(char *);
int putchar_(char);

char *strncpy_(char *, char *, int);
char *strncat_(char *, char *, int);
char *strchr_(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *memset_(char *, char, unsigned int);
void ffree(char **);
void *realloc_(void *, unsigned int, unsigned int);

int bfree(void **);

int interactive(Shell *);
int isdelim(char, char *);
int isalpha_(int);
int atoi_(char *);

int erratoi_(char *);
void printerror(Shell *, char *);
int printd(int, int);
char *convertnumber(long int, int, int);
void removecomments(char *);

int myexit(Shell *);
int mycd(Shell *);
int myhelp(Shell *);

int myhistory(Shell *);
int myalias(Shell *);


ssize_t getinput(Shell *);
int _getline(Shell *, char **, size_t *);
void sigintHandler(int);


void clearinfo(Shell *);
void setinfo(Shell *, char **);
void freeinfo(Shell *, int);

char *getenv_(Shell *, const char *);
int myenv_(Shell *);
int mysetenv_(Shell *);
int myunsetenv_(Shell *);
int populateenvlist(Shell *);

char **getenviron(Shell *);
int unsetenv_(Shell *, char *);
int setenv_(Shell *, char *, char *);

char *gethistoryfile(Shell *info);
int writehistory(Shell *info);
int readhistory(Shell *info);
int buildhistorylist(Shell *info, char *buf, int linecount);
int renumberhistory(Shell *info);

list_t *addnode(list_t **, const char *, int);
list_t *addnodeend(list_t **, const char *, int);
size_t printliststr(const list_t *);
int deletenodeatindex(list_t **, unsigned int);
void freelist(list_t **);

size_t listlen(const list_t *);
char **listtostrings(list_t *);
size_t printlist(const list_t *);
list_t *nodestartswith(list_t *, char *, char);
ssize_t getnodeindex(list_t *, list_t *);

int ischain(Shell *, char *, size_t *);
void checkchain(Shell *, char *, size_t *, size_t, size_t);
int replacealias(Shell *);
int replacevars(Shell *);
int replacestring(char **, char *);

ssize_t readbuf(Shell *info, char *buf, size_t *i);
int printalias(list_t *node)

#endif
