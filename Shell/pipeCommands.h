#ifndef PIPECOMMANDS_H
#define PIPECOMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

void pipeIt(char ** prePipe, char ** postPipe);
void pipeItRedirOut(char ** prePipe, char ** postPipe, FILE * redirOut);

#endif // PIPECOMMANDS_h
