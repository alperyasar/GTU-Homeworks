/*********************************************************************************
*                                                                                *
*                               ALPER YAŞAR                                      *
*                       GEBZE TECHNICAL UNİVERSITY                               *
*                               151044072                                        *
*                           SYSTEM PROGRAMMING                                   *
*                                   HW5                                          *
*                                                                                *
**********************************************************************************/

/*
    // for running the file
    $./hw5 -i filePath1 -j filePath2 -o output -n 4 -m 2
*/

#include "hdr.h"

#define PI 3.1415926535

int **matrix1,**matrix2,**resMat;
double **resIM,**resRE;
int secPart=0;

static pthread_mutex_t mtx; //mutexes for all florists.
static pthread_cond_t cond; //condition variables  for all florists.
pthread_t *tmp;
int main(int argc, char *argv[]){
    time_t begin,end;
    clock_t t = clock();
    time(&begin);
    int option;
    char string[100];
 //   int writeRes;

    /*Getting command line arguments.*/
    while ((option = getopt(argc, argv, ":i:j:o:n:m:")) != -1)
    {
        switch (option)
        {
            case 'i':
                filePath1 = optarg;
                break;
            case 'j':
                filePath2 = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case 'm':
                m = atoi(optarg);
                break;
            case '?':
                perror("It does not fit format! Format must be :./hw5 -i filePath1 -j filePath2 -o output -n 4 -m 2\n");
                exit(EXIT_FAILURE);
                break;
        }
    }
    /*This condition to control format of command line arguments.*/
    if ((optind != 11))
    {
        perror("It does not fit format! Format must be :./hw5 -i filePath1 -j filePath2 -o output -n 4 -m 2\n");
        exit(EXIT_FAILURE);
    }
    if(n <= 2){
        fprintf(stderr, "'n' value must be bigger than 2\n");
        exit(EXIT_FAILURE);
    }
    if(m < 2){
        fprintf(stderr, "'m' value must be bigger than 1\n");
        exit(EXIT_FAILURE);
    }


          //  sigset_t origMask, blockMask;
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");


    /*Opening input file.*/
    if ((fd1 = open(filePath1, O_RDONLY)) == -1)
    {
        perror("Failed to open input file in main.\n");
        exit(EXIT_FAILURE);
    }
        /*Opening input file.*/
    if ((fd2 = open(filePath2, O_RDONLY)) == -1)
    {
        perror("Failed to open input file in main.\n");
        exit(EXIT_FAILURE);
    }
    outputFd = open(outputFile, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR |  S_IWGRP | S_IWOTH);
    if (outputFd  == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    matrix1 = allocMatrix(fd1);
    matrix2 = allocMatrix(fd2);
    resMat = allocMatrix(-1);
    resRE = allocDoubleMatrix();
    resIM = allocDoubleMatrix();
    int r=pow(2,n);
    fprintf(stdout, "Two matrices of size %dx%d have been read. The number of threads is %d\n", r,r,m);

    int mtxCheck=pthread_mutex_init (&mtx, NULL);             
    if(mtxCheck!=0){
        perror("Error for thread mutex initialization!");
        exit(EXIT_FAILURE);
    }
    mtxCheck=pthread_cond_init (&cond, NULL);
    if(mtxCheck!=0){
        perror("Error for condition variable initialization!");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_lock(&mtx);
    pthread_t thread[m];
    int s, i;
    /*Creating 6 threads for chefs.*/
    int save[m];
    for (i = 0; i < m; i++)
    {
        save[i] = i;
        if ((s = pthread_create(&thread[i], NULL, calculation,(void*) &save[i])) != 0)
        {
            fprintf(stderr, "Failed to pthread_create operation in main.\n");
            exit(EXIT_FAILURE);
        }
    }
    tmp = thread;
    /*Waiting for chefs by main thread.*/
    for (i = 0; i < m; i++)
    {
        if ((s = pthread_join(thread[i], NULL)) != 0)
        {
            fprintf(stderr, "Pthread_join error in main%d\n",i );
            exit(EXIT_FAILURE);
        }
    }
    

    
    for (i = 0; i < r; ++i)
    {
        for (int j = 0; j < r; ++j)
        {
            memset(string, 0, sizeof (string));
            snprintf(string, 100, "%.3f + j(%.3f),", resRE[i][j],resIM[i][j]);               //print to buffer 
            write(outputFd, string, strlen(string));
        }
        write(outputFd,"\n", 1);
    }
    time(&end);
    double time_spent = difftime(end, begin);
    t = clock() - t;
    time_spent += ((double)t)/CLOCKS_PER_SEC;
    fprintf(stdout, "The process %ld has written the output file. The total time spent is %.4lf seconds.\n",(long) getpid(), time_spent);
    exitProcess();
    return 0;
}

static void *calculation(void *arg){
    time_t begin,end;
    clock_t t = clock();
    time(&begin);
    int index = *((int *)arg);
    int r=pow(2,n);
    int start,finish; // for column

    start = ((int)(r/m))*index;
    if(index == m-1){
        finish = r;
    }
    else{
        finish = (r/m)*(index+1);
    }

    int temp;
    for (int i = start; i < finish; ++i)
    {
        for (int k = 0; k < r; ++k)
        {
            temp =0;
            for (int j = 0; j < r; ++j)
            {
                temp += matrix1[k][j]*matrix2[j][i];
            }
            resMat[k][i] = temp; 
        }       
    }
    time(&end);
    double time_spent = difftime(end, begin);
    t = clock() - t;
    time_spent += ((double)t)/CLOCKS_PER_SEC;
    fprintf(stdout, "Thread %d has reached the rendezvous point in %0.4lf seconds.\n", index+1, time_spent);
    if(++secPart == m){
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx); //unlock mutex.
    }
    pthread_cond_wait(&cond,&mtx);
    fprintf(stdout, "Thread %d is advancing to the second part\n", index+1);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx); //unlock mutex.
    time(&begin);
    for (int x = start; x < finish; ++x)
    {
        
        for (int y = 0; y < r; ++y)
        {
            float ak=0; 
            float bk=0;
            for (int z = 0; z < r; ++z)
            {
                for (int t = 0; t < r; ++t)
                {
                    float x1=-2.0*PI*x*z/(float)r;
                    float y1=-2.0*PI*y*t/(float)r;
                    ak+=resMat[z][t]*cos(x1+y1);
                    bk+=resMat[z][t]*1.0*sin(x1+y1);
                }       
            }
            resRE[x][y]=ak;
            resIM[x][y]=bk;
        }       
    }
    time(&end);
    time_spent = difftime(end, begin);
    t = clock() - t;
    time_spent += ((double)t)/CLOCKS_PER_SEC;
    fprintf(stdout, "Thread %d has has finished the second part in %0.4lf seconds.\n", index+1, time_spent);
    pthread_exit(0);
}
/*This handler for SIGINT signals*/
void handler(int sig) {
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx); //unlock mutex.
    if (sig == SIGINT){
        fprintf(stderr, "Process %ld received signal %d (%s)\n",
        (long) getpid(), sig, strsignal(sig));
    }
    /*Waiting for chefs by main thread.*/
    int s;
    for (int i = 0; i < m; i++)
    {
        if ((s = pthread_join(tmp[i], NULL)) != 0)
        {
            fprintf(stderr, "Pthread_join error in main%d\n",i );
            exit(EXIT_FAILURE);
        }
    }
    exitProcess();
    exit(EXIT_SUCCESS);
}

