#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
*/
void execmd(char **argv)
{
	pid_t pid = fork();
	/*fork duplicates child process*/
	if (pid == 0)
	{
	/*child process now*/
		char *command = "/bin/ls";
	/*this is thr
