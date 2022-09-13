/*********************************************************************************
*                                                                                *
*                               ALPER YAŞAR                                      *
*                       GEBZE TECHNICAL UNİVERSITY                               *
*                               151044072                                        *
*                           SYSTEM PROGRAMMING                                   *
*                                   HW4                                          *
*                                                                                *
**********************************************************************************/

/*
    // for running the file
    $./hw4 -C 10 -N 5 -F inputfilePath
*/

#include "hdr.h"


/*
    Its task is to loop N times.
    Consumers x C
    Each consumer will have its own thread (not detached).
*/
int n,c;
char *inputFile;
#define SEM_MUTEX_KEY "/tmp/sem-mutex-key"
#define SEM_BUFFER_COUNT_KEY "/tmp/sem-buffer-count-key"
#define SEM_SPOOL_SIGNAL_KEY "/tmp/sem-spool-signal-key"


int mutex_first,mutex_second;
int spool_signal_sem;

/* for semaphore */
key_t s_key;
int firs,secon,leave;
union semun  
{
    int val;
    struct semid_ds *buf;
    ushort array [1];
} sem_attr;

int main(int argc, char *argv[]){
    int option,r;



    struct sembuf sops [1];
    sops [0].sem_num = 0;
    sops [0].sem_op = 0;
    sops [0].sem_flg = 0;
    /*Getting command line arguments.*/
    while ((option = getopt(argc, argv, ":C:N:F:")) != -1)
    {
        switch (option)
        {
            case 'F':
                inputFile = optarg;
                break;
            case 'N':
                n = atoi(optarg);
                break;
            case 'C':
                c = atoi(optarg);
                break;
            case '?':
                perror("It does not fit format! Format must be :./hw4 -C 10 -N 5 -F inputfilePath\n");
                exit(EXIT_FAILURE);
                break;
        }
    }
    /*This condition to control format of command line arguments.*/
    if ((optind != 7))
    {
        perror("It does not fit format! Format must be :./hw4 -C 10 -N 5 -F inputfilePath\n");
        exit(EXIT_FAILURE);
    }
    if((n <= 1)){
        fprintf(stdout, "N must be bigger than 1\n");
        exit(EXIT_FAILURE);
    }
    if((c <= 4)){
        fprintf(stdout, "C must be bigger than 4\n");
        exit(EXIT_FAILURE);
    }
    leave=0;
    //  mutual exclusion semaphore, mutex_sem with an initial value 1.
    /* generate a key for creating semaphore  */
    if ((s_key = ftok (SEM_MUTEX_KEY, 'a')) == -1) {
        perror ("ftok"); exit (1);
    }
    if ((mutex_first = semget (s_key, 1, 0660 | IPC_CREAT)) == -1) {
        perror ("semget"); exit (1);
    }
    // Giving initial value. 
    sem_attr.val = 0;        // unlocked
    if (semctl (mutex_first, 0, SETVAL, sem_attr) == -1) {
        perror ("semctl SETVAL"); exit (1);
    }

    // counting semaphore, indicating the number of available buffers.
    /* generate a key for creating semaphore  */
    if ((s_key = ftok (SEM_BUFFER_COUNT_KEY, 'a')) == -1) {
        perror ("ftok"); exit (1);
    }
    if ((mutex_second = semget (s_key, 1, 0660 | IPC_CREAT)) == -1) {
        perror ("semget"); exit (1);
    }
    // giving initial values
    sem_attr.val = 0;    // MAX_BUFFERS are available
    if (semctl (mutex_second, 0, SETVAL, sem_attr) == -1) {
        perror (" semctl SETVAL "); exit (1);
    }

    // counting semaphore, indicating the number of strings to be printed.
    /* generate a key for creating semaphore  */
    if ((s_key = ftok (SEM_SPOOL_SIGNAL_KEY, 'a')) == -1) {
        perror ("ftok"); exit (1);
    }
    if ((spool_signal_sem = semget (s_key, 1, 0660 | IPC_CREAT)) == -1) {
        perror ("semget"); exit (1);
    }

    sops [0].sem_op = 1;
    if (semop (mutex_first, sops, 1) == -1) {
        perror ("semop: mutex_sem"); 
        exit (1);
    }

    sops [0].sem_op = -1;
    if (semop (mutex_first, sops, 1) == -1) {
        perror ("semop: mutex_sem"); 
        exit (1);
    }
    sops [0].sem_op = 1;
    if (semop (mutex_second, sops, 1) == -1) {
        perror ("semop: spool_signal_sem"); exit (1);
    }
    pthread_t consumers[c];
    int s, i;
    /*Creating 6 threads for consumers.*/
    int save[c];
    for (i = 0; i < c; i++)
    {
        save[i] = i;
        if ((s = pthread_create(&consumers[i], NULL, consumer,(void*) &save[i])) != 0)
        {
            fprintf(stderr, "Failed to pthread_create operation in main.\n");
            exit(EXIT_FAILURE);
        }
    }
    int fd;
        /*Opening input file.*/
    if ((fd = open(inputFile, O_RDONLY)) == -1)
    {
        perror("Failed to open input file in main.\n");
        exit(EXIT_FAILURE);
    }
    printf("%d\n",fd );
    char controlChar[1];
    int first=0,second=0;
    /*Controls the file whether it has a line that includes 2 same ingredients or not.If it has,print error message.*/
    while(read(fd, controlChar, 1)){
        if(controlChar[0] == '1')
            first++;
        else if(controlChar[0] == '2')
            second++;
    }
    if(first != c*n){
        fprintf(stderr, "There is no enough '1'\n");
        exit(EXIT_FAILURE);
    }
    if(second != c*n){
        fprintf(stderr, "There is no enough '2'\n");
        exit(EXIT_FAILURE);
    }
    lseek(fd, 0, SEEK_SET);
    first =0;
    second = 0;
        /*Controls the file whether it has a line that includes 2 same ingredients or not.If it has,print error message.*/
    while(read(fd, controlChar, 1)){
        // Is there a string to print? P (spool_signal_sem);
        if(controlChar[0] == '1'){
            fprintf(stdout, "Supplier: read from input a ‘1’. Current amounts: %d x ‘1’, %d x ‘2’.\n",firs++,secon);  
            first++;    
            fprintf(stdout, "Supplier: delivered a ‘1’. Post-delivery amounts: %d x ‘1’, %d x ‘2’.\n",firs,secon);  

        }
        else if(controlChar[0] == '2'){
            fprintf(stdout, "Supplier: read from input a ‘1’. Current amounts: %d x ‘1’, %d x ‘2’.\n",firs,secon++);  
            second++; 
            fprintf(stdout, "Supplier: delivered a ‘1’. Post-delivery amounts: %d x ‘1’, %d x ‘2’.\n",firs,secon);  
        }
        if(firs> 0 && secon>0){
            
          //  printf("first %d * %d\n", first,second);
            sem_attr.val = first;
            semctl(mutex_first, 0, SETVAL, sem_attr);

            sem_attr.val = second;
            semctl(mutex_second, 0, SETVAL, sem_attr);
        //    printf("içeride\n");
            
        }
    }
    leave =1;
    sem_attr.val = 0;
    semctl(mutex_first, 0, SETVAL, sem_attr);

    sem_attr.val = 0;
    semctl(mutex_second, 0, SETVAL, sem_attr);
    fprintf(stdout, "The Supplier has left.\n" );
     // Wait for producers to terminate
    for (i = 0; i < c; i++){
        
        if ((r = pthread_join (consumers [i], NULL)) == -1) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    }
        
        // giving initial values
    sem_attr.val = 0;    // 0 strings are available initially.
    if (semctl (spool_signal_sem, 0, SETVAL, sem_attr) == -1) {
        perror (" semctl SETVAL "); exit (1);

        // No more strings to print? Wait for spool_signal_sem to become 0

        if (semop (spool_signal_sem, sops, 1) == -1) {
            perror ("semop: spool_signal_sem"); exit (1);
        }

        // remove semaphores
        if (semctl (mutex_first, 0, IPC_RMID) == -1) {
            perror ("semctl IPC_RMID"); exit (1);
        }
        if (semctl (mutex_second, 0, IPC_RMID) == -1) {
            perror ("semctl IPC_RMID"); exit (1);
        }
        if (semctl (spool_signal_sem, 0, IPC_RMID) == -1) {
            perror ("semctl IPC_RMID"); exit (1);
        }
    }
    return 0;
}

