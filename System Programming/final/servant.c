/*********************************************************************************
*                                                                                *
*                               ALPER YAŞAR                                      *
*                       GEBZE TECHNICAL UNİVERSITY                               *
*                               151044072                                        *
*                           SYSTEM PROGRAMMING                                   *
*                                   Final                                         *
*                                                                                *
**********************************************************************************/

/*
    // for running the file
    $:./servant -d directoryPath -c 10-19 -r IP -p PORT
*/

#include "hdr.h"
#include <dirent.h>


char *filepath;
char *range,*addr;
int start,finish;
int requestSize =0;
struct dir 
{ 
    char name[50]; 
    int index;
    struct dir* next;
    struct file* fileRoot;
}; 

struct file 
{ 
    int transactionID;
    char type[25];
    char name[250];
    int surface;
    int price;
    int year;
    int month;
    int day; 
    struct file* next;
}; 

struct servantFile
{
    int hasCity;
    char startDate[25];
    char finishDate[25];
    char type[50];
    char city[50];
};
int** queue;  //Client queue.
int* queueSize;

struct dir* dirRoot;
struct dir dirLast;
int sigintFlag;
int startThreadNum=1; //thread number at beginning.
int lastThreadNum=1; //max thread number.
int currRunningNum;  //Current running thread number.
/*Mutexes and condition variables for threads*/ 
static pthread_mutex_t* mtx=NULL; 
static pthread_cond_t* condFull=NULL; 
static pthread_cond_t* condEmpty=NULL; 
pthread_t* thread_server; //Server threads.
int *save;

/*SIGINT handler function */
void handler(){
    sigintFlag=1; //change flag.
  
}

void readFiles();

/*Initializes thread mutexes and condition variables.*/
void initilializeMutexesAndConds(){
    mtx=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*(lastThreadNum+1));
    condFull=(pthread_cond_t*)malloc(sizeof(pthread_cond_t)*(lastThreadNum+1));
    condEmpty=(pthread_cond_t*)malloc(sizeof(pthread_cond_t)*(lastThreadNum+1));
    int i;
    int m1,c,c2;
    for(i=0;i<lastThreadNum+1;i++){
        m1=pthread_mutex_init (&mtx[i], NULL);             
        if(m1!=0){
            fprintf(stderr,"Error for thread mutex initialization!");
            exit(EXIT_FAILURE);
        }
        c=pthread_cond_init (&condEmpty[i], NULL);
        if(c!=0){
            fprintf(stderr,"Error for condition variable initialization!");
            exit(EXIT_FAILURE);
        }  
        c2=pthread_cond_init (&condFull[i], NULL);
        if(c2!=0){
            fprintf(stderr,"Error for condition variable initialization!");
            exit(EXIT_FAILURE);
        }                          
    }          
    currRunningNum=0;
}
/*Initializing queue of file pointer of accept address of socket.*/ 
void initializeQueue(){
    queue=(int**)malloc((lastThreadNum+1)*sizeof(int*));
    int i;
    for(i=0;i<lastThreadNum+1;i++){
        queue[i]=(int*)malloc(500*sizeof(int));
    }

    queueSize=(int*)malloc((lastThreadNum+1)*sizeof(int));
    for(i=0;i<lastThreadNum+1;i++){
        queueSize[i]=0;
   
    }
}
/*Free queue.*/
void freeQueue(){
    int i;
    for(i=0;i<lastThreadNum+1;i++){
        free(queue[i]);

    }
    free(queue);
    free(queueSize);
}
/*Function for comminication between client and server.Messages is sending to client in this function.*/
/*And also reader-writer mechanism is used for informations of database structure.*/
void func(int sockfd) 
{ 
    int size = 0;
    struct servantFile srvF; 
    read(sockfd, &srvF, sizeof(struct servantFile));  //getting 2 nodes that are source and destination nodes from buffer on socket.
    
    struct dir* temp = dirRoot;
    struct file* temp2;
    int startDate=0,finishDate=0;
    char* token = strtok(srvF.startDate, "-");
    startDate += atoi(token);
    token = strtok(NULL, "-");
    startDate += atoi(token)*30;
    token = strtok(NULL, "-");
    startDate += atoi(token)*360; 

    char* token2 = strtok(srvF.finishDate, "-");
    finishDate += atoi(token2);
    token2 = strtok(NULL, "-");
    finishDate += atoi(token2)*30;
    token2 = strtok(NULL, "-");
    finishDate += atoi(token2)*360; 

    while(temp != NULL){
        if(srvF.hasCity == 1 && strcmp(srvF.city,temp->name) != 0){
            temp=temp->next;
            continue;
        }

        temp2 = temp->fileRoot;
        while(temp2 != NULL){
        //    printf("::::::%d-%s,%s\n",temp2->transactionID, temp->name,temp2->name);
            if((((temp2->year)*360) + ((temp2->month)*30)+temp2->day) >= startDate &&
               (((temp2->year)*360) + ((temp2->month)*30)+temp2->day) <= finishDate){
                if(strcmp(temp2->type,srvF.type) == 0){
                    size++;   
                }
            }
            temp2= temp2->next;
        }
        temp=temp->next;
    }
    write(sockfd,&size,sizeof(int));
    requestSize++;
   
    close(sockfd);
} 

