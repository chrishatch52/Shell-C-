#include "redirUtils.h"



void cleanRedir(char * preRedir, char * postRedir)
{
	if(preRedir != NULL)
	{
		free(preRedir);
		preRedir = NULL;
	}

	if(postRedir != NULL)
	{
		free(postRedir);
		postRedir = NULL;
	}

}//end cleanRedir

int hasRedir(char * s)
{
	if(strstr(s, ">") != NULL)
		return 0;

	return -1;
}//end hasRedir

char * parsePreRedir(char * s)
{
	char * tmp, * tmpTok, * svptr, * tmpPreRedir;
	
	tmp = (char*)calloc(strlen(s) + 1, sizeof(char));
	strncpy(tmp, s, strlen(s));

	tmpTok = strtok_r(tmp, ">", &svptr);

	tmpPreRedir = (char*)calloc(strlen(tmp) + 1, sizeof(char));
	strncpy(tmpPreRedir, tmp, strlen(tmp));

	if(tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
	return tmpPreRedir;
}//end preRedir

char * parsePostRedir(char * s)
{
	char * tmp, * tmpTok, * svptr, * tmpPostRedir;
	
	tmp = (char*)calloc(strlen(s) + 1, sizeof(char));
	strncpy(tmp, s, strlen(s));

	tmpTok = strtok_r(tmp, ">", &svptr);//throw away left side of redir

	tmpPostRedir = (char*)calloc(strlen(svptr) + 1, sizeof(char));
	strncpy(tmpPostRedir, svptr, strlen(svptr));

	if(tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
	return tmpPostRedir;
}//end postRedir

