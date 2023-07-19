#include "main.h"
 /*
 */

void execmd(char **argv)
{
	pid_t pid = fork();
	
	/*if 0, it is in the child's process*/
	/*why? child process inhereits parent*/
	if (pid == 0)
	{
		char *command = "/bin/ls";
		/*full path first*/

		char *args[] = {command, argv[1], NULL};

		if (execvp(argv[0], argv) == -1)
		{
		perror("Error");
		exit(1);
		}
	}
	else if (pid > 0)
	{
	/*parent process usually positive*/
	int child_status;
	/*stores info about child termination stat*/
	waitpid(pid, &child_status, 0);
	}
	else
	{
	perror("Error");
	}
}

int main()
{
	char *args[] = {"ls", "-l", NULL};
	execmd(args);
	return 0;
}

