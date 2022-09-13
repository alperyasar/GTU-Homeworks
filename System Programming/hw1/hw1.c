#include "hdr.h"

#define MAX_READ 1

int main(int argc, char *argv[]) {
    char *str, *token;
    char *saveptr;
    char buffer[1];
    int fd1, fd2;
    struct flock fl1,fl2;
    
    // check argument number 1. is strings 2. is filepath
    if (argc != 3){
        fprintf(stderr, "%s has not enough number of argument\n", argv[0]);
        exit(0);
    }
    // file locks
    memset(&fl1,0 , sizeof(fl1));
    memset(&fl2,0 , sizeof(fl1));
    // divide string with semicolon ";"
    for (str = argv[1]; ; str = NULL) {
        // file opening

        fl1.l_type = F_RDLCK;
        fl2.l_type = F_WRLCK;
        // read file
        fd1 = open(argv[2], O_RDWR);
        if (fd1 == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // lock file 
        fcntl(fd1,F_SETLKW,&fl1);
        fcntl(fd1,F_SETLKW,&fl2);        
        // create temp file
        char template[] = "/tmp/tempFileXXXXXX";
        fd2 = mkstemp(template);
        if (fd2 == -1){
            perror("mkstemp");
            exit(EXIT_FAILURE);
        }
        unlink(template); 
        // divide file with ";"
        token = strtok_r(str, ";", &saveptr);
        if (token == NULL)
            break;
        Tokenize(token,fd1,fd2);
        // file closing
        if (close(fd1) == -1)
            perror("File close");
        fd1 = open(argv[2],O_WRONLY | O_TRUNC);
        if (fd1 == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // read from temp file and write into file
        lseek(fd2, 0, SEEK_SET);
        while(read(fd2, buffer, 1) != '\0')
            write(fd1, buffer, 1); 
        // unclock and close file
        fl1.l_type = F_UNLCK;
        fl2.l_type = F_UNLCK;
        fcntl(fd1,F_SETLKW,&fl1);
        fcntl(fd1,F_SETLKW,&fl2); 
        if (close(fd1) == -1)
            perror("File close"); 
        if (close(fd2) == -1)
            perror("Temp file close");
    }

    return 0;
}

// this function taking string which divided by semicolon ";" and files 
// divide string with slash "/" and take them. 
// first string is which going to be changed string and  
// second one is new string.
// look which oparete is going to happened. 
// find contains special characters in functionChoose and 
// send strings to right functions
void Tokenize(char * token,int fd,int tempfile){
    char *str1,*str2,*inSens, *saveptr;
    str1 = strtok_r(token, "/", &saveptr);
    str2 = strtok_r(NULL, "/", &saveptr);
    if((inSens = strtok_r(NULL, "/", &saveptr)) != NULL){
        inSensitive(str1,str2, fd,tempfile);
    }
    else{
        switch(functionChoose(str1)){
            case 0: Sensitive( str1,str2,fd,tempfile);
                break;
            case 1:multipleMatch(str1,str2,fd,tempfile);
                break;
            case 2:lineStart(str1,str2,fd,tempfile);
                break;
            case 3:lineEnd(str1,str2,fd,tempfile);
                break;
            case 4:repetationMatch(str1,str2,fd,tempfile);
                break;
        }
    
    }

}
// find string if it is contain special character. 
// and return a value for them.
int functionChoose(char* str){
    for (int i = 0; i < strlen(str); ++i)
    {
        if(str[i] == '[')
            return 1;
        else if(str[i] == '^')
            return 2;
        else if(str[i] == '$')
            return 3;
        else if(str[i] == '*')
            return 4;
    }
    return 0;
}

// each function in the below reading each file char by char
// and checking character match.
// this function checking each character as case sensitive. 
// If first characters match with look others characters. 
// If all match happened write new string to file.
// if some character matched but others character not matched
// turn to next character of first match with lseek.
// if there is no match then write this character into temp file.
void Sensitive(char* str1,char* str2,int fd,int tempfile){
    char buffer[1];
    int curr , strCheck=0;
    while(read(fd, buffer, 1) != '\0'){
        if(str1[0] == buffer[0]){
            curr = lseek(fd, 0, SEEK_CUR);
            strCheck=1;
            for (int i = 1; i < strlen(str1); ++i)
            {
                if(strlen(str1) > 1 && (read(fd, buffer, 1) == '\0' || buffer[0] != str1[i])){
                    strCheck = 0;
                }   
            }
            if (strCheck)
            {
                // delete word from file and add new 
                write(tempfile, str2, strlen(str2));
                strCheck=0;
                continue;
            }
            else{

                lseek(fd, curr-1, SEEK_SET);
                read(fd, buffer, 1);
            }
        }
        
        if (!strCheck){
            write(tempfile, buffer, 1);
        }
        
    }

}
// happening as like as Sensitive function but just inSensitive case
void inSensitive(char* str1,char* str2,int fd,int tempfile){
    char buffer[1];
    int curr , strCheck=0;
    while(read(fd, buffer, 1) != '\0'){
        if(str1[0] == buffer[0]){
            curr = lseek(fd, 0, SEEK_CUR);
            strCheck=1;
            for (int i = 1; i < strlen(str1); ++i)
            {
                if(strlen(str1) > 1 && (read(fd, buffer, 1) == '\0' || tolower(buffer[0])!=tolower(str1[i]))){
                    strCheck = 0;
                }   
            }
            if (strCheck)
            {
                // delete word from file and add new 
                write(tempfile, str2, strlen(str2));
                strCheck=0;
                continue;
            }
            else{

                lseek(fd, curr-1, SEEK_SET);
                read(fd, buffer, 1);
            }
        }
        
        if (!strCheck){
            write(tempfile, buffer, 1);
        }
        
    }

}
/*  happening like other function above functions. 
    when see the "[" checking the characters which found 
    in "[]". 
    if command is '/Window[sz]/Linux/' when Windows or Windowz 
    found then change it with Linux

*/
void multipleMatch(char* str1,char* str2,int fd,int tempfile){
    char buffer[1];
    int curr ;
    bool strCheck=false,multiFound = false;
    while(read(fd, buffer, 1) != '\0'){
        if(str1[0] == buffer[0]){
            curr = lseek(fd, 0, SEEK_CUR);
            strCheck=true;
            multiFound = false;
            for (int i = 1; i < strlen(str1); ++i)
            {
                
                if(strlen(str1) < 1 || (read(fd, buffer, 1) == '\0' )){
                    strCheck = false;
                }  
                else if(str1[i] == '['){
                    ++i;
                    while(str1[i] != ']'){
                        if(str1[i] == buffer[0])
                            multiFound = true;
                        ++i;
                    }
                }
                else if (buffer[0] != str1[i])
                    strCheck = false;
            }
            if (strCheck && multiFound)
            {
                // delete word from file and add new 
                write(tempfile, str2, strlen(str2));
                strCheck=false;
                continue;
            }
            else{
                strCheck=false;
                lseek(fd, curr-1, SEEK_SET);
                read(fd, buffer, 1);
            }
        }
        else if(str1[0] == '['){
            curr = lseek(fd, 0, SEEK_CUR);
            strCheck=true;
            multiFound = false;
            int i = 1;
            while(str1[i] != ']'){
                if(str1[i] == buffer[0])
                    multiFound = true;
                ++i;
            }
            i++;
            if (multiFound)
            {
                while(i<strlen(str1)){
                    if((read(fd, buffer, 1) == '\0' ) || buffer[0] != str1[i]){
                        strCheck = false;
                    }  
                    ++i;
                }
            }
            
            if (strCheck && multiFound)
            {
                // delete word from file and add new 
                write(tempfile, str2, strlen(str2));
                strCheck=false;
                continue;
            }
            else{
                strCheck=false;
                lseek(fd, curr-1, SEEK_SET);
                read(fd, buffer, 1);
            }
        }
        
        if (!strCheck){
            write(tempfile, buffer, 1);
        }
        
    }

}
// if changing word found in begin of the line change it. 
// otherwise do not change.
void lineStart(char* str1,char* str2,int fd,int tempfile){
    char buffer[1];
    int curr , strCheck=0;
    int line = 0;
    while(read(fd, buffer, 1) != '\0'){
        if(str1[1] == buffer[0] && line == 0){
            curr = lseek(fd, 0, SEEK_CUR);
            strCheck=1;
            for (int i = 2; i < strlen(str1); ++i)
            {
                if((strlen(str1) < 2 || (read(fd, buffer, 1) == '\0') || buffer[0] != str1[i])){
                    strCheck = 0;
                }   
            }
            if (strCheck)
            {
                // delete word from file and add new 
                write(tempfile, str2, strlen(str2));
                strCheck=0;
                continue;
            }
            else{

                lseek(fd, curr-1, SEEK_SET);
                read(fd, buffer, 1);
            }
        }
        else if (buffer[0] == '\n'){
            line = 0;
        }
        else line++;
        
        if (!strCheck){
            write(tempfile, buffer, 1);
        }
        
    }

}
// if changing word found in end of the line change it. 
// otherwise do not change.
void lineEnd(char* str1,char* str2,int fd,int tempfile){
    char buffer[1];
    int curr , strCheck=0;
    while(read(fd, buffer, 1) != '\0'){
        if(str1[0] == buffer[0]){
            curr = lseek(fd, 0, SEEK_CUR);
            strCheck=1;
            for (int i = 1; i < strlen(str1) - 1; ++i)
            {
                if(strlen(str1) < 1 || (read(fd, buffer, 1) == '\0' || buffer[0] != str1[i])){
                    strCheck = 0;
                }   
            }
            read(fd, buffer, 1);
            if (strCheck && buffer[0] == '\n')
            {
                // delete word from file and add new 
                write(tempfile, str2, strlen(str2));
                write(tempfile, buffer, 1);     
                strCheck=0;
                continue;
            }
            else{
                strCheck=0;
                lseek(fd, curr-1, SEEK_SET);
                read(fd, buffer, 1);
            }
        }
        
        if (!strCheck){
            write(tempfile, buffer, 1);
        }
        
    }

}
/*  
    It must support zero or more repetitions of characters; 
    e.g. this will match sr1, str1, sttr1,sttttr1, etc
*/
void repetationMatch(char* str1,char* str2,int fd,int tempfile){
    char buffer[1];
    int curr ;
    bool strCheck=false;
    while(read(fd, buffer, 1) != '\0'){
        if(str1[0] == buffer[0]){
            curr = lseek(fd, 0, SEEK_CUR);
            strCheck=true;
            for (int i = 1; i < strlen(str1); ++i)
            {
                read(fd, buffer, 1);
                if(strlen(str1) < 2 || (buffer[0] == '\0' )){
                    strCheck = false;
                    break;
                }
                if(str1[i+1] == '*' && str1[i] != buffer[0] ){
                    if(strlen(str1) > i+2){
                        if(buffer[0] == str1[i+2])
                            i += 2;
                        else
                            strCheck = false;
                    }
                }
                if(str1[i] == '*'){

                    if (str1[i-1] == buffer[0]){
                        while(buffer[0] == str1[i-1])
                            read(fd, buffer, 1);
                        lseek(fd, -1, SEEK_CUR);
                        continue;
                    }
                    else if(str1[i-1] != buffer[0] && strlen(str1) > i+1 && str1[i+1] != buffer[0]){
                        strCheck = false;
                    }
                    else i++;
                }  
                else if (buffer[0] != str1[i]){
                    strCheck = false;
                }
            }
            if (strCheck)
            {
                // delete word from file and add new 
                write(tempfile, str2, strlen(str2));
                strCheck=false;
                continue;
            }
            else{
                strCheck=false;
                lseek(fd, curr-1, SEEK_SET);
                read(fd, buffer, 1);
            }
        }
       
        
        if (!strCheck){
            write(tempfile, buffer, 1);
        }
        
    }

}