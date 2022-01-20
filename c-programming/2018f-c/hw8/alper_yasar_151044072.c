#include <stdio.h>
#include <stdlib.h>

#define MAX_X 512
#define MAX_Y 512 
typedef struct island
{
	int **M;
}node;

void rec(node *islands,int x,int y);

int main()
{
	int L;							/*water level information*/
	int i=0,j=0,a,c=2;				/*a: elevation matrix M, c: sum of islands */
	node *islands = (node*)malloc(sizeof(node));
	
	FILE *inp,*outp;					/*open file*/
	inp= fopen("input.txt","r");
	outp= fopen("output.txt","w");
											
	fscanf(inp,"%d",&L);				/*read first value for water level*/

	islands->M = malloc(sizeof(int*)*MAX_X);			/*each rows*/
	while(i<MAX_X){
		islands->M[i] = (int*)malloc(sizeof(int)*MAX_Y);	/*each columns*/
		while(j<MAX_Y){
			fscanf(inp,"%d",&a);					/*read each islnad elevations*/
			if(a>L)
				islands->M[i][j] = 1;		/*check the island elevation is higher or lower water elevation*/
			
			else
				islands->M[i][j] = 0; 
			j++;
		}
		i++;
		j=0;
	}
	i=0;
	while(i<MAX_X){
		while(j<MAX_Y){
			if(islands->M[i][j] == 1){
				islands->M[i][j] = c;  /*assing sequence number first coordinate of island*/
				rec(islands,i,j);
				c++;					/*need for found a new island, assign a next number*/
			}
			j++;
		}
		i++;
		j=0;
	}
	fprintf(outp, "%d\n",c-2 );			/*number of islands write to file*/
	c=2;
	i=0;
	while(i<MAX_X){
		while(j<MAX_Y){
			if(islands->M[i][j] == c){
				islands->M[i][j] = 2;			
				fprintf(outp,"%d %d\n",i,j);	/*write first coordinate each island to file*/
				c++;
			}
			j++;
		}
		i++;
		j=0;
	}

	free(islands);
	/*close files*/
	fclose(inp);
	fclose(outp);
	return 0;
}

void rec(node *islands,int x,int y){

	if(y < MAX_Y-1 && islands->M[x][y+1] == 1){			/*check the right column*/
		islands->M[x][y+1] = 2;
		rec(islands,x,y+1);
	}
	if(y > 0 && islands->M[x][y-1] == 1 ){				/*check the left column*/
		islands->M[x][y-1] = 2;
		rec(islands,x,y-1);
	}
	if(x < MAX_X-1 && islands->M[x+1][y] == 1 ){		/*check the up row*/
		islands->M[x+1][y] = 2;
		rec(islands,x+1,y);
	}
	if(x > 0 && islands->M[x-1][y] == 1){				/*check the down row*/
		islands->M[x-1][y] = 2;
		rec(islands,x-1,y);
	}
}
