#include "hdr.h"
/*
    first 'make' for compile
    after that run server as deamon process on background
$: ./serverY -s /tmp/server -o path.log -p 4 -r 4 -t 5
    then run client
$: ./client -s /tmp/server -o test/data.csv
    
    after all run 
    for exiting from backgroun
$: ps -ef | grep serverY
    check process and 
$: kill pid

*/

void readDatas();
void releaseMemory(int size);
int matrixSize=1;
static char clientFifo[100];
int main(int argc, char *argv[]){
    time_t begin,end;
    clock_t t = clock();
    time(&begin);
	//girdi kontrol..
    int opt;
    int serverFd,dpFd;
    int writeRes;
    char string[300];

	while ((opt = getopt(argc, argv, "s:o:")) != -1)
    {
        switch (opt)
        {
            case 's':
                pathToServerFifo = optarg;
                break;
            case 'o':
                inputPath = optarg;
                break;
            case ':':
                sprintf(string,"Option needs a value %s\n./client -s pathToServerFifo -o pathToLogFile\n",optarg);
                writeRes=write(2, string, strlen(string));
                if(writeRes==-1){
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_FAILURE);
            case '?':
                sprintf(string,"Unknown option: %c\n./client -s pathToServerFifo -o pathToDataFile\n",optopt);
                writeRes=write(2, string, strlen(string));
                if(writeRes==-1){
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_FAILURE);
        }
    }
    readDatas();
     /* Create our FIFO (before sending request, to avoid a race) */
    umask(0); /* So we get the permissions we want */
    req.pid=getpid();
    snprintf(clientFifo, strlen(clientPath) + 20, clientPath, (long) getpid());
    // creating fifo for responds
    if (mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) == -1 && errno != EEXIST){
        sprintf(string,"mkfifo %s\n", clientFifo);
        writeRes=write(2, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        } 
    }
    if (atexit(removeFifo) != 0)
        perror("atexit");
    /* Construct request message, open server FIFO, and send request */

    serverFd = open(pathToServerFifo, O_WRONLY);

    if (serverFd == -1){
        sprintf(string,"open %s\n", pathToServerFifo);
        writeRes=write(2, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        } 
    }
    sprintf(string,"Client PID#%ld () is submitting a %dx%d matrix",(long) getpid(),req.arraySize,req.arraySize);
    if (write(serverFd, &req, sizeof(struct request)) != sizeof(struct request))
        perror("Can't write to server");
    if (close(serverFd) == -1)
        perror("2close");
    /* Open our FIFO, read and display response */
    dpFd = open(clientFifo, O_RDONLY);
    if (read(dpFd, &resp, sizeof(struct response)) != sizeof(struct response))
        perror("Can't read response from server");
    removeFifo();
    time(&end);
    double time_spent = difftime(end, begin);
    t = clock() - t;
    time_spent += ((double)t)/CLOCKS_PER_SEC;
    if(resp.inv)
        sprintf(string,"Client PID#%ld () the matrix is invertible, total time %f seconds, goodbye.\n",(long) getpid(),time_spent);
    else
        sprintf(string,"Client PID#%ld () the matrix is non-invertible, total time %f seconds, goodbye.\n",(long) getpid(),time_spent);
    if (close(dpFd) == -1)
        perror("close");
    writeRes=write(STDOUT_FILENO, string, strlen(string));
    if(writeRes==-1){
        exit(EXIT_FAILURE);
    } 
    releaseMemory(matrixSize);
    return 0;
}

void readDatas(){
    /*Open input file*/
    char buffer[1];
    if((inputFd=open(inputPath,O_RDONLY))==-1){
        perror("Failed to open input file in main.\n");
        exit(EXIT_FAILURE);
    }
    
    while(read(inputFd, buffer, 1) != '\0' && buffer[0] != '\n'){
        if(buffer[0] == ',')
            matrixSize++;
    }
    // in each of its first n rows (n >= 2). 
    if(matrixSize < 2){
        fprintf(stderr, "n < 2\n");
        _exit(EXIT_FAILURE);
    }
    req.arraySize = matrixSize;
    // passing file characters until  to integer.
    lseek(inputFd, 0, SEEK_SET);
    char buf[8];
    int i=0;
    int j=0,k=0;
    read(inputFd, &buf[i], 1);
    while(!isdigit(buf[i]))
        read(inputFd, &buf[i], 1);

    i++;
    while (read(inputFd, &buf[i], 1) == 1) {
        /* end of line */

        if (buf[i] == '\n' || buf[i] == ',') {     
            if (buf[i] == '\n')
            {
               k=0;
            }           
            buf[i] = '\0';
            req.datas[j]= atoi(buf);
            memset(buf, 0, sizeof (buf));
            i=-1;
            j++;
            k++;
        }
        if (k == matrixSize+1)
        {
            fprintf(stderr, "This is not square matrix\n" );
            releaseMemory(j);
            _exit(EXIT_FAILURE);
        }
        i++;
    } 
    req.datas[j]= atoi(buf);
}

void releaseMemory(int size){
    removeFifo();
}

void removeFifo()/* Invoked on exit to delete client FIFO */
{
    unlink(clientFifo);
}