/*Thread function.*/
static void *threadFunc(void *arg) {
    int serverNum=*((int *)arg);   //current thread number.
    
   
    while(1){
       
        pthread_mutex_lock(&mtx[serverNum]); //lock mutex of current thread.
     
        while( queueSize[serverNum]==0 && sigintFlag==0 ){//block while queue is 0.
            pthread_cond_wait(&condFull[serverNum],&mtx[serverNum]);
        }

        if(sigintFlag==1){ //If sigint signal come, exit thread.
            pthread_mutex_unlock(&mtx[serverNum]);
            break;
        }
       
        int fdSoc=queue[serverNum][queueSize[serverNum] - 1];//add file descriptor of common address in queue of current thread.
        queueSize[serverNum] = queueSize[serverNum]-1;//update queue size of current thread.
        currRunningNum=currRunningNum+1;
        func(fdSoc);//function for writing result in client.
        pthread_cond_signal(&condEmpty[serverNum]); 
        pthread_mutex_unlock(&mtx[serverNum]);  
        currRunningNum=currRunningNum-1;

    }  
    return 0;  
} 

void listening(int index){
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli; 
    socklen_t len;
     // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        fprintf(stderr,"socket creation failed...\n"); 
        exit(EXIT_FAILURE); 
    } 
    
    bzero(&servaddr, sizeof(servaddr)); 

    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(index); 
    
    int flag = 1;  
    if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag))) {  
        fprintf(stderr,"setsockopt fail");  
        exit(EXIT_FAILURE);
    }  
    // Binding newly created socket to given IP and verification. 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        fprintf(stderr,"socket bind failed because of "); 
        fprintf(stderr, "%s\n", strerror(errno)); 
        exit(EXIT_FAILURE); 
    } 

    // server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        fprintf(stderr,"Listen failed...\n"); 
        exit(EXIT_FAILURE); 
    } 
    
    len = sizeof(cli);
    thread_server=(pthread_t*)malloc(startThreadNum*sizeof(pthread_t));
    
    save=(int*)malloc((lastThreadNum+1)*sizeof(int));
    int i,s;
   
    initilializeMutexesAndConds(); //initializes mutexes and condition variables.

    initializeQueue();//initializing queue.
     /*Creating threads for first threads.*/
    for (i = 0; i < startThreadNum; i++) {
        save[i] = i;
        if ((s = pthread_create(&thread_server[i], NULL,threadFunc,(void*) &save[i])) != 0)
        {
            fprintf(stderr,"Failed to pthread_create operation in main.\n");
            exit(EXIT_FAILURE);
        }
    }


    int threadIndex=0;
    while(1){
        if(sigintFlag==1){/*If sigint signal come,close thread*/
            break;
        }    
        else{
            if(sigintFlag==0){
                connfd = accept(sockfd, (struct sockaddr*)&cli, &len); //Accepting socked fd's from client.
                if (connfd < 0 && sigintFlag==0) { 
                    fprintf(stderr,"server acccept failed...\n"); 
                    exit(EXIT_FAILURE); 
                }
            }
        }
        if(sigintFlag==1){
            break;
        }      
        pthread_mutex_lock(&mtx[threadIndex]);  
    
        while(queueSize[threadIndex]==500 && sigintFlag==0){ /*If queue size is over,wait.*/
            pthread_cond_wait(&condEmpty[threadIndex],&mtx[threadIndex]);
        }
        if(sigintFlag==1){/*If sigint signal come,close thread*/
            pthread_mutex_unlock(&mtx[threadIndex]);
            break;
        }
        queue[threadIndex][queueSize[threadIndex]]=connfd; //add socket fd's in queue.
        queueSize[threadIndex]=queueSize[threadIndex]+1;

        if(currRunningNum==lastThreadNum){
        }

        pthread_cond_signal(&condFull[threadIndex]); 
    
        pthread_mutex_unlock(&mtx[threadIndex]);

        threadIndex++;
        if(threadIndex==startThreadNum){
            threadIndex=0;
        } 
     
    } 
        /*Send signal to waiting  threads for closing after sigint signal.*/
    for(i=0;i< startThreadNum;++i){
        if(pthread_cond_signal(&condFull[i])!=0){
            fprintf(stderr, "Pthread cond error in main");
            exit(EXIT_FAILURE);
        }
    }
    /*Send signal to waiting  threads for closing after sigint signal.*/
    for(i=0;i<startThreadNum;++i){
        if(pthread_cond_signal(&condEmpty[i])!=0){
            fprintf(stderr, "Pthread cond error in main");
            exit(EXIT_FAILURE);
        }
    }
      /*Waiting for threads by main thread.*/
    for (i = 0; i < startThreadNum; i++)
    {
        if ((s = pthread_join(thread_server[i], NULL)) != 0)
        {
            fprintf(stderr, "Pthread_join error in main");
            
            exit(EXIT_FAILURE);
        }
    }     
    /*Mutex destroy of all threads.*/ 
    for(i=0;i<lastThreadNum+1;++i){
        if(pthread_mutex_destroy(&mtx[i])!=0){
            fprintf(stderr, "Pthread mutex destroy error in main");
           
            exit(EXIT_FAILURE);
          
        }
    } 
    /*Condition empty variable destroy of all threads.*/ 
    for(i=0;i<lastThreadNum+1;++i){
        if(pthread_cond_destroy(&condEmpty[i])!=0){
            fprintf(stderr,"Error in Condition destroy\n");
            exit(EXIT_FAILURE);
        }
    }
   /*Condition full variable destroy of all threads.*/ 
    for(i=0;i<lastThreadNum+1;++i){
        if(pthread_cond_destroy(&condFull[i])!=0){
            fprintf(stderr,"Error in Condition destroy\n");
            exit(EXIT_FAILURE);
        }
    }
    /*Free resources.*/
    freeQueue();
    free(mtx);
    free(save);
    free(thread_server);
    free(condEmpty);
    free(condFull);
    close(sockfd);

}

