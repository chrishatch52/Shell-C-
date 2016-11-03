#ifndef SHELLCOMMANDS_H
#define SHELLCOMMANDS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void forkIt(int argc, char ** argv);
void forkItRedirOut(int argc, char ** argv, FILE * redirOut);

#endif // SHELLCOMMANDS_H
