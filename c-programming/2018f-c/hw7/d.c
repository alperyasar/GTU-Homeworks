#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEGATE 10

typedef struct gate
{
	char *input;
	int *value;
	struct gate *right;
	struct gate *left;

}gate;

//int gateResult(char *gt,int value1,int value2);
void readAndWriteFile();

int main()
{

	readAndWriteFile();
	return 0;
}

/*
int gateResult(char *gt,int value1,int value2){
	char **logic = {AND,OR,NOT,FLIPFLOP};
	int result;
		result = value1 + value2;
	if(strcmp(gt,&logic[0]) == 0){
		if(result == 2) return 1;
		else 			return 0;
	}
	else if(strcmp(gt,&logic[1]) == 0){
		if(result == 0)	return 0;
		else 			return 1;	
	}
	else if(strcmp(gt,&logic[2]) == 0){
		if(result == 1)	return 0;
		else 			return 1;
	}
	else if(strcmp(gt,&logic[3]) == 0){
		if(result == 1)	return 1;
		else 			return 0;
	}

}*/

void readAndWriteFile(){
	gate *inputs,*root;
	FILE *inp1,*inp2,*outp;
	char *line,c,*logicNumber;
	char *logicGate, iden1[10],iden2[10];
	int idenControl = 0;
	int sumofLogic,cntrl=0;
	int i=0,j=0,spaceControl=0,space2=0;


	inp1 = fopen("input.txt","r");
	inp2 = fopen("circuit.txt","r");
	outp = fopen("output.txt","w");

	line = (char*)malloc(sizeof(char));
	while ((c = fgetc(inp1)) != EOF)
    {
        line[i++] = (char) c;
       	line = (char*)realloc(line,sizeof(char)*i);
    }
    line[i] = '\n';
    printf("aaa\n");
	inputs = (gate*)malloc(sizeof(gate));
	inputs->input = (char*)malloc(sizeof(char)*SIZEGATE);
	inputs->input=strtok(line," ");
	inputs->right=NULL;
	inputs->left=NULL;
    root = inputs;
    i=0;

    logicNumber = (char*)malloc(sizeof(char));
    while ((c = fgetc(inp2)) != EOF)
    {
        logicNumber[i++] = (char) c;
       	logicNumber = (char*)realloc(logicNumber,sizeof(char)*(i+2));
    }
    logicNumber[i] = '\n';
    i=0;
    printf("%s\n",inputs->input);
    printf("%d,%c\n", i,logicNumber[i]);
     while(logicNumber[i]){
    	while(logicNumber[i+1] != '\n'){
    		if(logicNumber[i] == '0' || logicNumber[i] == '1'){
    			printf("%d--%c----", i,logicNumber[i]);
    			inputs->right = (gate*)malloc(sizeof(gate));
			    inputs->right->left = inputs;
			    inputs = inputs->right;
				inputs->input = (char*)malloc(sizeof(char)*SIZEGATE);
				inputs->input=strtok(NULL," ");
				inputs->right=NULL;
				printf("%s\n",inputs->input);
	    		}
	    		i++;
    	}

    	inputs->right = (gate*)malloc(sizeof(gate));
	    inputs->right->left = inputs;
	    inputs = inputs->right;
		inputs->input = (char*)malloc(sizeof(char)*SIZEGATE);
		inputs->input=strtok(NULL,"\n");
		inputs->right=NULL;
		    	printf("%d--%c----", i,logicNumber[i]);
	//	printf("%s----\n",inputs->left->input);

		while(logicGate = strtok(NULL," ")){
			 
		}
		i+=2;

    }
/*
    while((c = fgetc(inp2)) != EOF) {
    	while((c = fgetc(inp2)) != '\n')
	    	if(c == '0' || c == '1'){
	    		if(j==0){
	    			logicNumber = (int*)malloc(sizeof(int));
	    			logicNumber[i] = c-'0';

	    			inputs = (gate*)malloc(sizeof(gate));
	    			inputs[j].input = (char*)malloc(sizeof(char)*SIZEGATE);
	    			inputs[j].input=strtok(line," ");
	    			inputs[j].right=NULL;
	    			inputs[j].left=NULL;
	    			j++;
	    		}
	    		if(c != )
			       	logicNumber = (int*)realloc(logicNumber,sizeof(int)*(i+1));   	
					logicNumber[i] = c-'0';
					printf("%d ",logicNumber[i]);
				}
		}
		if(c == '\n'){

		}
		i++;
	}

	sumofLogic = i;
	i=0;*/

}