struct file *files(char* path){

    
    struct file* root,*traverse;
    char filePath[150],string[300],file2[500];
    char bufFile[1];
    sprintf(filePath, "%s/%s",filepath,path);
    DIR *dir = opendir(filePath);
    struct dirent *dit;
    root = (struct file *)malloc(sizeof(struct file));
    dit = readdir(dir);
    if ( (strcmp(dit->d_name, ".") != 0) && (strcmp(dit->d_name, "..") != 0) ){
        sprintf(file2,"%s/%s",filePath,dit->d_name);
        int fd = open(file2, O_RDONLY);
        int j = 0,k=0;
         memset(string, 0, sizeof (string));
        while(read(fd, bufFile, 1)){
            if(bufFile[0] == '\n'){
                
                root->price = atoi(string);

                memset(string, 0, sizeof (string));
                j=0;
                char* token = strtok(dit->d_name, "-");
                root->day = atoi(token);
                token = strtok(NULL, "-");
                root->month = atoi(token);
                token = strtok(NULL, "-");
                root->year = atoi(token); 
                root->next = NULL;
                traverse = root;
                break;
            }
            else if(bufFile[0] == ' '){
                
                switch(k){
                    case 0: root->transactionID = atoi(string);
                        k++;
                        break;
                    case 1: strcpy(root->type, string);
                        k++;
                        break;
                    case 2:strcpy(root->name, string);
                        k++;
                        break;
                    case 3:root->surface = atoi(string);
                        memset(string, 0, sizeof (string));
                        j=0;
                        k=0;
                        break;
                }
                memset(string, 0, sizeof (string));
                j=0;
            }
            else{
                string[j] = bufFile[0];
                j++;
            }            
        }
        close(fd);
    }
    else if ((dit = readdir(dir)) != NULL && (strcmp(dit->d_name, ".") != 0) && (strcmp(dit->d_name, "..") != 0)){
        
        sprintf(file2,"%s/%s",filePath,dit->d_name);
        int fd = open(file2, O_RDONLY);
        int j = 0,k=0;
         memset(string, 0, sizeof (string));
        while(read(fd, bufFile, 1)){
            if(bufFile[0] == '\n'){
                
                root->price = atoi(string);

                memset(string, 0, sizeof (string));
                j=0;
                char* token = strtok(dit->d_name, "-");
                root->day = atoi(token);
                token = strtok(NULL, "-");
                root->month = atoi(token);
                token = strtok(NULL, "-");
                root->year = atoi(token); 
                root->next = NULL;
                traverse = root;
                break;
            }
            else if(bufFile[0] == ' '){
                
                switch(k){
                    case 0: root->transactionID = atoi(string);
                        k++;
                        break;
                    case 1: strcpy(root->type, string);
                        k++;
                        break;
                    case 2:strcpy(root->name, string);
                        k++;
                        break;
                    case 3:root->surface = atoi(string);
                        memset(string, 0, sizeof (string));
                        j=0;
                        k=0;
                        break;
                }
                memset(string, 0, sizeof (string));
                j=0;
            }
            else{
                string[j] = bufFile[0];
                j++;
            }            
        }
        close(fd);
    }

