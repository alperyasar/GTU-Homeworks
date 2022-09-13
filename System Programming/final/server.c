
#include "hdr.h"


int servantPort = 16000;
int requestSize =0;

struct servant
{
    int port;
    int pid;
    char firstCity[50];
    char lastCity[50];
    int index;
    struct servant* next;
};
struct servant* servantRoot;
/*Node for cache structure.*/

struct servantFile
{
    int hasCity;
    char startDate[25];
    char finishDate[25];
    char type[50];
    char city[50];
};

/*Mutexes and condition variables for threads*/ 
static pthread_mutex_t* mtx=NULL; 
static pthread_cond_t* condFull=NULL; 
static pthread_cond_t* condEmpty=NULL; 
/*Condition variables for reader-writer paradigm.*/
pthread_t* thread_server; //Server threads.
int* save;

int** queue;  //Client queue.
int* queueSize;
int threadNum; //thread number at beginning.
int currRunningNum;  //Current running thread number.
atomic_int sigintFlag=0;/*Sigint flag*/
/*This function finds total node number in file.*/
   


/*Initializes thread mutexes and condition variables.*/
void initilializeMutexesAndConds(){
    mtx=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*(threadNum+1));
    condFull=(pthread_cond_t*)malloc(sizeof(pthread_cond_t)*(threadNum+1));
    condEmpty=(pthread_cond_t*)malloc(sizeof(pthread_cond_t)*(threadNum+1));
    int i;
    int m1,c,c2;
    for(i=0;i<threadNum+1;i++){
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


int createServant(int index,char* token,int tempPort){
    if(index == 0){
        servantRoot = (struct servant *)malloc(sizeof(struct servant));
        servantRoot->pid = atoi(token);
        token = strtok(NULL, " ");
        strcpy(servantRoot->firstCity,token);
        token = strtok(NULL, " ");
        strcpy(servantRoot->lastCity,token);
        servantRoot->index = index;
        servantRoot->port = tempPort;
        servantRoot->next = NULL;
        return tempPort;
    }

    struct servant *traverse = servantRoot;
    while(traverse->next != NULL)
        traverse = traverse->next;
    struct servant *temp = (struct servant *)malloc(sizeof(struct servant));
    temp->pid = atoi(token);
    token = strtok(NULL, " ");
    strcpy(temp->firstCity,token);
    token = strtok(NULL, " ");
    strcpy(temp->lastCity,token);
    temp->index = index;
    temp->port = tempPort;
    temp->next = NULL;
    traverse->next = temp;
    time_t begin;
    time(&begin);
    fprintf(stdout, "%s:Servant %d present at port %d handling cities %s-%s\n",ctime(&begin),temp->pid,temp->port,temp->firstCity,temp->lastCity );
    return tempPort;


}
int sendData(struct servantFile srvF,struct servant srv){
    int sockfd;
    struct sockaddr_in servaddr;
    //socket create and varification 
 //   fprintf(stdout,"%s: Client-Thread-%d: Thread-%d has been created\n",ctime(&begin),index,index);
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        fprintf(stderr,"socket creation failed...\n");
        exit(0); 
    } 
    bzero(&servaddr, sizeof(servaddr)); 

    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(srv.port); 
    
    int flag = 1;  
    if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag))) {  
        perror("setsockopt fail");  
    }  

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        perror("connection:\n");
        fprintf(stderr,"connection with the server failed...\n"); 
        exit(0); 
    } 
    write(sockfd, &srvF, sizeof(struct servantFile)); //send nodes for server via socket.

    int tempPort;
    read(sockfd, &tempPort,sizeof(int)); //get answer via socket.


    close(sockfd); 
    return tempPort;
}
int comp2City(char* str1,char* str2){
    int i=0;
    if (strcmp(str1,str2) == 0)
    {
        return 1;
    }
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] > str2[i])
            return 0;
        else if(str1[i] < str2[i])
            return 1;
        i++;
    }
    return 1;
}
int connectServant(char* str){
    time_t begin;
    char string[300];
    memset(string, 0, sizeof (string));
    int j =0;
    int i=0;
    while(str[i] != ' '){
        string[j] = str[i];
        j++;
        i++;
    }
    int totalsize=0;
    struct servant* temp5 = servantRoot;
    struct servantFile temp;
//    memset(&temp, 0, sizeof (struct servantFile));
    memset(string, 0, sizeof (string));
    while(str[i] == ' ')
        i++;
    j =0;
    while(str[i] != ' '){
        string[j] = str[i];
        j++;
        i++;
    }
    strcpy(temp.type,string);
    memset(string, 0, sizeof (string));
    j =0;
    while(str[i] == ' ')
        i++;
    while(str[i] != ' '){
        string[j] = str[i];
        j++;
        i++;
    }
    strcpy(temp.startDate,string);
    memset(string, 0, sizeof (string));
    j =0;
    while(str[i] == ' ')
        i++;
    while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0'){
        string[j] = str[i];
        j++;
        i++;
    }
    strcpy(temp.finishDate,string);
    temp.hasCity = 0;
    while(str[i] == ' ')
        i++;
    int ifCond = 0;
    if(str[i] != '\n' && str[i] != '\0')
        ifCond = 1;

    if(ifCond == 1){

            
        memset(string, 0, sizeof (string));
        j =0;
        while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0'){
            string[j] = str[i];
            j++;
            i++;
        }
        
        strcpy(temp.city,string);
        temp.hasCity = 1;
        while(temp5 != NULL){
            char str1[50],str2[50];
            strcpy(str1,temp5->firstCity);
            strcpy(str2,temp5->lastCity);
            int cmp1 = comp2City(string,str2);
            int cmp2 = comp2City(str1,string);
            if(cmp1 == 1 && cmp2 == 1){
                time(&begin);
                fprintf(stdout, "%s:Contacting servant %d\n",ctime(&begin),temp5->pid);

                return sendData(temp,*temp5);;
            }
            temp5 = temp5->next;
        }
    }
    time(&begin);
    fprintf(stdout, "%s:Contacting ALL servants\n",ctime(&begin));
    while(temp5 != NULL){
        totalsize += sendData(temp,*temp5);
        temp5 = temp5->next;
    }
    return totalsize;
}

