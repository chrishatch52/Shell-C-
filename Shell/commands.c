#include "commands.h"



void printCommand(void * passedIn)
{
	Commands *tmp;
	int x = 0;

	tmp = (Commands*)passedIn;
	
	if(tmp != NULL)
	{
		if(tmp->command != NULL)
		{
			fprintf(stdout, "%d ", tmp->num);
			for(; x < tmp->rows; x++)
			{
				fprintf(stdout, "%s ", tmp->command[x]);
			}
			fprintf(stdout, "\n");
		}
	}
}//end printCommand
void * buildCommand(int argc, char ** argv)
{
	Commands *tmp = NULL;
	int x = 1;
	if(argv != NULL)
	{
		tmp = (Commands*)calloc(1, sizeof(Commands));
		tmp->command = (char**)calloc(argc + 1, sizeof(char*));
		tmp->command[0] = (char*)calloc(strlen(argv[0]) + 1, sizeof(char));
		strncpy(tmp->command[0], argv[0], strlen(argv[0]));
		tmp->rows = argc;
	
		for(; x < argc; x++)
		{
			tmp->command[x] = (char*)calloc(strlen(argv[x]) + 1, sizeof(char));
			strncpy(tmp->command[x], argv[x], strlen(argv[x]));
		}
		tmp->command[argc] = NULL;
	}
	return tmp;
}//end buildCommand

int compareTwoCommands(const void * p1, const void * p2)
{
	int x = 0, retVal = -1;
	const Commands *comp_one = (const Commands*)p1;
	const Commands *comp_two = (const Commands*)p2;

	
	if(comp_one != NULL && comp_two != NULL)
	{
		char **ara1 = comp_one->command;
		char **ara2 = comp_two->command;
		
		if(comp_one->rows != comp_two->rows)
		{
			return -1;
		}
		else
		{
			for(; x < comp_one->rows; x++)
			{
				if(strcmp(ara1[x], ara2[x]) == 0)
				{
					retVal = 0;
				}
				else
				{
					retVal = -1;
				}
			}
			return retVal;
		}
	}

	return -1;
}//end compareTwoCommands
void cleanCommand(void * command)
{
	int x = 0;
	Commands *tmp = (Commands*)command;

	if(tmp->command != NULL)
	{	
		for(; x < tmp->rows + 1; x++)
		{
			if(tmp->command[x] != NULL)
			{
				free(tmp->command[x]);
				tmp->command[x] = NULL;
			}
		}

		free(tmp->command);
		tmp->command = NULL;
	}

	if(tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
}//cleanCommand