static void *consumer(void *arg){
   // Create 10 strings and terminate
    int i;
    int my_id = *((int *) arg);
    int first ,second;
    struct sembuf sops [1];

    sops [0].sem_num = 0;
    sops [0].sem_op = 0;
    sops [0].sem_flg = 0;
    for (i = 0; i < n; i++) {
        /* There might be multiple producers. We must ensure that 
            only one producer uses buffer_index at a time.  */
        // P (mutex_sem);
        sops [0].sem_op = -1;
        if (semop (mutex_first, sops, 1) == -1)  {
            perror ("*semop: mutex_sem"); 
            exit (1);
        }

        sops [0].sem_op = -1;
        if (semop (mutex_second, sops, 1) == -1)  {
            perror ("semop: mutex_sem"); 
            exit (1);
        }
            first = semctl(mutex_first, 0, GETVAL, sem_attr);
            second = semctl(mutex_second, 0, GETVAL, sem_attr);
        // Critical section
            fprintf(stdout, "Consumer-%d at iteration %d (waiting). Current amounts: %d x ‘1’, %d x ‘2’.\n", my_id,i,firs--,secon--);
            sem_attr.val = --first;
            semctl(mutex_first, 0, SETVAL, sem_attr);

            sem_attr.val = --second;
            semctl(mutex_second, 0, SETVAL, sem_attr);
            fprintf(stdout, "Consumer-%d at iteration %d (consumed). Post-consumption amounts: %d x ‘1’, %d x ‘2’.\n", my_id,i,firs,secon);
        // Release mutex sem: V (mutex_sem)
        if((firs< 1 || secon< 1) && leave == 0){
            sops [0].sem_op = 0;
            if (semop (mutex_second, sops, 1) == -1) {
                perror ("semop: spool_signal_sem"); exit (1);
            }
            sops [0].sem_op = 0;
            if (semop (mutex_first, sops, 1) == -1) {
                perror ("semop: spool_signal_sem"); exit (1);
            }
        }
        else{
            sops [0].sem_op = 1;
            if (semop (mutex_first, sops, 1) == -1) {
                perror ("semop: spool_signal_sem"); exit (1);
            }
            sops [0].sem_op = 1;
            if (semop (mutex_second, sops, 1) == -1) {
                perror ("semop: spool_signal_sem"); exit (1);
            }
            
        }
       
    }
    fprintf(stdout, "Consumer-%d has left.\n",my_id );
    return 0;
}
