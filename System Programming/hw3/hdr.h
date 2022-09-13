/*********************************************************************************
*																				 *
*								ALPER YAŞAR										 *
*						GEBZE TECHNICAL UNİVERSITY								 *
*								151044072										 *
*							SYSTEM PROGRAMMING									 *
*									HW3 										 *
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

typedef struct ingredients
{
	char ing1[8],ing2[8];
	char has[3],need[3];
} Chef;
Chef chef[6];
int fdInput,mother = 0;

void handler(int sig) ;
int street(int index);
void wholesaler();

#endif
