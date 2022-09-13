#ifndef HDR_H
#define HDR_H /* Prevent accidental double inclusion */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h> 
#include <math.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

void sigTermHandler(int sigNo);
void handler();

extern char **environ;
int inputFd,outputFd;
//char *tempPath;
char *inputPath;
char *outputPath;


#endif
