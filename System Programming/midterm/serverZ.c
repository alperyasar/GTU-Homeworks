#include "hdr.h"

pid_t childPid; /* PID of waited for child */

static int *glob_var;
static int *total_req;
static int *invertible;

struct request2 { /* Request (client --> server) */
    int datas[1024];
    int arraySize;
    pid_t pid; 
    struct request2* next;

};
static int *pid;

int pids[100];
int sizepid;
static struct request2 *req1;

    struct flock fl1,fl2;
int main(int argc, char *argv[]){


    int opt,fd, zProcessChild,sleepTime;
    int numRead,filedes[2];
    int writeRes,clientFd,outputFd;
    char string[300];
    time_t begin;
 //   struct request2 *temp,temp2;

    memset(&fl1,0 , sizeof(fl1));
    memset(&fl2,0 , sizeof(fl2));

    fl1.l_type = F_WRLCK;
    fl2.l_type = F_UNLCK;
    glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *glob_var = 0;
    total_req = mmap(NULL, sizeof *total_req, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *total_req = 0;
    invertible = mmap(NULL, sizeof *invertible, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *invertible = 0;
    pid = mmap(NULL, sizeof *pid, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *pid = 0;
    /*
     *  -s: denotes the path (relative or absolute) of the server fifo
     *  -o: denotes the path (relative or absolute) of the log file to record all server output/errors
     *  -p: denotes the pool size of serverY (p >= 2)
     *  -r: denotes the pool size of serverZ (r >= 2)
     *  -t: denotes the sleep duration (in seconds)
    */

	while ((opt = getopt(argc, argv, "s:o:p:r:t:")) != -1)
    {
        switch (opt)
        {
            case 's':
                pathToServerFifo = optarg;
                break;
            case 'o':
                inputPath = optarg;
                break;
            case 'r':
                zProcessChild = atoi(optarg);
                break;
            case 'p':
                fd = atoi(optarg);
                break;
            case 't':
                sleepTime = atoi(optarg);
                break;
        }
    }
    outputFd = open(inputPath, O_WRONLY | O_APPEND);
    if (outputFd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int kd;
    char* buffer="SharedArea";  
    /*Open  an  object with a specified name for shared memory.*/
    kd = shm_open(buffer,O_CREAT |  O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (kd == -1){
        sprintf(string,"Failed shm_open operation in main!");
        writeRes=write(STDOUT_FILENO, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    } 
    if (ftruncate(kd, sizeof(struct request)) == -1){
        sprintf(string,"ftruncate error in main!");
        writeRes=write(STDOUT_FILENO, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        }
         exit(EXIT_FAILURE);
    } 
    /*Maps the shared memory object into the process’s virtual address space.*/
    req1 = mmap(NULL, sizeof(struct request), PROT_READ | PROT_WRITE,MAP_SHARED, kd, 0); 
    if( MAP_FAILED == req1 ) {
        sprintf(string,"Mmap failed in main function!" );
        writeRes=write(STDOUT_FILENO, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        }
        return EXIT_FAILURE;
    }
        /*Initializes the unnamed semaphores.*/ 
    req1->next  =  NULL;
        //  sigset_t origMask, blockMask;
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");
    if (pipe(filedes) == -1) /* Create the pipe */
        perror("pipe");
    sizepid = zProcessChild;
    for (int i = 0;i<zProcessChild;i++){
        switch (fork()) {
            case -1:
                perror("fork");
                _exit(EXIT_FAILURE);
            case 0: /* Child sleeps for a while then exits */
           //     sleep(k);
            //    fprintf(stdout, " z- Kardeşim pid (%d) giriş yapıyor\n",(int)getpid() );
                *pid = (int)getpid();
                if (close(filedes[1]) == -1) /* Close unused write end */
                    perror("close");
                writeRes=write(1, string, strlen(string));
                if(writeRes==-1){
                    exit(EXIT_FAILURE);
                }
                for (;;){
                    numRead = read(filedes[0], &req, sizeof(struct request));
                    (*glob_var)++;
                    fcntl(outputFd,F_SETLKW,&fl1);
                    time(&begin);
                    sprintf(string,"%sZ:Worker PID#%d is handling client PID#%d, matrix size %dx%d, pool busy %d/%d\n", 
                                    ctime(&begin),(int)getpid(),req.pid,req.arraySize,req.arraySize,*glob_var,zProcessChild);
                    
                    writeRes=write(outputFd, string, strlen(string));
                    if(writeRes==-1){
                        exit(EXIT_FAILURE);
                    }
                    fcntl(outputFd,F_SETLKW,&fl2);
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
                    fcntl(outputFd,F_SETLKW,&fl1);
                    time(&begin);
                    if(resp.inv){
                        sprintf(string,"%sZ:Worker PID#%d responding to client PID#%d, the matrix is invertible\n", 
                                    ctime(&begin),(int)getpid(),req.pid);
                        (*invertible)++;
                    }
                    else sprintf(string,"%sZ:Worker PID#%d responding to client PID#%d, the matrix is NOT invertible\n", 
                                    ctime(&begin),(int)getpid(),req.pid);
                    
                    writeRes=write(outputFd, string, strlen(string));
                    if(writeRes==-1){
                        exit(EXIT_FAILURE);
                    } 
                    fcntl(outputFd,F_SETLKW,&fl2);
                    if (write(clientFd, &resp, sizeof(struct response)) != sizeof(struct response)){
                        sprintf(string,"Error writing to FIFO %s\n", inputPath);
                        writeRes=write(STDERR_FILENO, string, strlen(string));
                        if(writeRes==-1)
                            exit(EXIT_FAILURE);
                        
                    }
                    req1 = req1->next;
                    if (close(clientFd) == -1)
                        perror("close");
                    (*glob_var)--;
                    sleep(sleepTime);
                    
                    
                }
                _exit(EXIT_SUCCESS);
            default: /* Parent just continues around loop */
                break;
        } 
        pids[i] = *pid; 
    }
    if (close(filedes[0]) == -1) /* Close unused write end */
        perror("close");
    for (;;) { /* Parent waits for each child to exit */
       
        numRead = read(fd, &req, sizeof(struct request));

        if(req.arraySize==-1){
            fcntl(outputFd,F_SETLKW,&fl1);
            char string[300];
            sprintf(string,"Z:SIGINT received, exiting server Z. Total requests handled %d, %d invertible %d not.\n", 
                            *total_req,*invertible,*total_req - *invertible);
            
            write(outputFd, string, strlen(string));
           
            fcntl(outputFd,F_SETLKW,&fl2);
            exit(EXIT_SUCCESS);
        }
        else{
            (*total_req)++;
            if((*glob_var) < zProcessChild)
                write(filedes[1], &req, sizeof(struct request));
            if (numRead == -1)
                perror("read");
        }
        
    //    printf(" wait() returned child PID %ld (numDead=%d)\n",  (long) childPid, numDead);
    }
    return 0;
}

/*This handler for SIGUSR1 and SIGUSR2 signals*/
void handler(int sig) {
    
  /*  for(int i =0 ; i< sizepid;i++){
        kill(pids[i],SIGTERM);
    }
    */
    munmap(glob_var, sizeof *glob_var);
    munmap(total_req, sizeof *total_req);
    munmap(invertible, sizeof *invertible);
    munmap(req1, sizeof *req1);
  //  removeFifo();
    exit(EXIT_SUCCESS);
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