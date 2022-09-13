#include "hdr.h"

int calculateCov(int mean,int k);
int calculateCov1(int mean1,int mean2,int k,int l);
int main(int argc, char *argv[]){
	int x=0,y=0,z=0,i=0,outputFd;
	struct flock fl1,fl2;
	char **ep;
	int matrix[9];
	char buf[12] = {0}; 
//	char buf[4] = {0}; 
	    // file locks

	  //  sigset_t origMask, blockMask;
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");
    // read file
    outputFd = open(argv[4], O_WRONLY | O_APPEND);
    if (outputFd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    memset(&fl1,0 , sizeof(fl1));
    memset(&fl2,0 , sizeof(fl1));

	fl1.l_type = F_RDLCK;
	fl2.l_type = F_WRLCK;
    // lock file 
    fcntl(outputFd,F_SETLKW,&fl1);
    fcntl(outputFd,F_SETLKW,&fl2);  
    fprintf(stdout, "Created %ld with ",(long)getpid() ); 
	for (ep = environ; *ep != NULL; ep++){
		i++;
		x+=(int)ep[0][0];
		y+=(int)ep[0][1];
		z+=(int)ep[0][2];
		fprintf(stdout, "(%d,%d,%d)",(int)ep[0][0],(int)ep[0][1],(int)ep[0][2]); 
		if(i!=10)
			fprintf(stdout, ","); 
	}
	fprintf(stdout, "\n");
	x=x/10;
	y=y/10;
	z=z/10;
	printf("** x:%d - y:%d - z:%d\n",x,y,z);
	matrix[0] = calculateCov(x,0);
	matrix[4] = calculateCov(y,1);
	matrix[8] = calculateCov(z,2);
	matrix[1] = matrix[3] = calculateCov1(x,y,0,1);		
	matrix[2] = matrix[6] = calculateCov1(x,z,0,2);	
	matrix[5] = matrix[7] = calculateCov1(z,y,2,1);

	for(int j=1;j<=9;j++){
		memset(buf, 0, sizeof (buf));
	    snprintf(buf, sizeof matrix[j-1], "%d", matrix[j-1]);               //print to buffer 
		write(outputFd, buf, strlen(buf));
		write(outputFd, " ", 1);
		if(j%3==0){
 			write(outputFd,"\n", 1);
		}
	}
	write(outputFd,"\n", 1);
	fl1.l_type = F_UNLCK;
	fl2.l_type = F_UNLCK;
	fcntl(outputFd,F_SETLKW,&fl1);
	fcntl(outputFd,F_SETLKW,&fl2);
	
    if (close(outputFd) == -1)
    	perror("File close"); 
    return 0;
}
int calculateCov(int mean,int k){
	int temp=0;
	char **ep;
	int x;
	for (ep = environ; *ep != NULL; ep++){
		x = (int)ep[0][k];
		temp += ((x - mean) * (x - mean));
	}
	return temp/10;
}
int calculateCov1(int mean1,int mean2,int k,int l){
	int temp=0;
	char **ep;
	int x,y;
	for (ep = environ; *ep != NULL; ep++){
		x=(int)ep[0][k];
		y=(int)ep[0][l];

		temp += ((x - mean1) * (y - mean2));		
	}
	return temp/10;
}

/*This handler for SIGUSR1 and SIGUSR2 signals*/
void handler(int sig) {
	fprintf(stderr, "Process %ld received signal %d (%s)\n",
        (long) getpid(), sig, strsignal(sig));
    if (close(outputFd) == -1)
    	perror("File close"); 
    exit(EXIT_SUCCESS);
}