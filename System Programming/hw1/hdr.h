#ifndef HDR_H
#define HDR_H /* Prevent accidental double inclusion */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void Tokenize(char * token,int fd,int tempfile);
void Sensitive(char* str1,char* str2,int fd,int tempfile);
void inSensitive(char* str1,char* str2,int fd,int tempfile);
int functionChoose(char* str);
void multipleMatch(char* str1,char* str2,int fd,int tempfile);
void lineStart(char* str1,char* str2,int fd,int tempfile);
void lineEnd(char* str1,char* str2,int fd,int tempfile);
void repetationMatch(char* str1,char* str2,int fd,int tempfile);

#endif
