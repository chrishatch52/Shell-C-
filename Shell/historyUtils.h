#ifndef HISTORY_UTILS
#define HISTORY_UTILS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include "commands.h"
#include "utility.h"


char ** findHistComm(char * s, int * argc, LinkedList * history);
Node * getNodeAtIndex(LinkedList * history, int index);
int isLastHistoryComm(char * s, Node * end);
void parseLastCommand(char ** preRedir, char ** postRedir, Node * end);
void parseBangCommand(char ** preRedir, LinkedList * history);
void printHistory(Node * countStart);
void saveHistoryToFile(LinkedList * history, Node * fileStart);
void setCounts(FILE * ushrcIn, int * histCount, int * histFileCount);
void setHistory(FILE * ush_historyIn, LinkedList * history);
void setHistoryPointers(LinkedList * history, Node ** countStart, Node ** fileStart, Node ** end, int histCount, int histFileCount);


#endif
