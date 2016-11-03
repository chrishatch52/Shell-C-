#include "historyUtils.h"


#define MAX 100

char ** findHistComm(char * s, int * argc, LinkedList * history)// does not handle !n | !m
{
	int tmpLoc = -1, x = 0;
	char buf[(int)strlen(s) + 1], * bangStr, * mainSvptr, * svptr, * tmp, ** argv = NULL;
	char buf1[(int)strlen(s) + 1], buf2[MAX], * pipeStr;
	Node * cur;
	Commands * tmpComm;
	
	strncpy(buf, s, (int)strlen(s));
	strncpy(buf1, s, (int)strlen(s));
	
	if(cur != NULL)
	{
		if((bangStr = strstr(s, "!")) != NULL)
		{
			tmp = strtok_r(buf, "|>", &svptr);
		
			if(strcmp(s, buf) == 0)
			{
				tmp = strtok_r(buf, "!", &svptr);
				tmpLoc = atoi(tmp);
				cur = getNodeAtIndex(history, tmpLoc);
				argv = ((Commands*)cur->data)->command;
			}
			else
			{
				if((pipeStr = strstr(s, "|"))!= NULL)
				{
					tmp = strtok_r(buf1, "|", &mainSvptr);
					fprintf(stdout, "mainSvptr: %s\n", mainSvptr);
					tmp = NULL;
					if(strstr(buf1, "!") == NULL)
					{
						tmp = strtok_r(NULL, "!", &svptr);
						tmpLoc = atoi(svptr);
						cur = getNodeAtIndex(history, tmpLoc);
						if(cur->data != NULL)
						{
							tmpComm = (Commands*)cur->data;
							printCommand(cur->data);
							for(; x < tmpComm->rows; x++)
							{
								strncat(buf2, tmpComm->command[x], (int)strlen(tmpComm->command[x]));
								strncat(buf2, " ", 1);
							}
						}
					}
					else
					{
						tmp = strtok_r(buf1, "!", &svptr);
						tmpLoc = atoi(tmp);
						cur = getNodeAtIndex(history, tmpLoc);
						if(cur->data != NULL)
						{		
							tmpComm = (Commands*)cur->data;
							printCommand(cur->data);	
							for(; x < tmpComm->rows; x++)
							{
								strncat(buf2, tmpComm->command[x], (int)strlen(tmpComm->command[x]));
							}
						}
					}
				}
				if(strstr(mainSvptr, "|") != NULL)
				{
					fprintf(stdout, "msp: %s\n", mainSvptr);
					strncat(buf1, buf2, (int)strlen(buf2));
				}	
				else
				{
					fprintf(stdout, "buf1: %s\n", buf1);
					strncat(buf1, mainSvptr, (int)strlen(mainSvptr));
				}
			}

		}

	}	
	
	return argv;
}//end findHistComm

Node * getNodeAtIndex(LinkedList * history, int index)
{
	int x = 0;
	Node * cur = NULL;

	if(index > -1 && index < history->size)
	{
		cur = history->head->next;
		while(cur != NULL && x < history->size)
		{
			if(x == index - 1)
				return cur;
			else
				x++;
			cur = cur->next;
		}
	}

	return cur;
}//end getNodeAtIndex

int isLastHistoryComm(char * s, Node * end)
{
	char **argv = NULL;
	int equalsLastComm = -1, x = 0, argc = -1;
	Commands * tmp = NULL;
	
	if(strcmp(s, "!!") != 0
		&& strcmp(s, "!-1") != 0)
	{
		argv = makeargs(s, &argc);
	}

	if(argc != -1)
	{
		tmp = (Commands*)calloc(1, sizeof(Commands));
		
		tmp->command = (char**)calloc(argc + 1, sizeof(char*));
		tmp->command[0] = (char*)calloc(strlen(argv[0]) + 1, sizeof(char));
		strncpy(tmp->command[0], argv[0], strlen(argv[0]));

		tmp->rows = argc;
		tmp->num = 0;

		for(; x < argc; x++)
		{
			tmp->command[x] = (char*)calloc(strlen(argv[x]) + 1, sizeof(char));
			strncpy(tmp->command[x], argv[x], strlen(argv[x]));
		}
		tmp->command[argc] = NULL;

		if(end->data != NULL)
			equalsLastComm = compareTwoCommands(end->data, tmp);
	
		cleanCommand(tmp);
	}

	return equalsLastComm;
}//isLastHistoryComm

