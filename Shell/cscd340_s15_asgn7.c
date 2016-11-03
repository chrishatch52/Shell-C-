#include "utility.h"
// add your #includes here
#include "linkedList.h"
#include "historyUtils.h"
#include "redirUtils.h"
#include "commands.h"
#include "pipeCommands.h"
#include "shellCommands.h"

int main()//myLs not implemented
{
    char s[MAX], **argv = NULL, ** prePipe = NULL, ** postPipe = NULL;
    char * bangStr, * bangStr_Pipe, * preRedir = NULL, * postRedir = NULL;
    int type, histCount = 0, histFileCount = 0, argc, preCount = 0, postCount = 0;
    Node * countStart, * fileStart, * end;
    LinkedList * history = linkedList();
    FILE * ushrcIn, * ush_HistIn, * redirOut;

	// You will need code to open .ushrc and .ush_history here
	ushrcIn = fopen(".ushrc", "r");
	ush_HistIn = fopen(".ush_history", "r");
	
	setCounts(ushrcIn, &histCount, &histFileCount);

	if(ush_HistIn != NULL)
	{
		//add .ush_history to LL Hist
		setHistory(ush_HistIn, history);
		setHistoryPointers(history, &countStart, &fileStart, &end, histCount, histFileCount);
	}
	printf("Please enter a string (exit to exit) ");
	fgets(s, MAX, stdin);
	strip(s);

	while(strcmp(s, "exit") != 0)
	{

		// You will need fork it and pipe it and other code here
		if(strcmp(s, "history") == 0)
		{
			printHistory(countStart);
		}

		else
		{
			if(isLastHistoryComm(s, end) == 0)
			{
				fprintf(stdout, "is last hist comm\n");
				parseLastCommand(&preRedir, &postRedir, end);
			}
			else
			{
				preRedir = parsePreRedir(s);//returns copy of s if no Redir so s does not get corrupted
				if(hasRedir(s) == 0)
				{
					postRedir = parsePostRedir(s);
				}
			}
		}
		if(preRedir != NULL)
		{
			if((bangStr = strstr(preRedir, "!")) == NULL)
			{
				argv = makeargs(s, &argc);
			}
			else
			{
				fprintf(stdout, "Has ! in argv\n");
				parseBangCommand(&preRedir, history);
				if(hasRedir(s) == 0)
				{
					postRedir = parsePostRedir(s);
				}
				//argv = findHistComm(s, &argc, history); ran out of time on this one
			}

			if(argv != NULL)
			{
				addLast(history, buildNode(argc, argv, buildCommand));
				setHistoryPointers(history, &countStart, &fileStart, &end, histCount, histFileCount);
			}

			if(hasPipe(s) == 0)
			{
				fprintf(stdout, "Has Pipe\n");
				
				prePipe = parsePrePipe(preRedir, &preCount);
				postPipe = parsePostPipe(preRedir, &postCount);
				
				if(postRedir == NULL)
				{
					fprintf(stdout, "Pipe no Redir\n");
					
					pipeIt(prePipe, postPipe);
					
				}
				else
				{
					fprintf(stdout, "Pipe no Redir\n");
					
					pipeItRedirOut(prePipe, postPipe, redirOut);
					
				}
			}
			else
			{
				fprintf(stdout, "Reg Command\n");
				if(postRedir != NULL)
				{
					forkItRedirOut(argc, argv, redirOut);
				}
				else
				{
					forkIt(argc, argv);
				}
			}
		}
		// you will probably need code to clean up stuff		
		clean(argc, argv);
		argv = NULL;
		cleanRedir(preRedir, postRedir);
		preRedir = NULL;
		postRedir = NULL;
        printf("Please enter a string (exit to exit) ");
        fgets(s, MAX, stdin);
        strip(s);
	
	}// end while
	saveHistoryToFile(history, fileStart);
	clearList(history, cleanCommand);
	free(history);
	history = NULL;
	if(ushrcIn != NULL)
		fclose(ushrcIn);
	if(ush_HistIn != NULL)
		fclose(ush_HistIn);
	
	return 0;

}// end main
