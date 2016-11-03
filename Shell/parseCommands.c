#include "parseCommands.h"

int hasPipe(char * s)
{
	if(strstr(s, "|") != NULL)
		return 0;

	return -1;
}//end hasPipe

char ** parsePrePipe(char * s, int * count)
{
	char *svptr, *tmp, *tmp_preComm, **tmpPre;
	
	*count = -1;
	tmp = (char*)calloc(strlen(s) + 1, sizeof(char));
	strncpy(tmp, s, strlen(s));
	tmp_preComm = strtok_r(tmp, "|", &svptr);

	tmpPre = makeargs(tmp_preComm, count);

	if(tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}

	return tmpPre;
}//end parsePrePipe

char ** parsePostPipe(char * s, int * count)
{
	char *svptr, *tmp, *tmp_postComm, **tmpPost;
	
	tmp = (char*)calloc(strlen(s) + 1, sizeof(char));
	strncpy(tmp, s, strlen(s));
	tmp_postComm = strtok_r(tmp, "|", &svptr);//discard left side of pipe

	tmpPost = makeargs(tmp_postComm, count);

	if(tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}

	return tmpPost;
}//end parsePostPipe