void parseLastCommand(char ** preRedir, char ** postRedir, Node * end)
{
	int x = 0, y = 0, z = 0, hasRedir = 0, redirLoc = -1;
	char buf[MAX], buf1[MAX];
	Commands * tmpEnd;
	if(end != NULL)
	{
		if(end->data != NULL)
		{
			tmpEnd = (Commands*)end->data;

			for(; x < tmpEnd->rows; x++)
			{
				if(strcmp(tmpEnd->command[x], ">") == 0)
				{
					hasRedir = 1;
					redirLoc = x;
				}
			}

			if(hasRedir == 1)
			{
				
				for(; y < redirLoc; y++)
				{
					strncat(buf, tmpEnd->command[y], (int)strlen(tmpEnd->command[y]));
					strncat(buf, " ", 1);
				}
				for(redirLoc = redirLoc + 1; redirLoc < tmpEnd->rows; redirLoc++)
				{
					strncat(buf1, tmpEnd->command[redirLoc], (int)strlen(tmpEnd->command[redirLoc]));
					strncat(buf1, " ", 1);
				}
				(*preRedir) = (char*)calloc(strlen(buf) + 1, sizeof(char));
				strncpy(*preRedir, buf, (int)strlen(buf));
				(*postRedir) = (char*)calloc(strlen(buf1) + 1, sizeof(char));
				strncpy(*postRedir, buf1, (int)strlen(buf1));
			}
			else
			{
				for(; z < tmpEnd->rows; z++)
				{
					strncat(buf, tmpEnd->command[z], (int)strlen(tmpEnd->command[z]));
					strncat(buf, " ", 1);
				}
				(*preRedir) = (char*)calloc(strlen(buf) + 1, sizeof(char));
				strncpy(*preRedir, buf, (int)strlen(buf));
			}
		}
	}
	
	
}//end parseLastCommand

void parseBangCommand(char ** preRedir, LinkedList * history)
{
	
}//end parseBangCommand

void printHistory(Node * countStart)
{
	Node * cur;
	
	for(cur = countStart; cur != NULL; cur = cur->next)
	{
		if(cur->data != NULL)
		{
			printCommand(cur->data);
		}
	}

}//end printHistory

void saveHistoryToFile(LinkedList * history, Node * fileStart)
{
	int x = 0;
	Node * cur;
	Commands * tmpComm;
	FILE * fout = fopen(".ush_history", "w");

	if(fout != NULL)
	{
		for(cur = fileStart; cur != NULL; cur = cur->next)
		{
			tmpComm = (Commands*)cur->data;
			fprintf(fout, "%d ", tmpComm->num);
			for(; x < tmpComm->rows; x++)
			{
				fprintf(fout, "%s ", tmpComm->command[x]);
			}
			fprintf(fout, "\n");
			x = 0;
		}
	}
	else
	{
		fprintf(stdout, "New History File Failed\n");
	}
	if(fout != NULL)
		fclose(fout);
}//end saveHistoryToFile

void setCounts(FILE * ushrcIn, int * histCount, int * histFileCount)
{
	char buf[MAX], * tmpTok, * svptr;

	fgets(buf, MAX, ushrcIn);

	tmpTok = strtok_r(buf, "=", &svptr);

	*histCount = atoi(svptr);

	fgets(buf, MAX, ushrcIn);

	tmpTok = strtok_r(buf, "=", &svptr);

	*histFileCount = atoi(svptr);
	
}//end setCounts

void setHistory(FILE * ush_historyIn, LinkedList * history)
{
	char buf[MAX];
	char **argv = NULL, *svptr, *tmpTok;
	int argc, tmpRow;
	Node * tmp;
	
	while(fgets(buf, MAX, ush_historyIn) != NULL)
	{
		tmpTok = strtok_r(buf, " ", &svptr);
		tmpRow = atoi(tmpTok);
		argv = makeargs(svptr, &argc);
		if(argc != -1)
		{	
			tmp = buildNode(argc, argv, buildCommand);
			((Commands*)tmp->data)->num = tmpRow;
			addLast(history, tmp);
		}
		clean(argc, argv);
	}
}//end setHistory

void setHistoryPointers(LinkedList * history, Node ** countStart, Node ** fileStart, Node ** end, int histCount, int histFileCount)
{
	int x = 0, y = 0, z = 0, tempCstart = 1, tempFstart = 1;
	Node * tmpCount, * tmpFile, * tmpEnd;

	if(history != NULL)
	{
		tmpCount = history->head;
		tmpFile = history->head;
		tmpEnd = history->head;
		if(histCount < history->size)
		{
			histCount = (history->size - histCount);
		}
		for(; x < histCount; x++)
		{
			tmpCount = tmpCount->next;
		}
		if(histFileCount < history->size)
		{
			histFileCount = (history->size - histFileCount);
		}
		for(; y < histFileCount; y++)
		{
			tmpFile = tmpFile->next;
		}
		for(; z < history->size; z++)
		{
			tmpEnd = tmpEnd->next;
		}
		if(tmpCount != NULL)
		{
			*countStart = tmpCount;
		}
		if(tmpFile != NULL)
		{
			*fileStart = tmpFile;
		}
		if(tmpEnd != NULL)
		{
			*end = tmpEnd;
		}
	}



}//end setHistoryPointers
