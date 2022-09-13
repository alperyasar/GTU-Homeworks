/*********************************************************************************
*																				 *
*								ALPER YAŞAR										 *
*						GEBZE TECHNICAL UNİVERSITY								 *
*								151044072										 *
*							SYSTEM PROGRAMMING									 *
*									HW3 										 *
*																				 *
**********************************************************************************/


/*
	// for running the file
	$./hw3unnamed -i input.txt
*/

#include "hdr.h"

/*Shared Memory*/
struct SharedMemory {
    /*Unnamed semaphores and mutexes.*/    
    sem_t sem_chef[6],sem_wholesaler;
    int exit,waitToWrite;
    char ingredients[3];      /*Global ingredients array.*/
};


static struct SharedMemory *sharedMem;

int main(int argc, char *argv[]){
	char *inputFile;
    int option;
    char string[300];
    int writeRes;

    /*Getting command line arguments.*/
    while ((option = getopt(argc, argv, ":i:")) != -1)
    {
        switch (option)
        {
	        case 'i':
	            inputFile = optarg;
	            break;
	        case '?':
	            perror("It does not fit format! Format must be :./hw3named -i inputFilePath\n");
	            exit(EXIT_FAILURE);
	            break;
        }
    }
    /*This condition to control format of command line arguments.*/
    if ((optind != 3))
    {
        perror("It does not fit format! Format must be :./hw3named -i inputFilePath\n");
        exit(EXIT_FAILURE);
    }

    //  sigset_t origMask, blockMask;
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");
    	
    /* Assigning the chefs what has and what needs*/
    sprintf(chef[0].ing1, "walnuts");
    sprintf(chef[0].ing2, "sugar");
    sprintf(chef[0].need,"WS");
    sprintf(chef[0].has,"MF");
    sprintf(chef[1].ing1, "flour");
    sprintf(chef[1].ing2, "walnuts");
    sprintf(chef[1].need,"FW");
    sprintf(chef[1].has,"MS");
    sprintf(chef[2].ing1, "sugar");
    sprintf(chef[2].ing2, "flour");
    sprintf(chef[2].need,"SF");
    sprintf(chef[2].has,"MW");
    sprintf(chef[3].ing1, "milk");
    sprintf(chef[3].ing2, "flour");
    sprintf(chef[3].need,"MF");
    sprintf(chef[3].has,"SW");
    sprintf(chef[4].ing1, "milk");
    sprintf(chef[4].ing2, "walnuts");
    sprintf(chef[4].need,"MW");
    sprintf(chef[4].has,"SF");
    sprintf(chef[5].ing1, "sugar");
    sprintf(chef[5].ing2, "milk");
    sprintf(chef[5].need,"SM");
    sprintf(chef[5].has,"FW");

    /*Open  an  object with a specified name for shared memory.*/
    int fd = shm_open("SharedArea",O_CREAT |  O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1){
        sprintf(string,"Failed shm_open operation in main!");
        writeRes=write(STDOUT_FILENO, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    } 
    if (ftruncate(fd, sizeof(struct SharedMemory)) == -1){
        sprintf(string,"ftruncate error in main!");
        writeRes=write(STDOUT_FILENO, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        }
         exit(EXIT_FAILURE);
    } 
    /*Maps the shared memory object into the process’s virtual address space.*/
    sharedMem = mmap(NULL, sizeof(struct SharedMemory), PROT_READ | PROT_WRITE,MAP_SHARED, fd, 0); 
    if( MAP_FAILED == sharedMem ) {
        sprintf(string,"Mmap failed in main function!" );
        writeRes=write(STDOUT_FILENO, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        }
        return EXIT_FAILURE;
    }
    /*Initializes the unnamed semaphores.*/ 
    if ( sem_init(&sharedMem->sem_chef[0],1,0) == -1 || sem_init(&sharedMem->sem_chef[1],1,0) == -1 ||
    	 sem_init(&sharedMem->sem_chef[2],1,0) == -1 || sem_init(&sharedMem->sem_chef[3],1,0) == -1 ||
    	 sem_init(&sharedMem->sem_chef[4],1,0) == -1 || sem_init(&sharedMem->sem_chef[5],1,0) == -1 ||
    	 sem_init(&sharedMem->sem_wholesaler,1,1) == -1){
        sprintf(string,"Error in main function for sem_init operation. \n");
        writeRes=write(STDOUT_FILENO, string, strlen(string));
        if(writeRes==-1){
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    } 
    /*Initializes the variables in shared memory.*/   
    sharedMem->exit=0;
    sharedMem->waitToWrite=0;
    /*Opening input file.*/
    if ((fdInput = open(inputFile, O_RDONLY)) == -1)
    {
        perror("Failed to open input file in main.\n");
        exit(EXIT_FAILURE);
    }
    int bytes;
    char keep[1];

    /*Controls the file whether it has a letter except M or W or F or W or not.If it has,print error message.*/
    do
    {
        if ((bytes = read(fdInput, keep, 1)) == -1)
        {
            perror("Failed to read input file in main.\n");
            exit(EXIT_FAILURE);
        }
        if (keep[0] != 'W' && keep[0] != 'S' && keep[0] != 'F' && keep[0] != 'M' && keep[0] != '\n')
        {
            perror("Error! Letters in line in input file must be M or W or S or F\n");
            exit(EXIT_FAILURE);
        }
    } while (bytes > 0);
    lseek(fdInput, 0, SEEK_SET);
    char keep2[2];    
    char tmp[3],str[3];
    int newlineCount=0,tmpBytes;
    bytes = 0;
    /*Controls the file whether it has a line that includes 2 same ingredients or not.If it has,print error message.*/
    do
    {
        if ((bytes = read(fdInput, keep2, 3)) == -1)
        {
            perror("Failed to read input file in main.\n");
            exit(EXIT_FAILURE);
        }
        if (keep2[0] == keep2[1])
        {
            perror("Error! In a line of input file,there must be 2 distinct letter.\n");
            exit(EXIT_FAILURE);
        }
        if (keep2[1] != 'W' && keep2[1] != 'S' && keep2[1] != 'F' && keep2[1] != 'M')
        {
            perror("1 ingredient in line\n");
            exit(EXIT_FAILURE);
        }
        newlineCount++;
    } while (bytes > 0);
    /*If size of file less than 10,print error.*/
    if(newlineCount<1){
        perror("Error! In input file,there must be at least 10 row.\n");
        exit(EXIT_FAILURE);
    }
    lseek(fdInput, 0, SEEK_SET);
    sem_wait(&sharedMem->sem_wholesaler);
    int result;
    for(int i = 0;i<6;i++){
    	switch (fork()) {
            case -1:
                perror("fork");
                _exit(EXIT_FAILURE);
            case 0: /* Child sleeps for a while then exits */
           //     sleep(k);
                
                mother = 1;
                result = street(i);

                _exit(result);
            default: /* Parent just continues around loop */
                break;
            }  
    }
    sem_wait(&sharedMem->sem_wholesaler);
    /*Creating 6 processes for chefs.*/
    /*Main process that is wholesaler's process.*/
    do
    {
        if ((tmpBytes = read(fdInput, tmp, 3)) == -1)  /*Read a line from file that includes 2 letters in each line.*/
        {
            sprintf(string, "Failed to read input file in main.\n");
            writeRes = write(STDOUT_FILENO, string, strlen(string));
            if (writeRes == -1)
            {
                exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
        }
        if (tmpBytes == 0) /*End of file*/
        {               
            sharedMem->exit = 1; /*For notify  the chefs that no more ingredients.*/
            break;
        }

        char stringPrint[50];
        str[0] = tmp[0];
        str[1] = tmp[1];
        /*Selecting message that will print according to letters.*/
        if (str[0] == 'W' && str[1] == 'S')
        {
            sprintf(stringPrint, "walnuts and sugar");
        }
        if (str[0] == 'S' && str[1] == 'W')
        {
            sprintf(stringPrint, "sugar and walnuts");
        }
        if (str[0] == 'F' && str[1] == 'W')
        {
            sprintf(stringPrint, "flour and walnuts");
        }
        if (str[0] == 'W' && str[1] == 'F')
        {
            sprintf(stringPrint, "walnuts and flour");
        }
        if (str[0] == 'S' && str[1] == 'F')
        {
            sprintf(stringPrint, "sugar and flour");
        }
        if (str[0] == 'F' && str[1] == 'S')
        {
            sprintf(stringPrint, "flour and sugar");
        }
        if (str[0] == 'W' && str[1] == 'M')
        {
            sprintf(stringPrint, "walnuts and milk");
        }
        if (str[0] == 'M' && str[1] == 'W')
        {
            sprintf(stringPrint, "milk and walnuts");
        }
        if (str[0] == 'M' && str[1] == 'F')
        {
            sprintf(stringPrint, "milk and flour");
        }
        if (str[0] == 'F' && str[1] == 'M')
        {
            sprintf(stringPrint, "flour and milk");
        }
        if (str[0] == 'M' && str[1] == 'S')
        {
            sprintf(stringPrint, "milk and sugar");
        }
        if (str[0] == 'S' && str[1] == 'M')
        {
            sprintf(stringPrint, "sugar and milk");
        }
        /*Print message on screen*/
        fprintf(stdout,"the wholesaler (pid %ld) delivers %s\n",(long) getpid(), stringPrint);

        /*Put ingredients in global array.*/
        sharedMem->ingredients[0] = str[0];
        sharedMem->ingredients[1] = str[1];

        fprintf(stdout,"the wholesaler (pid %ld) is waiting for the dessert\n",(long) getpid());
        /*Post operation for semaphore.*/
        if (sem_post(&sharedMem->sem_chef[0]) == -1)
        {
            sprintf(string, "Failed to sem_post operation in main.\n");
            writeRes = write(STDOUT_FILENO, string, strlen(string));
            if (writeRes == -1)
            {
                exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
        }
        /*This semaphore is using to wait for wholesaler while chef is preparing dessert.*/
        if (sem_wait(&sharedMem->sem_wholesaler) == -1)
        {
            sprintf(string, "Failed to sem_wait operation in main.\n");
            writeRes = write(STDOUT_FILENO, string, strlen(string));
            if (writeRes == -1)
            {
                exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
        }
        fprintf(stdout,"the wholesaler (pid %ld) has obtained the dessert and left to sell it\n",(long) getpid());

    } while (tmpBytes > 0);

    wholesaler();
    return 0;
}

int street(int index){
	char string[300];
	int writeRes;
	sprintf(string,"chef%d (pid %ld) is waiting for %s and %s contain of %s\n",index,(long) getpid(),chef[index].ing1,chef[index].ing2,chef[index].has );
    int result=0;
    writeRes=write(STDOUT_FILENO, string, strlen(string));

 
    if(writeRes==-1)
        exit(EXIT_FAILURE);
    (sharedMem->waitToWrite)++;
    if(sharedMem->waitToWrite == 6)
    	sem_post(&sharedMem->sem_wholesaler);
    while(sharedMem->exit != 1){
    	sem_wait(&sharedMem->sem_chef[index]);
       

        if((sharedMem->ingredients[0] == chef[index].need[0] && sharedMem->ingredients[1] == chef[index].need[1]) || 
   	   	   (sharedMem->ingredients[0] == chef[index].need[1] && sharedMem->ingredients[1] == chef[index].need[0])){
        
        	sharedMem->ingredients[0] = '\0';
	        sharedMem->ingredients[1] = '\0';
	        // işlemler burada
	        sprintf(string,"chef%d (pid %ld) has taken the %s contain of %s%c\n",index,(long) getpid(),chef[index].ing1,chef[index].has,chef[index].need[0]);
	        write(STDOUT_FILENO, string, strlen(string));
	        sprintf(string,"chef%d (pid %ld) has taken the %s contain of %s%s\n",index,(long) getpid(),chef[index].ing2,chef[index].has,chef[index].need);
	        write(STDOUT_FILENO, string, strlen(string));
	        sprintf(string,"Chef%d (pid %ld) is preparing the dessert contain of %s%s\n",index,(long) getpid(),chef[index].has,chef[index].need);
	        write(STDOUT_FILENO, string, strlen(string));
	        sprintf(string,"Chef%d (pid %ld) has delivered the dessert contain of %s\n",index,(long) getpid(),chef[index].has);
	        write(STDOUT_FILENO, string, strlen(string));
	        result++;
	        if (sem_post(&sharedMem->sem_wholesaler) == -1)
	        {
	            sprintf(string, "Failed to sem_post operation in chefs function.\n");
	            writeRes = write(STDOUT_FILENO, string, strlen(string));
	            if (writeRes == -1)
	            {
	                exit(EXIT_FAILURE);
	            }
	            exit(EXIT_FAILURE);
	        }
        }
        else{
        	if(index != 5)
 		       	sem_post(&sharedMem->sem_chef[index+1]);
        }
        
    }
    if(index != 5)
       	sem_post(&sharedMem->sem_chef[index+1]);
    fprintf(stdout, "chef%d (pid %ld) is exiting\n",index,(long)getpid() );
    return result;
}

void wholesaler(){
	
	sharedMem->exit=1;
    int status;
    int result = 0;
	sem_post(&sharedMem->sem_chef[0]);
	char string[100];
	int childPid,writeRes;
	for (;;) { /* Parent waits for each child to exit */
        childPid = waitpid(-1, &status, WUNTRACED);
        if(childPid != -1){
            result += WEXITSTATUS(status);
        }
        
        if (childPid == -1) {
            if (errno == ECHILD) {
                
		    /*Removes the shared memory object specified by name.*/  
            	fprintf(stdout,"the wholesaler (pid %ld) is done (total desserts: %d)\n",(long) getpid(),result);
            	close(fdInput);
			    if (sem_destroy(&sharedMem->sem_wholesaler) == -1  ){
			        sprintf(string,"Error in main function for sem_destroy operation. \n");
			        writeRes=write(STDOUT_FILENO, string, strlen(string));
			        if(writeRes==-1){
			            exit(EXIT_FAILURE);
			        }
			        exit(EXIT_FAILURE);
			    }  
			    for (int i = 0; i < 6; ++i)
			    {
			    	sem_destroy(&sharedMem->sem_chef[i]);
			    }
			    if(shm_unlink("SharedArea")==-1){
			        sprintf(string,"UNLINK error in main!\n");
			        writeRes=write(STDOUT_FILENO, string, strlen(string));
			        if(writeRes==-1){
			            exit(EXIT_FAILURE);
			        }
			        exit(EXIT_FAILURE);
			    }

			    /*Delete the mappings.*/ 
			    if(munmap(sharedMem, sizeof(struct SharedMemory))==-1){
			        sprintf(string,"MUNMAP error in main!\n");
			        writeRes=write(STDOUT_FILENO, string, strlen(string));
			        if(writeRes==-1){
			            exit(EXIT_FAILURE);
			        }
			        exit(EXIT_FAILURE);
			    }
			    exit(EXIT_SUCCESS);
            } else { /* Some other (unexpected) error */
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/*This handler for SIGINT signals*/
void handler(int sig) {
    if (sig == SIGINT){
        fprintf(stderr, "Process %ld received signal %d (%s)\n",
        (long) getpid(), sig, strsignal(sig));
        if(mother == 0)
	        wholesaler();
    }
    exit(EXIT_SUCCESS);
}
