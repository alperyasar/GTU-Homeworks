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
    $./client -r requestFile -q PORT -s IP
*/

#include "hdr.h"


int threadSize=0;
time_t startTime;
char *addr;
static pthread_mutex_t mtx; //mutexes 
static pthread_mutex_t mainMtx; //mutexes
static pthread_cond_t cond; //condition 
static pthread_cond_t condMain; //condition 
/*Get time as microsecond.While using after,it will be converted second.*/
unsigned long getTime(){
    struct timeval timeValue;
    gettimeofday(&timeValue,NULL);
    unsigned long microSecond=1000000 * timeValue.tv_sec + timeValue.tv_usec;
   
    return microSecond;
}
/*For send and get information via socket with server.*/
static void *func(void *arg) 
{   
    time_t begin;
    int index = threadSize++;
    int sockfd;
    struct sockaddr_in servaddr;
    char str[500];

    strcpy(str,arg); 
    //socket create and varification 
    time(&begin);
    fprintf(stdout,"%s: Client-Thread-%d: Thread-%d has been created\n",ctime(&begin),index,index);
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

    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        perror("connection:\n");
        fprintf(stderr,"connection with the server failed...\n"); 
        exit(0); 
    } 


    pthread_cond_signal(&condMain);
    pthread_mutex_unlock(&mainMtx); //unlock mutex.

    int buff2;
    
    pthread_cond_wait(&cond,&mtx);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx); //unlock mutex.
    time(&begin);
    fprintf(stdout,"%s: Client-Thread-%d: I am requesting “/%s”\n",ctime(&begin),index,str);
    write(sockfd, str, strlen(str)+1); //send nodes for server via socket.

    read(sockfd, &buff2,sizeof(buff2)); //get answer via socket.
    time(&begin);
    fprintf(stdout,"%s: Client-Thread-%d: The server’s response to “/%s” is %d\n",ctime(&begin),index,str,buff2);
    fprintf(stdout, "Client-Thread-%d: Terminating\n",index);
    
    //close the socket 
    close(sockfd); 
    return 0;  
} 

int main(int argc, char *argv[]) { 

    char *filepath;
    time_t begin;
    int  option;
  /*getting command line arguments.*/
    while((option = getopt(argc, argv, ":r:q:s:")) != -1){ 
      switch(option){
        case 's':
            addr=optarg;
            break;
        case 'r':
            if(optarg[0] == '.' && optarg[1] == '.')
                filepath=(optarg+1);
            else
                filepath=optarg;
            break;
        case 'q': 
            port= atoi(optarg);
            break;      
        case '?': 
            perror("It does not fit format!Format example is ./client -r requestFile -q PORT -s IP\n");
            exit(EXIT_FAILURE);
        break;
      }
    }
    if((optind!=7)){
        errno=EINVAL;
        perror("CommandLine argument numbers must be 7! Format example is ./client -r requestFile -q PORT -s IP\n");
        exit(EXIT_FAILURE);
    } 
    
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
    mtxCheck=pthread_mutex_init (&mainMtx, NULL);             
    if(mtxCheck!=0){
        perror("Error for thread mutex initialization!");
        exit(EXIT_FAILURE);
    }
    mtxCheck=pthread_cond_init (&condMain, NULL);
    if(mtxCheck!=0){
        perror("Error for condition variable initialization!");
        exit(EXIT_FAILURE);
    }

    int fd;
    if ((fd = open(filepath, O_RDONLY)) == -1)
    {
        perror("Failed to open input file in main.\n");
        exit(EXIT_FAILURE);
    }
    int line=0,newincre=0,s;
    char bufFile[1];
    int reading = read(fd, bufFile, 1);
    while(reading != 0){
        if(bufFile[0] == '\n'){
            
            line++;
            newincre=1;
        }
        else if(newincre == 1){
            newincre = 0;
        }   
        reading = read(fd, bufFile, 1);
        if(newincre == 1 && bufFile[0] == '\n'){
                reading=0;
        }
    }
    pthread_t thread_server[line]; //Server threads.
    time(&begin);
    fprintf(stdout,"%s: Client: I have loaded %d requests and I’m creating %d threads.\n",ctime(&begin),line,line);

    char string[300];
    lseek(fd, 0, SEEK_SET);
    for (int i = 0; i < line; ++i)
    {
        memset(string, 0, sizeof (string));
        int j =0;
        while(read(fd, bufFile, 1) && bufFile[0] != '\n'){
            string[j] = bufFile[0];
            j++;
        }
        if ((s = pthread_create(&thread_server[i], NULL,func,(void*) string)) != 0)
        {
            fprintf(stderr,"Failed to pthread_create operation in main.\n");
            exit(EXIT_FAILURE);
        }
        pthread_cond_wait(&condMain,&mainMtx);
    }
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx); //unlock mutex.
    for (int i = 0; i < line; i++)
    {
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx); //unlock mutex.
        if ((s = pthread_join(thread_server[i], NULL)) != 0)
        {
            fprintf(stderr, "Pthread_join error in main\n");
            
            exit(EXIT_FAILURE);
        }
    }
    fprintf(stderr, "Client: All threads have terminated, goodbye.\n" );
    close(fd);
} 