/*Function for comminication between client and server.Messages is sending to client in this function.*/
/*And also reader-writer mechanism is used for informations of database structure.*/
void func(int sockfd,int tempPort,int index) 
{ 
    int buff[2];
    char buff32[1000];
    time_t begin;

    bzero(buff,2);   
    read(sockfd, buff32, sizeof(buff32));  //getting 2 nodes that are source and destination nodes from buffer on socket.
    
    if(buff32[0] >= '0' && buff32[0] <= '9'){

        char* token = strtok(buff32, " ");
        int temp = createServant(index,token,tempPort);
        write(sockfd, &temp, sizeof(int)); 
    }
    
    else{
        time(&begin);
        fprintf(stdout, "%s:Request arrived \"%s\"\n",ctime(&begin),buff32);

        int temp = connectServant(buff32);

        time(&begin);
        fprintf(stdout, "%s:Response received: %d, forwarded to client\n",ctime(&begin),temp);
        requestSize++;
        write(sockfd,&temp,sizeof(int));
    }

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
        
        func(fdSoc,++servantPort,serverNum);//function for writing result in client.
        pthread_cond_signal(&condEmpty[serverNum]); 
        pthread_mutex_unlock(&mtx[serverNum]);  
        currRunningNum=currRunningNum-1;
        serverNum++;

    }  
    return 0;  
} 
/*Initializing queue of file pointer of accept address of socket.*/ 
void initializeQueue(){
    queue=(int**)malloc((threadNum+1)*sizeof(int*));
    int i;
    for(i=0;i<threadNum+1;i++){
        queue[i]=(int*)malloc(500*sizeof(int));
    }

    queueSize=(int*)malloc((threadNum+1)*sizeof(int));
    for(i=0;i<threadNum+1;i++){
        queueSize[i]=0;
   
    }
}
/*Free queue.*/
void freeQueue(){
    int i;
    for(i=0;i<threadNum+1;i++){
        free(queue[i]);

    }
    free(queue);
    free(queueSize);
}

