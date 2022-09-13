/*********************************************************************************
*																				 *
*								ALPER YAŞAR										 *
*						GEBZE TECHNICAL UNİVERSITY								 *
*								151044072										 *
*							SYSTEM PROGRAMMING									 *
*								   FINAL										 *
*																				 *
**********************************************************************************/

/*	// for compiling the files
	$make	
*/


#ifndef HDR_H
#define HDR_H /* Prevent accidental double inclusion */

#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdatomic.h>
#define SA struct sockaddr 



void handler();



int port;


#endif
