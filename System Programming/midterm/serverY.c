
#include "hdr.h"

pid_t childPid; /* PID of waited for child */

#define BD_NO_CHDIR 01 /* Don't chdir("/") */
#define BD_NO_CLOSE_FILES 02 /* Don't close all open files */
#define BD_NO_REOPEN_STD_FDS 04 /* Don't reopen stdin, stdout, and
 stderr to /dev/null */
#define BD_NO_UMASK0 010 /* Don't do a umask(0) */
#define BD_MAX_CLOSE 8192

static int *glob_var;
static int *total_req;
static int *invertible;
static int *forw;
static int *pid;
static int *killtouse;
struct flock fl1,fl2;
int filedes2[2];
int fdOutput;
int pids[100];
int sizepid;
int tempfd;
int main(int argc, char *argv[]){
    char **temp = NULL;
    int opt, yProcessChild,zProcessChild,sleepTime;
    int serverFd, clientFd;
    int seqNum = 0; /* This is our "service" */
    int writeRes;
    char string[300];
    int maxfd, fd;
    
    time_t begin;

    struct sigaction sa;
    int filedes1[2];

    /*
     *  -s: denotes the path (relative or absolute) of the server fifo
     *  -o: denotes the path (relative or absolute) of the log file to record all server output/errors
     *  -p: denotes the pool size of serverY (p >= 2)
     *  -r: denotes the pool size of serverZ (r >= 2)
     *  -t: denotes the sleep duration (in seconds)
    */
    int y=0,tempfd=0;
    while ((opt = getopt(argc, argv, "s:o:p:r:t:")) != -1)
    {
        y++;
        switch (opt)
        {
            case 's':
                pathToServerFifo = optarg;
                break;
            case 'o':
                inputPath = optarg;
                break;
            case 'p':
                yProcessChild = atoi(optarg);
                tempfd = 2*(y-1)+2;
                if(yProcessChild<2){
                    sprintf(string,"-p: denotes the pool size of serverY (p >= 2).\nYour child is %d\n",yProcessChild);
                    writeRes=write(2, string, strlen(string));
                    if(writeRes==-1){
                        exit(EXIT_FAILURE);
                    }
                    exit(EXIT_FAILURE);
                }
                break;
            case 'r':
                zProcessChild = atoi(optarg);
                if(zProcessChild<2){
                    sprintf(string,"-p: denotes the pool size of serverZ (r >= 2).\nYour child is %d\n",zProcessChild);
                    writeRes=write(2, string, strlen(string));
                    if(writeRes==-1){
                        exit(EXIT_FAILURE);
                    }
                    exit(EXIT_FAILURE);
                } 
                break;
            case 't':
                sleepTime = atoi(optarg);
                if(sleepTime<0){
                    sprintf(string,"-t: denotes the sleep duration (in seconds) : %d\nTime can not be under 0 \n",sleepTime);
                    writeRes=write(2, string, strlen(string));
                    if(writeRes==-1){
                        exit(EXIT_FAILURE);
                    }
                    exit(EXIT_FAILURE);
                } 
                break;
            case ':':
                sprintf(string,"Option needs a value %s\n./serverY -s pathToServerFifo -o pathToLogFile -p 4 -r 4 -t 2\n",optarg);
                writeRes=write(2, string, strlen(string));
                if(writeRes==-1){
                    exit(EXIT_FAILURE);
                }
            case '?':
                sprintf(string,"Unknown option: %c\n./serverY -s pathToServerFifo -o pathToLogFile -p 4 -r 4 -t 2\n",optopt);
                writeRes=write(2, string, strlen(string));
                if(writeRes==-1){
                    exit(EXIT_FAILURE);
                }
        }
    }
    
    switch (fork()) {
        case -1:
            perror("fork");
            _exit(EXIT_FAILURE);
        case 0: 
            sizepid = yProcessChild +1;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;
            sa.sa_handler = handler;
            if (sigaction(SIGINT, &sa, NULL) == -1)
                perror("sigaction");
            if (sigaction(SIGTERM, &sa, NULL) == -1)
                perror("sigaction");

            memset(&fl1,0 , sizeof(fl1));
            memset(&fl2,0 , sizeof(fl2));

            fl1.l_type = F_WRLCK;
            fl2.l_type = F_UNLCK;
       //     global variable for shared memory
            glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
            *glob_var = 0;
            total_req = mmap(NULL, sizeof *total_req, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
            *total_req = 0;
            invertible = mmap(NULL, sizeof *invertible, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
            *invertible = 0;
            forw = mmap(NULL, sizeof *forw, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
            *forw = 0;
            pid = mmap(NULL, sizeof *pid, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
            *pid = 0;
            killtouse = mmap(NULL, sizeof *killtouse, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
            *killtouse = 1;
            if (pipe(filedes1) == -1) /* Create the pipe */
                perror("pipe");
            if (pipe(filedes2) == -1) /* Create the pipe */
                perror("pipe");
            //  sigset_t origMask, blockMask;
            if((fdOutput=open(inputPath,O_RDWR | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR |  S_IWGRP | S_IWOTH))==-1){
                perror("Failed to open output file in main.\n");
                exit(EXIT_FAILURE);
            }
            time(&begin);
            fcntl(fdOutput,F_SETLKW,&fl1);
            sprintf(string,"%sServer Y (%s, p=%d, t=%d) started\n",ctime(&begin),inputPath, yProcessChild,sleepTime);
            
    
            writeRes=write(fdOutput, string, strlen(string));
            if(writeRes==-1){
                exit(EXIT_FAILURE);
            } 
            fcntl(fdOutput,F_SETLKW,&fl2);
            

            switch(fork()){
                case -1:
                    perror("fork");
                    _exit(EXIT_FAILURE);
                case 0:
                    if (close(filedes2[1]) == -1) /* Close unused write end */
                        perror("close");
                    *pid = (int)getpid();
                    char buf[4];
                    snprintf(buf, sizeof(filedes2[0]), "%d", filedes2[0]); 
                    argv[tempfd] = buf;
                    if(execve("./serverZ", argv, temp) == -1)
                        perror("execve");
                    _exit(EXIT_SUCCESS);
                default: /* Parent just continues around loop */
                    break;

            }
            pids[0] = *pid;
            for (int i = 0;i<yProcessChild;i++){
                switch (fork()) {
                    case -1:
                        perror("fork");
                        _exit(EXIT_FAILURE);
                    case 0: /* Child sleeps for a while then exits */
                   //     sleep(k);
                        *pid = (int)getpid();
                        if (close(filedes1[1]) == -1) /* Close unused write end */
                            perror("close");
                        int numRead;
                        for (;;){
                            numRead = read(filedes1[0], &req, sizeof(struct request));
                            (*glob_var)++;
                            fcntl(fdOutput,F_SETLKW,&fl1);
                            time(&begin);
                            sprintf(string,"%sY:Worker PID#%d is handling client PID#%d, matrix size %dx%d, pool busy %d/%d\n", 
                                            ctime(&begin),(int)getpid(),req.pid,req.arraySize,req.arraySize,*glob_var,yProcessChild);
                            
                            writeRes=write(fdOutput, string, strlen(string));
                            if(writeRes==-1){
                                exit(EXIT_FAILURE);
                            } 
                            fcntl(fdOutput,F_SETLKW,&fl2);
                            if (numRead == -1)
                                perror("read1");
                            clientFd = open(clientPath, O_WRONLY);
                            if (clientFd == -1) { /* Open failed, give up on client */
                               /* sprintf(string,"open %s\n", clientPath);
                                writeRes=write(STDERR_FILENO, string, strlen(string));
                                if(writeRes==-1){
                                    exit(EXIT_FAILURE);
                                }       */
                                continue;
                            }
                            /* Send response and close FIFO */
                            resp.inv = isMatrixInvertible();
                            fcntl(fdOutput,F_SETLKW,&fl1);
                            time(&begin);
                            
                            if(resp.inv){
                                sprintf(string,"%sY:Worker PID#%d responding to client PID#%d, the matrix is invertible\n", 
                                            ctime(&begin),(int)getpid(),req.pid);
                                (*invertible)++;
                            }

                            else sprintf(string,"%sY:Worker PID#%d responding to client PID#%d, the matrix is NOT invertible\n", 
                                            ctime(&begin),(int)getpid(),req.pid);
                            
                            writeRes=write(fdOutput, string, strlen(string));
                            if(writeRes==-1){
                                exit(EXIT_FAILURE);
                            } 
                            fcntl(fdOutput,F_SETLKW,&fl2);
                            if (write(clientFd, &resp, sizeof(struct response)) != sizeof(struct response)){
                                sprintf(string,"Error writing to FIFO %s\n", inputPath);
                                writeRes=write(STDERR_FILENO, string, strlen(string));
                                if(writeRes==-1)
                                    exit(EXIT_FAILURE);
                                
                            }
                            if (close(clientFd) == -1)
                                perror("close");
                            sleep(sleepTime);
                            (*glob_var)--;
                            
                        }
                 /*       */

                        _exit(EXIT_SUCCESS);
                    default: /* Parent just continues around loop */
                        break;
                }  
                pids[i] = *pid;
            }
            if (close(filedes1[0]) == -1) /* Close unused write end */
                perror("close");
            if (close(filedes2[0]) == -1) /* Close unused write end */
                perror("close");
            
            umask(0); /* So we get the permissions we want */
            if (mkfifo(pathToServerFifo, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) == -1 && errno != EEXIST){
                sprintf(string,"mkfifo %s\n", pathToServerFifo);
                writeRes=write(2, string, strlen(string));
                if(writeRes==-1){
                    exit(EXIT_FAILURE);
                } 
            } // Error check omitted
          /*  if (signal(SIGPIPE, SIG_IG_IGN) == SIG_ERR)
                perror("signal");*/
            tempfd = filedes2[1];
            for (;;) { /* Parent waits for each child to exit */
              
                serverFd = open(pathToServerFifo, O_RDONLY);
                if (serverFd == -1){
                    sprintf(string,"open %s\n", pathToServerFifo);
                    writeRes=write(2, string, strlen(string));
                    if(writeRes==-1){
                        exit(EXIT_FAILURE);
                    } 
                }

                
             /*   dummyFd = open(pathToServerFifo, O_WRONLY);
                if (dummyFd == -1)
                    fprintf(stderr, "open %s\n", pathToServerFifo);*/
                read(serverFd, &req, sizeof(struct request));
                if (sizeof(req) != sizeof(struct request)) {
                    sprintf(string,"Error reading request; discarding %d\n",serverFd);
                    writeRes=write(2, string, strlen(string));
                    if(writeRes==-1){
                        exit(EXIT_FAILURE);
                    } 
                    continue; /* Either partial read or error */
                }
                seqNum += req.arraySize; /* Update our sequence number */
                if((*glob_var) != yProcessChild){
                    (*total_req)++;
                    write(filedes1[1], &req, sizeof(struct request));
                }
                else{
                    (*forw)++;
                    fcntl(fdOutput,F_SETLKW,&fl1);
                    time(&begin);                    
                    sprintf(string,"%sY:Forwarding request of client PID#%d, to serverZ matrix size %dx%d, pool busy %d/%d\n", 
                                    ctime(&begin),req.pid,req.arraySize,req.arraySize,*glob_var,yProcessChild);
                    
                    writeRes=write(fdOutput, string, strlen(string));
                    fcntl(fdOutput,F_SETLKW,&fl2);
                    write(filedes2[1], &req, sizeof(struct request));

                }
            
            }

            _exit(EXIT_SUCCESS);
        default: /* Parent just continues around loop */
           _exit(EXIT_SUCCESS);
    }
      
    if (!(BD_NO_UMASK0))
        umask(0); /* Clear file mode creation mask */
    if (!(BD_NO_CHDIR))
        chdir("/"); /* Change to root directory */
    if (!(BD_NO_CLOSE_FILES)) { /* Close all open files */
        maxfd = sysconf(_SC_OPEN_MAX);
        if (maxfd == -1) /* Limit is indeterminate... */
            maxfd = BD_MAX_CLOSE; /* so take a guess */
        for (fd = 0; fd < maxfd; fd++)
            close(fd);
    }
    if (!(BD_NO_REOPEN_STD_FDS)) {
        close(STDIN_FILENO); /* Reopen standard fd's to /dev/null */
        fd = open("/dev/null", O_RDWR);
        if (fd != STDIN_FILENO) /* 'fd' should be 0 */
            return -1;
        if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
            return -1;
        if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
            return -1;
    }
    return 0;
}

/*This handler for SIGUSR1 and SIGUSR2 signals*/
void handler(int sig) {
    if(*killtouse == 1){
        *killtouse = 0;
        req.arraySize = -1;
        write(filedes2[1], &req, sizeof(struct request));
        sleep(0.1);
        fcntl(fdOutput,F_SETLKW,&fl1);
        char string[300];
        sprintf(string,"SIGINT received, terminating Z and exiting server Y. Total requests handled: %d, %d invertible %d not. %d requests were forwarded.\n", 
                        *total_req,*invertible,*total_req - *invertible,*forw);
        
        write(fdOutput, string, strlen(string));

        fcntl(fdOutput,F_SETLKW,&fl2);
        sleep(0.1);
        for(int i =1 ; i< sizepid;i++){
            kill(pids[i],SIGTERM);
        }
        munmap(glob_var, sizeof *glob_var);
        munmap(total_req, sizeof *total_req);
        munmap(invertible, sizeof *invertible);
        munmap(forw, sizeof *forw);
        munmap(pid, sizeof *pid);
        removeFifo();
        exit(EXIT_SUCCESS);
    
    }
    
    munmap(glob_var, sizeof *glob_var);
    munmap(total_req, sizeof *total_req);
    munmap(invertible, sizeof *invertible);
    munmap(forw, sizeof *forw);
    munmap(pid, sizeof *pid);
    removeFifo();
    exit(EXIT_SUCCESS);
}

void removeFifo()/* Invoked on exit to delete client FIFO */
{
   // unlink(pathToServerFifo);
 //   unlink(inputPath);
}

void findCoFactor(int n,int mat[][n], int mat2[][n], int p, int q) {
   int i = 0, j = 0;
   for (int row = 0; row < n; row++) {
      for (int col = 0; col < n; col++) {
         if (row != p && col != q) {
            mat2[i][j++] = mat[row][col];
            if (j == n - 1) {
               j = 0;
               i++;
            }
         }
      }
   }
}
int getDeterminant(int n,int mat[][n]) {
   int determinant = 0;
   if (n == 1)
      return mat[0][0];
   int temp[n][n];
   int sign = 1;
   for (int f = 0; f < n; f++) {
      findCoFactor(n,mat, temp, 0, f);
      determinant += sign * mat[0][f] * getDeterminant( n - 1,temp);
      sign = -sign;
   }
   return determinant;
}
bool isMatrixInvertible() {
    int size = req.arraySize;
    int newArr[size][size];
    for (int i = 0; i < req.arraySize; ++i)
    {
        for (int j = 0; j < req.arraySize; ++j)
        {
            newArr[i][j] = req.datas[(i*size)+j];
        }
    }
   if (getDeterminant(size,newArr) != 0)
      return true;
   else
      return false;
}