#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct gate
{
	char *input;
	int *value;
}gates;

int main()
{
	gates *inputs;
	FILE *inp1,*inp2;
	char *line,c,*logicNumber;
	int i=0,j=0,spaceControl=0,space2=0;
	inp1 = fopen("input.txt","r");
	inp2 = fopen("circuit.txt","r");
	line = (char*)malloc(sizeof(char));
	while ((c = fgetc(inp1)) != EOF)
    {
        line[i++] = (char) c;
       	line = (char*)realloc(line,sizeof(char)*i);
       	if(line[i-1] == ' '){
       		spaceControl++;
       	}
    }
    line[i] = '\n';
    i=0;


    logicNumber = (char*)malloc(sizeof(char));
    while ((c = fgetc(inp2)) != EOF)
    {
        logicNumber[i++] = (char) c;
       	logicNumber = (char*)realloc(logicNumber,sizeof(char)*(i+1));
    }
    logicNumber[i] = '\n';
    i=0;
    while(logicNumber[i]){
    	if(logicNumber[i+1] != '\n')
    		printf("%c",logicNumber[i] );
    	i++;
    	
    }
	i=0;
 //   printf("%d,%d\n",i,spaceControl);
    while(space2 < spaceControl){
	    while(line[i]!= '\n'){
	    //	printf("%d**%c**",i,line[i]);
	    	if(line[i] == ' ' && j==0){
		    	inputs.rights = (gates*)malloc(sizeof(gates));
			    inputs.left = inputs;
			    inputs = inputs.rights;
			    inputs[j].input =(char*) malloc(sizeof(char)*10);
			    inputs[j].input=strtok(line," ");
			    printf("%s ",inputs[j].input );
	    		j++;
	    		space2++;
	    	}
			else if(line[i] == ' '){
	    		j++;
	    		inputs = (gates*)realloc(inputs,sizeof(gates)*(j));
	    		
	    		inputs[j-1].input = (char*)malloc(sizeof(char)*10);
	    		inputs[j-1].input=strtok(NULL," ");
	    		printf("%s ",inputs[j-1].input );
	    		space2++;	    	
	    	}


	    	i++;
	    }
	    int k =0;
	    while(k < i)
	    	printf("%c",line[k++] );
	        	j++;
	    	inputs = (gates*)realloc(inputs,sizeof(gates)*(j));
	    		
	    		inputs[j-1].input = (char*)malloc(sizeof(char)*10);
	    		inputs[j-1].input=strtok(NULL,"\n");
	    		printf("\n\n%s\n",inputs[j-1].input );
	    i++;
	}
 /*   s1=strtok(line," ");
    s2=strtok(NULL," ");
    s3=strtok(NULL," ");
    s4=strtok(NULL," ");
    s5=strtok(NULL," \n");
    s6=strtok(NULL," ");
    printf("%s %s %s %s- %s %s\n",s1,s2,s3,s4,s5,s6);*/
	
	return 0;
}