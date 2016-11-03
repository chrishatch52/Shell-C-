#include "pipeCommands.h"



void pipeIt(char ** prePipe, char ** postPipe)
{
	int fd[2], res, status;
	pid_t pid, pid2;


	pid = fork();

	if(pid == 0)
	{
		res = pipe(fd);

		if(res < 0)
		{
			printf("Pipe Failure\n");
			exit(-1);
		}// end if

		pid2 = fork();

		if(pid2 == 0)
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			if((execvp(prePipe[0], prePipe)) == -1)
			{
				perror("exec prePipe: failed");
				exit(-1);
			}
		}
		else
		{
			close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);

			if((execvp(postPipe[0], postPipe)) == -1)
			{
				perror("exec postPipe: failed");
				exit(-1);
			}

		}
	}
	else
	{
		waitpid(-1, &status, NULL);
	}
}//end pipeIt

void pipeItRedirOut(char ** prePipe, char ** postPipe, FILE * redirOut)
{
	int fd[2], res, status;
	pid_t pid, pid2;


	pid = fork();

	if(pid == 0)
	{
		res = pipe(fd);

		if(res < 0)
		{
			printf("Pipe Failure\n");
			exit(-1);
		}// end if

		pid2 = fork();

		if(pid2 == 0)
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			if((execvp(prePipe[0], prePipe)) == -1)
			{
				perror("exec prePipe: failed");
				exit(-1);
			}
		}
		else
		{
			close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);
			close(1);
			dup(redirOut);
			if((execvp(postPipe[0], postPipe)) == -1)
			{
				perror("exec postPipe: failed");
				exit(-1);
			}

		}
	}
	else
	{
		waitpid(-1, &status, NULL);
	}
}//end pipeItRedirOut
