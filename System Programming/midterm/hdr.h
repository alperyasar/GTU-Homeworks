/*************************************
			ALPER YAŞAR
			 151044072
	CSE344 - SYSTEM PROGRAMMING
    	   MIDTERM PROJECT
		
************************************/


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
#include <sys/mman.h>
#include <stdbool.h>
#include<time.h>
#include <stdint.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <stdarg.h>
#include <sys/shm.h>
#include <sys/mman.h>

void sigTermHandler(int sigNo);
void handler();

extern char **environ;
int inputFd,outputFd;
//char *tempPath;
char *inputPath;
char *pathToServerFifo;
char *clientPath = "/tmp/client";




void removeFifo();

struct response { /* Response (server --> client) */
	bool inv; /* Start of sequence */
};
struct request { /* Request (client --> server) */
	int datas[1024];
	int arraySize;
	pid_t pid; 

};
bool isMatrixInvertible();

struct request req;
struct response resp;
#endif
