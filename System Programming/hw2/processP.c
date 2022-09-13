#include "hdr.h"

char *pos[10];
pid_t childPid; /* PID of waited for child */

void collectData(int temp);
void FrobeniusNorm();
int main(int argc, char *argv[]) { 
    char *inputFile,*outputFile;
    int option; 
    int fdInput,fdOutput;
    char buffer[1];
      //  sigset_t origMask, blockMask;
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");


    /*getting command line arguments.*/
    while((option = getopt(argc, argv, ":i:o:")) != -1){ 
        switch(option){
            case 'i':
                inputFile=optarg;
                break;
            case 'o': 
                outputFile=optarg;
                break;   
            case '?': 
                perror("It does not fit format!Format must be: ./program -i inputPath -o outputPath\n");
                exit(EXIT_FAILURE);
                break;
            }
    }
    if((optind!=5)){
        errno=EINVAL;
        perror("CommandLine argument numbers must be 5! Format must be: ./program -i inputPath -o outputPath\n");
        exit(EXIT_FAILURE);
    } 
                                            
    /*Open input file*/
    if((fdInput=open(inputFile,O_RDONLY))==-1){
        perror("Failed to open input file in main.\n");
        exit(EXIT_FAILURE);
    }
    inputFd=fdInput; /*Copy of input file descriptor in global variable.*/
    inputPath = (char*)malloc((strlen(inputFile)+1) * sizeof(char));
    strcpy(inputPath,inputFile);    
    /*Open output file.*/ 
    if((fdOutput=open(outputFile,O_RDWR | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR |  S_IWGRP | S_IWOTH))==-1){
        perror("Failed to open output file in main.\n");
        exit(EXIT_FAILURE);
    }
    outputPath = (char*)malloc((strlen(outputFile)+1) * sizeof(char));
    strcpy(outputPath,outputFile); 
    outputFd=fdOutput;  /*Copy of output file descriptor in global variable.*/


    int byteCount = 0;
    int x=0,y=0; /* Number of children so far waited for */
    
    for (int i = 0; i < 10; i++)
        pos[i] = (char*)malloc(3 * sizeof(char));
    fprintf(stderr, "Process %ld reading %s\n",(long)getpid(),argv[2]);
 //   int k=0;
    while (read(inputFd, buffer, 1) != '\0') { /* Create one child for each argument */
        if(++byteCount == 30){
        //    k++;
            switch (fork()) {
            case -1:
                perror("fork");
                _exit(EXIT_FAILURE);
            case 0: /* Child sleeps for a while then exits */
           //     sleep(k);
                pos[x][2]= buffer[0];
                pos[10] = NULL;
                if(execve("./covarianceMatrix", argv, pos) == -1)
                    perror("execve");

                _exit(EXIT_SUCCESS);
            default: /* Parent just continues around loop */
                break;
            }  
            byteCount = 0; x=0; y=0;
            
            
        }
        else {
            if(y==3){
                y=1;++x;
                pos[x][0]=  buffer[0];
            }
            else{
                pos[x][y]= buffer[0];
                y++;
            }

        }
        
    }
    collectData(2);
    return 0;
} 
    
/*This handler for SIGINT signals*/
void handler(int sig) {
    if (sig == SIGINT){
        fprintf(stderr, "Process %ld received signal %d (%s)\n",
        (long) getpid(), sig, strsignal(sig));
        collectData(1);
    }
    exit(EXIT_SUCCESS);
}

void collectData(int temp){
       // printf("Handler caught SIGUSR1 signal.\n"); 

    for (;;) { /* Parent waits for each child to exit */
        childPid = wait(NULL);
        if (childPid == -1) {
            if (errno == ECHILD) {
                if (temp == 1)
                {
                    unlink (outputPath);
                    break;
                }
                else {
                    fprintf(stdout, "Reached EOF, collecting outputs from %s\n",outputPath); 
                    FrobeniusNorm();
                }
                break;
            } else { /* Some other (unexpected) error */
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    //    printf(" wait() returned child PID %ld (numDead=%d)\n",  (long) childPid, numDead);
    }
    if(close(inputFd)<0){
        perror("Close input file error in SIGTERM signal handler.\n");
        exit(EXIT_FAILURE);
    }
    if(close(outputFd)<0){
        perror("Close output file error in SIGTERM signal handler.\n");
        exit(EXIT_FAILURE);
    } 
    for (int i = 0; i < 10; i++)
        free(pos[i]);
    free(inputPath);
    free(outputPath);
}

void FrobeniusNorm(){
    int i=0,j=0;
    float num,sum=0;
    int k=0;
    float res[512];
   // int cur,cur2;
    char buffer[30];
    lseek(outputFd, 0, SEEK_SET); 
    while (read(outputFd, &buffer[i], 1) == 1) {
        /* end of line */

        if (buffer[i] == '\n') {   
            i=-1; 
            char * token = strtok(buffer, " ");
            if(isdigit(token[0]) || token[0] == '-'){
                j += 3;
                num = atoi(token);
                sum += num*num;

                printf("**%.2f\n", num);
                num = atoi(strtok(NULL, " "));
                sum += num*num;
                printf("**%.2f\n", num);
                num = atoi(strtok(NULL, " "));
                sum += num*num;
                printf("**%.2f\n", num);
            }
            memset(buffer, 0, sizeof (buffer));
        }
        if(j==9){
            j=0;
            res[k] = sqrt(sum);
            printf("--%f\n", res[k]);
            k++;
            sum = 0;
        }
        i++;
    }
    int value1,value2;
    float dif;
    value1 = 0;
    value2 = 1;
    dif = res[0] - res[1];
    if (dif < 0)
        dif = dif * -1;
    for (i = 0; i < k-1; ++i)
    {
        for(j=i+1;j < k;j++){
            float temp2 = res[j] - res[i];
            if(temp2 < 0)
                temp2 = temp2 * -1;
            if(temp2 < dif){
                value1 = i;
                value2 = j;
                dif = temp2;
            }
        }
    }

    lseek(outputFd, 0, SEEK_SET); 
    int first = 0,lastArr[9];
    j=0;
    k=0;
    i=0;
    fprintf(stdout, "The closest 2 matrices are ");
    memset(buffer, 0, sizeof (buffer));
    while (read(outputFd, &buffer[i], 1) == 1) {
        /* end of line */

        if (buffer[i] == '\n') {   
            i=-1; 
            char * token = strtok(buffer, " ");
            if(isdigit(token[0]) || token[0] == '-'){
                
                lastArr[j] = atoi(token);
                lastArr[j+1] = atoi(strtok(NULL, " "));
                lastArr[j+2] = atoi(strtok(NULL, " "));
                j += 3;
            }
            memset(buffer, 0, sizeof (buffer));
        }
        if(j==9){
            j=0;
            if(k == value1 || k == value2){
                fprintf(stdout, "{" );
                fprintf(stdout, "{{%d,%d,%d},{%d,%d,%d},{%d,%d,%d}} ",
                        lastArr[0],lastArr[1],lastArr[2],
                        lastArr[3],lastArr[4],lastArr[5],
                        lastArr[6],lastArr[7],lastArr[8] );
                if (first == 0)
                {
                    fprintf(stdout, "and ");
                    first++;
                }
            }
            k++;
            sum = 0;
        }
        i++;
    }
    fprintf(stdout, ", and their distance is %f.\n",dif );
}