void exitProcess(){
    deAllocMatrix(matrix1);
    deAllocMatrix(matrix2);
    deAllocMatrix(resMat);
    deAllocDoubleMatrix(resRE);
    deAllocDoubleMatrix(resIM);

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);
    if (close(fd1) == -1)
        perror("File close"); 
    if (close(fd2) == -1)
        perror("File close");
    if (close(outputFd) == -1)
        perror("File close");
}

int **allocMatrix(int fd){
    int **arr;
    int r =  (int) pow(2,n);
    char str[r];

    if(fd == -1){
        arr = (int**) malloc(r * sizeof(int*));
        for (int i = 0; i < r; ++i) 
            arr[i] = (int*)malloc(r * sizeof(int));
        return arr;
    }
    arr = (int**) malloc(r * sizeof(int*));
    for (int i = 0; i < r; ++i)
    {
        arr[i] = (int*)malloc(r * sizeof(int));
        if(read(fd, str, r) != r){
            fprintf(stderr, "File is not big enough.\n");
            exit(EXIT_FAILURE);
        }
        else
            for (int j = 0; j < r; ++j)
                arr[i][j] = (int) str[j];
    }
    return arr;
}
void deAllocMatrix(int **arr){
    int r =  (int) pow(2,n);
    for (int i = 0; i < r; ++i)
        if(arr[i] != NULL)
            free(arr[i]);
    free(arr);
}

double **allocDoubleMatrix(){
    double **arr;
    int r =  (int) pow(2,n);
    arr = (double**) malloc(r * sizeof(double*));
    for (int i = 0; i < r; ++i) 
        arr[i] = (double*)malloc(r * sizeof(double));

    return arr;
}
void deAllocDoubleMatrix(double **arr){
    int r =  (int) pow(2,n);
    for (int i = 0; i < r; ++i)
        if(arr[i] != NULL)
            free(arr[i]);
    free(arr);
}