/*SIGINT handler function */
void handler(){

    sigintFlag=1; //change flag.
  
}

// Main function.
int main(int argc, char *argv[]) { 
    int  option,port;
    sigintFlag=0;

    struct sigaction action;
    sigemptyset(&action.sa_mask); 
    action.sa_flags = 0;
    action.sa_handler = handler;
    if (sigaction(SIGINT, &action, NULL) == -1)
        perror("sigaction");
    if (sigaction(SIGTERM, &action, NULL) == -1)
        perror("sigaction");
     /*getting command line arguments.*/
    while((option = getopt(argc, argv, ":p:t:")) != -1){ 
      switch(option){
        case 'p': 
            port = atoi(optarg);
            break; 
        case 't': 
            threadNum = atoi(optarg);
            break;               
        case '?':
        perror("It does not fit format!Format must be: ./server -p 3300 -t 11\n");
        exit(EXIT_FAILURE);
        break;
      }
    }
    if((optind!=5)){
        errno=EINVAL;
        perror("CommandLine argument numbers must be 13! Format must be: ./server -p 3300 -t 11\n");
        exit(EXIT_FAILURE);
    }


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
    servaddr.sin_port = htons(port); 
    
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


   

    thread_server=(pthread_t*)malloc(threadNum*sizeof(pthread_t));
    
    save=(int*)malloc((threadNum+1)*sizeof(int));
    int i,s;
   
    initilializeMutexesAndConds(); //initializes mutexes and condition variables.

    initializeQueue();//initializing queue.
     /*Creating threads for first threads.*/
    for (i = 0; i < threadNum; i++) {
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


        pthread_cond_signal(&condFull[threadIndex]); 
    
        pthread_mutex_unlock(&mtx[threadIndex]);

        threadIndex++;
        if(threadIndex==threadNum){
            threadIndex=0;
        } 
     
    } 
    /*Send signal to waiting  threads for closing after sigint signal.*/
    for(i=0;i<threadNum;++i){
        if(pthread_cond_signal(&condFull[i])!=0){
            fprintf(stderr, "Pthread cond error in main");
            exit(EXIT_FAILURE);
        }
    }
    /*Send signal to waiting  threads for closing after sigint signal.*/
    for(i=0;i<threadNum;++i){
        if(pthread_cond_signal(&condEmpty[i])!=0){
            fprintf(stderr, "Pthread cond error in main");
            exit(EXIT_FAILURE);
        }
    }
      /*Waiting for threads by main thread.*/
    for (i = 0; i < threadNum; i++)
    {
        if ((s = pthread_join(thread_server[i], NULL)) != 0)
        {
            fprintf(stderr, "Pthread_join error in main");
            
            exit(EXIT_FAILURE);
        }
    }     
    /*Mutex destroy of all threads.*/ 
    for(i=0;i<threadNum+1;++i){
        if(pthread_mutex_destroy(&mtx[i])!=0){
            fprintf(stderr, "Pthread mutex destroy error in main");
           
            exit(EXIT_FAILURE);
          
        }
    } 
    /*Condition empty variable destroy of all threads.*/ 
    for(i=0;i<threadNum+1;++i){
        if(pthread_cond_destroy(&condEmpty[i])!=0){
            fprintf(stderr,"Error in Condition destroy\n");
            exit(EXIT_FAILURE);
        }
    }
   /*Condition full variable destroy of all threads.*/ 
    for(i=0;i<threadNum+1;++i){
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
    time_t begin;
    time(&begin);
    struct servant *traverse = servantRoot;
    while(traverse != NULL){
        servantRoot = servantRoot->next;
        kill((pid_t)traverse->pid,SIGTERM);
        free(traverse);
        traverse = servantRoot;
    }
    fprintf(stdout, "%sSIGINT has been received. I handled a total of %d requests. Goodbye.\n", ctime(&begin),requestSize);
} 