    else {
        sprintf(file2,"%s/%s",filePath,dit->d_name);
        int fd = open(file2, O_RDONLY);
        int j = 0,k=0;
         memset(string, 0, sizeof (string));
        while(read(fd, bufFile, 1)){
            if(bufFile[0] == '\n'){
                
                root->price = atoi(string);

                memset(string, 0, sizeof (string));
                j=0;
                char* token = strtok(dit->d_name, "-");
                root->day = atoi(token);
                token = strtok(NULL, "-");
                root->month = atoi(token);
                token = strtok(NULL, "-");
                root->year = atoi(token); 
                root->next = NULL;
                traverse = root;
                break;
            }
            else if(bufFile[0] == ' '){
                
                switch(k){
                    case 0: root->transactionID = atoi(string);
                        k++;
                        break;
                    case 1: strcpy(root->type, string);
                        k++;
                        break;
                    case 2:strcpy(root->name, string);
                        k++;
                        break;
                    case 3:root->surface = atoi(string);
                        memset(string, 0, sizeof (string));
                        j=0;
                        k=0;
                        break;
                }
                memset(string, 0, sizeof (string));
                j=0;
            }
            else{
                string[j] = bufFile[0];
                j++;
            }            
        }
        close(fd);
    }
    traverse = root;
    while ((dit = readdir(dir)) != NULL)
    {
        if ( (strcmp(dit->d_name, ".") == 0) || (strcmp(dit->d_name, "..") == 0) )
            continue;
        sprintf(file2,"%s/%s",filePath,dit->d_name);
        int fd = open(file2, O_RDONLY);
        int j = 0,k=0;
        int day,month,year;
        char* token = strtok(dit->d_name, "-");
        
        day = atoi(token);

        token = strtok(NULL, "-");
        month = atoi(token);
        token = strtok(NULL, "-");
        year = atoi(token); 

        char type[150],strName[150];
        int tID,surface;
        while(read(fd, bufFile, 1) && bufFile[0] != '\0'){
            if(bufFile[0] == '\n'){
                struct file* temp = (struct file *)malloc(sizeof(struct file));
                temp->price = atoi(string);

                memset(string, 0, sizeof (string));
                j=0;

                temp->day = day;
                temp->month = month;
                temp->year = year; 
                temp->next = NULL;

                traverse->next = temp;
                traverse = traverse->next;
                temp->transactionID = tID;
                temp->surface = surface;
                strcpy(temp->type, type);
                strcpy(temp->name, strName);
            //    free(temp);
                

            }
            else if(bufFile[0] == ' '){
                switch(k){
                    case 0: tID = atoi(string);
                        k++;
                        break;
                    case 1: strcpy(type, string);
                        k++;
                        break;
                    case 2:strcpy(strName, string);
                        k++;
                        break;
                    case 3:surface = atoi(string);
                        memset(string, 0, sizeof (string));
                        j=0;
                        k=0;
                        break;
                }
                memset(string, 0, sizeof (string));
                j=0;
            }
            else{
                string[j] = bufFile[0];
                j++;
            }            
        }
       
    }   
    closedir(dir);
    free(dit);
    return root;
}

char doublePath[1000][100];

void takeToStruct(){
    char filePath[150];
    struct dir *temp,*traverse;

    dirRoot = (struct dir *)malloc(sizeof(struct dir));
    strcpy(dirRoot->name, doublePath[start-1]);
    dirRoot->index = start;
    dirRoot->next = NULL;
    sprintf(filePath,"%s/%s",filepath,dirRoot->name);
    dirRoot->fileRoot =  files(dirRoot->name);

    traverse = dirRoot;
    for(int i=start;i<finish;i++){
        temp = (struct dir *)malloc(sizeof(struct dir));
        strcpy(temp->name, doublePath[i]);
        temp->index = start;
        temp->next = NULL;
        sprintf(filePath,"%s/%s",filepath,temp->name);
        temp->fileRoot =  files(temp->name);

        traverse->next = temp;
        traverse = traverse->next;
        if(i==finish-1)
            dirLast = *temp;
    }
}

