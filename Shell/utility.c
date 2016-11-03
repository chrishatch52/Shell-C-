#include "utility.h"

void strip(char *s)
{
  int x = 0, len;
  len = strlen(s);
  while(s[x] != '\0' && x < len)
  {
	if(s[x] == '\r')
    	s[x] = '\0';

	else if(s[x] == '\n')
    	s[x] = '\0';

    x++;
  }// end while
}// end strip

void clean(int argc, char **argv)
{
	int x = 0;

	if(argv != NULL)
	{
		for(; x < argc + 1; x++)
		{
			if(argv[x] != NULL)
			{
				free(argv[x]);
				argv[x] = NULL;
			}
		}
		
		free(argv);
		argv = NULL;
	}
		
}

void printargs(int argc, char **argv)
{
	int x;

	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}

char ** makeargs(char *s, int * argc)
{
   char *svptr , *svptr2, *tmp, tmp2[(int)strlen(s) + 1], tmp3[(int)strlen(s) + 1], **tmp_args;
   int count = 0, x = 1, tmp_length = 0;
   
   if(s == NULL)
   {
	return NULL;
   }
   else if(strcmp(s, "\0") == 0)
   {
	*argc = -1;
        return NULL;
   }
   strcpy(tmp2, s);
   strcpy(tmp3, s);
   tmp = strtok_r(tmp3, " ", &svptr);
   
   while(tmp != NULL)
   {
	tmp = strtok_r(NULL, " ", &svptr);
	count++;
   }

   tmp_args = (char**)calloc(count + 1, sizeof(char*));
   
   tmp = strtok_r(tmp2, " ", &svptr2);
   strip(tmp);
   tmp_length = (int)(strlen(tmp) + 1);
   tmp_args[0] = (char*)calloc(tmp_length, sizeof(char));
   strncpy(tmp_args[0], tmp, tmp_length);

   for(; x < count; x++)
   {
	tmp = strtok_r(NULL, " ", &svptr2);
	strip(tmp);
	tmp_length = (int)(strlen(tmp) + 1);
	tmp_args[x] = (char*)calloc(strlen(tmp) + 1, sizeof(char));
	strncpy(tmp_args[x], tmp, tmp_length);
   }

   *argc = count;
   tmp_args[count] = NULL;

   return tmp_args;

}// end makeArgs

