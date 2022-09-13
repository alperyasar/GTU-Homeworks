/*********************************************************************************
*																				 *
*								ALPER YAŞAR										 *
*						GEBZE TECHNICAL UNİVERSITY								 *
*								151044072										 *
*							SYSTEM PROGRAMMING									 *
*									HW4 										 *
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
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>


static void *consumer(void *arg);

#endif
