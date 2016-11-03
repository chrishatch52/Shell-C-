#include "shellCommands.h"





void forkIt(int argc, char ** argv)
{
	pid_t pid;
	int status, x = 0;

	pid = fork();

	if(pid == -1)
	{
		perror("fork");
		exit(-1);
	}	
	
	if(pid != 0)
	{
		waitpid(-1, &status, 0);
	}
	else
	{
		
		if(execvp(argv[0],argv) == -1)
		{
			perror("execvp");
			exit(-1);
		}
	}
}//end forkIt

void forkItRedirOut(int argc, char ** argv, FILE * redirOut)
{
	pid_t pid;
	int status, x = 0;

	pid = fork();

	if(pid == -1)
	{
		perror("fork");
		exit(-1);
	}	
	
	if(pid != 0)
	{
		waitpid(-1, &status, 0);
	}
	else
	{
		close(1);
		dup(redirOut);
		if(execvp(argv[0],argv) == -1)
		{
			perror("execvp");
			exit(-1);
		}
	}
}//end forkItRedirOut