void sortCities(int size){
    char temp[100];
  //Sort array using the Bubble Sort algorithm
  for(int i=0; i<size; i++){
    for(int j=0; j<size-1-i; j++){
      if(strcmp(doublePath[j], doublePath[j+1]) > 0){
        //swap array[j] and array[j+1]
        strcpy(temp, doublePath[j]);
        strcpy(doublePath[j], doublePath[j+1]);
        strcpy(doublePath[j+1], temp);
      }
    }
  }
}

void readFiles(char *path){
    DIR *dir = opendir(path);
    struct dirent *dit;
    int size = 0;
    while ((dit = readdir(dir)) != NULL)
    {
        
        if ( (strcmp(dit->d_name, ".") == 0) || (strcmp(dit->d_name, "..") == 0) )
            continue;

        sprintf(doublePath[size], "%s",dit->d_name);
        size++;        
    }  
    closedir(dir);
    free(dit);
    sortCities(size);  
    takeToStruct();
}


//print 

void freeStruct(){
    struct dir* temp4,* temp = dirRoot;
    struct file* temp2,*temp3;

    while(temp != NULL){
        temp2 = temp->fileRoot;
        while(temp2 != NULL){
            temp3 = temp2;
            temp2= temp2->next;
            free(temp3);
        }
        temp4 = temp;
        temp=temp->next;
        free(temp4);
    }
}


int main(int argc, char *argv[]){
    
    time_t begin;
    int option;
    char str[500];

    struct sigaction action;
    sigemptyset(&action.sa_mask); 
    action.sa_flags = 0;
    action.sa_handler = handler;
    if (sigaction(SIGINT, &action, NULL) == -1)
        perror("sigaction");
    if (sigaction(SIGTERM, &action, NULL) == -1)
        perror("sigaction");
    /*Getting command line arguments.*/
    while ((option = getopt(argc, argv, ":d:c:r:p:")) != -1)
    {
        switch (option)
        {
            case 'd':
                if(optarg[0] == '.' && optarg[1] == '.')
                    filepath=(optarg+1);
                else
                    filepath = optarg;
                break;
            case 'c':
                range = optarg;
                char* token = strtok(range, "-");
                start = atoi(token);
                token = strtok(NULL, "-");
                finish = atoi(token);
                break;
            case 'r':
                addr = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case '?':
                perror("It does not fit format! Format must be :./servant -d directoryPath -c 10-19 -r IP -p PORT\n");
                exit(EXIT_FAILURE);
                break;
        }
    }
    /*This condition to control format of command line arguments.*/
    if ((optind != 9))
    {
        perror("It does not fit format! Format must be :./servant -d directoryPath -c 10-19 -r IP -p PORT\n");
        exit(EXIT_FAILURE);
    }
    if(port <= 2000){
        fprintf(stderr, "'$PORT' value must be bigger than 2000\n");
        exit(EXIT_FAILURE);
    }
    readFiles("./dataset");
    int sockfd;
    struct sockaddr_in servaddr;
    //socket create and varification 
    time(&begin);
 //   fprintf(stdout,"%s: Client-Thread-%d: Thread-%d has been created\n",ctime(&begin),index,index);
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        fprintf(stderr,"socket creation failed...\n");
        exit(0); 
    } 
    bzero(&servaddr, sizeof(servaddr)); 

    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(addr); 
    servaddr.sin_port = htons(port); 
    
    int flag = 1;  
    if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag))) {  
        perror("setsockopt fail");  
    }  

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        perror("connection:\n");
        fprintf(stderr,"connection with the server failed...\n"); 
   //     exit(0); 
    } 
    char buff2[900000]={0}; 
    sprintf(str,"%d %s %s",(int)getpid(),dirRoot->name,dirLast.name);
    bzero(buff2, sizeof(buff2)); 
    time(&begin);
    fprintf(stdout, "%s:Servant %ld: loaded dataset, %s-%s\n",ctime(&begin),(long)getpid() ,dirRoot->name,dirLast.name);
    write(sockfd, str, strlen(str)+1); //send nodes for server via socket.

    int tempPort;
    read(sockfd, &tempPort,sizeof(int)); //get answer via socket.
    time(&begin);
    fprintf(stdout, "%s:Servant %ld: listening at port %d\n",ctime(&begin),(long)getpid() ,tempPort);
    time(&begin);

    close(sockfd); 

    listening(tempPort);
    time(&begin);
    freeStruct();
    fprintf(stdout, "%sServant %d: termination message received, handled %d requests in total.\n",ctime(&begin),(int)getpid(),requestSize );

    return 0;
}