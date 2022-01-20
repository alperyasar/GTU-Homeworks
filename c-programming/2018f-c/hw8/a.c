#include <stdio.h>
#include <stdlib.h>

typedef struct island
{
	int **M;
}node;

void rec(node *islands,int x,int y);


int main()
{
	int L;
	int i=0,j=0,a;
	node *islands = (node*)malloc(sizeof(node));
	FILE *inp,*outp;
	inp= fopen("input.txt","r");
	outp= fopen("output.txt","w");

	
	islands->M = malloc(sizeof(int*)*10);

	fscanf(inp,"%d",&L);
/*	while(fscanf(inp,"%s",a) != EOF){
		printf("%-3sa - ",a);
		M[i][j] = *a -'0';
		printf("%-3dM - [%d][%d]\n",M[i][j],i,j);
		j++;
		if(j == 10){
			i++;
			j=0;
		}
	}*/
	while(i<10){
		islands->M[i] = (int*)malloc(sizeof(int)*10);
		while(j<10){
			fscanf(inp,"%d",&a);
			if(a>L){
				islands->M[i][j] = 1;
				printf("%d",islands->M[i][j] );
			}
			else{
				islands->M[i][j] = 0; 
				printf(" ");
			}
			j++;
		}
		printf("\n");
		i++;
		j=0;
	}
	printf("\n");
	i=0;
	while(i<10){
		while(j<10){
			if(islands->M[i][j] == 1){
				islands->M[i][j] = 2;
				rec(islands,i,j);
				printf("**%d-%d\n",i,j);
			}
			j++;
		}
		i++;
		j=0;
	}
	i=0;
	while(i<10){
		while(j<10){
			printf("%d",islands->M[i][j] );
			j++;
		}
		printf("\n");
		j=0;
		i++;
	}
	

	return 0;
}

void rec(node *islands,int x,int y){
//	printf("a\n");
	printf("%d,%d\t",x,y);
	if(y < 9 && islands->M[x][y+1] == 1){
		islands->M[x][y] = 2;
		rec(islands,x,y+1);
	}
	if(y > 0 && islands->M[x][y-1] == 1 ){
		islands->M[x][y] = 2;
		rec(islands,x,y-1);
	}
	if(x < 9 && islands->M[x+1][y] == 1 ){
		islands->M[x][y] = 2;
		rec(islands,x+1,y);
	}
	if(x > 9 && islands->M[x-1][y] == 1){
		islands->M[x][y] = 2;
		rec(islands,x-1,y);
	}



}
