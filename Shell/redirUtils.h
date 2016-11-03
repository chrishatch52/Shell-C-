#ifndef REDIR_UTILS
#define REDIR_UTILS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void cleanRedir(char * preRedir, char * postRedir);
char * parsePreRedir(char * s);
char * parsePostRedir(char * s);
int hasRedir(char * s);

#endif
