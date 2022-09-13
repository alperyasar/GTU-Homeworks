/*********************************************************************************
*																				 *
*								ALPER YAŞAR										 *
*						GEBZE TECHNICAL UNİVERSITY								 *
*								151044072										 *
*							SYSTEM PROGRAMMING									 *
*									HW5 										 *
*																				 *
**********************************************************************************/

/*	// for compiling the files
	$make	
*/


#ifndef HDR_H
#define HDR_H /* Prevent accidental double inclusion */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

char *filePath1,*filePath2,*outputFile;
int n,m;
int fd1,fd2,outputFd;


void exitProcess();
void handler(int sig);
int **allocMatrix(int fd);
void deAllocMatrix(int **arr);
double **allocDoubleMatrix();
void deAllocDoubleMatrix(double **arr);
static void *calculation(void *arg);

#endif
