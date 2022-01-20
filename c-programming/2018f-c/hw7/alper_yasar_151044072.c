#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEGATE 10

typedef struct gate
{
	char *input;
	int value;
	struct gate *right;
	struct gate *left;

}gate;

void readAndWriteFile();
void f(char *in1,char * in2,FILE *dosya,int *ff);
int gateResult(char *gt,int value1,int value2);

int main()
{

	readAndWriteFile();
	return 0;
}


int gateResult(char *gt,int value1,int value2){
	char logic[4][10] = {"AND","OR","NOT","FLIPFLOP"};
	int result;
		result = value1 + value2;
	if(strcmp(gt,logic[0]) == 0){		/*for AND gate each inputs must 1 so result 2*/
		if(result == 2) return 1;
		else 			return 0;
	}
	else if(strcmp(gt,logic[1]) == 0){		/*OR gate : if each inputs are 0 result equal zero or 1*/
		if(result == 0)	return 0;
		else 			return 1;	
	}
	else if(strcmp(gt,logic[2]) == 0){		/*NOT gate: change input 1 to 0, 0 to 1*/
		if(result == 0)	return 1;
		else 			return 0;
	}
	else if(strcmp(gt,logic[3]) == 0){		/*FLIPFLOP gate: speacial condition*/
		if(result == 1)	return 1;
		else 			return 0;
	}

}

void readAndWriteFile(){
	gate *inputs,*root;
	FILE *inp1,*inp2,*outp;
	char *line,c,*logicNumber,*logicGate;
	int i=0,j=0,ff=0;


	inp1 = fopen("input.txt","r");
	inp2 = fopen("circuit.txt","r");
	outp = fopen("output.txt","w");

	line = (char*)malloc(sizeof(char));
	while ((c = fgetc(inp2)) != EOF)					/*read each character and increase memory area from input*/
    {
        line[i++] = (char) c;
       	line = (char*)realloc(line,sizeof(char)*(i+1));
    }
    line[i] = '\n';										/*assign new line charachter to last*/
    j=i;
 
    i=0;

    logicNumber = (char*)malloc(sizeof(char));
    while ((c = fgetc(inp1)) != EOF)				/*read each character and increase memory area from circuit*/
    {
        logicNumber[i] = (char) c;
        i++;
       	logicNumber = (char*)realloc(logicNumber,sizeof(char)*(i+1));
       	if(logicNumber[i-1] == '\n'){									/*initialize f function when the circuit line ended*/
     		logicGate = (char*)malloc(sizeof(char)*(j+1));				/*assign line string to new string */
     		strcpy(logicGate,line);										/*for avoid changing line in f function */
       		f(logicGate,logicNumber,outp,&ff);
       		free(logicGate);
       		i=0;
       	}
    }
    logicNumber[i] = '\n';
	f(line,logicNumber,outp,&ff);					/*initialize f function when the circuit line ended*/
    i=0;

}
void f(char *in1,char * in2,FILE *dosya,int *ff){
	gate *inputs,*root;
	char *gt,*newres,*gate1,*gate2;
	int cntrl =0,a1,a2;
	int i =0,j=0;

	gt = (char*)malloc(sizeof(char)*SIZEGATE);					/*assign gate ("AND","OR","NOT","FLIPFLOP"), input file*/
	newres = (char*)malloc(sizeof(char)*SIZEGATE);				/*result input (ex. a AND b -> and1)*/

	inputs = (gate*)malloc(sizeof(gate));						/*it's first struct*/
	inputs->input = (char*)malloc(sizeof(char)*SIZEGATE);		/*first word*/
	inputs->input=strtok(in1," ");								
	inputs->right=NULL;
	inputs->left=NULL;
    root = inputs;
	while(in2[i+1] != '\n'){
		if(in2[i] == '0' || in2[i] == '1'){
			inputs->right = (gate*)malloc(sizeof(gate));			/*assign each value in circuit.txt to input in input.txt*/
		    inputs->right->left = inputs;
		    inputs = inputs->right;
			inputs->input = (char*)malloc(sizeof(char)*SIZEGATE);
			inputs->input=strtok(NULL," ");
			inputs->value = in2[i] - '0';
			inputs->right=NULL;
    		}
    		i++;
	}
	inputs->right = (gate*)malloc(sizeof(gate));				/*assign last value in circuit.txt to last input in input.txt*/
    inputs->right->left = inputs;
    inputs = inputs->right;
	inputs->input = (char*)malloc(sizeof(char)*SIZEGATE);   
	inputs->input=strtok(NULL,"\n");
	inputs->value = in2[i] - '0';
	inputs->right=NULL;
	inputs = root->right;

	while(in1[j] != '\0'){

		gt = strtok(NULL," ");									/*first word of line, name of gate*/
		newres = strtok(NULL," ");								/*inputs result*/

		while(in1[j] != '\n'){
			if(in1[j] == ' '){									/*if inputs are 2 it's control and assign to a1*/
				cntrl++;
				gate1 = strtok(NULL," ");
				if(strcmp(gate1,inputs->input) == 0){			/*control input, may it right input*/
					a1 = inputs->value;
					inputs = inputs->right;
				}
				else if(strcmp(gate1,inputs->left->input) == 0){	/*or left input and assign value in there to a1*/
					a1 = inputs->left->value;
				}
			}
			j++;
		}
		gate2 = strtok(NULL,"\n");
		if(strcmp(gate2,inputs->input) == 0){				/*control input, may it right input*/
			a2 = inputs->value;
		}
		else if(strcmp(gate2,inputs->left->input) == 0){			/*or left input and assign value in there to a1*/
			a2 = inputs->left->value;
		}
		if(cntrl == 1){									/*if inputs number are 2*/
			a1 = gateResult(gt,a1,a2);					/*assign result to a1*/
		}	
		else{								/*or 1*/
			if(strcmp(gt,"FLIPFLOP") == 0){			/*control it's if GATE is FLIPFLOP*/
				a1 = *ff;	
			}
			else{					/*or NOT*/
				a1 = 0;	
			}
			a1 = gateResult(gt,a1,a2);					/*assign result to a1*/

		}
		if(inputs->right == NULL){							/*check the next struct is empty*/
			inputs->right = (gate*)malloc(sizeof(gate));	/*if next struct is empty assing new result it*/
		    inputs->right->left = inputs->left;				/*and connect the left struct to it*/
		    inputs = inputs->right;
			inputs->input = (char*)malloc(sizeof(char)*SIZEGATE);
			inputs->input=newres;
			inputs->value = a1;
			inputs->right=NULL;
		}
		else{
			free(inputs->left);								/*if the next struct is not empty*/
			inputs->left = (gate*)malloc(sizeof(gate));		/*erase the left struct and define new struct to left*/
			inputs->left->input = (char*)malloc(sizeof(char)*SIZEGATE);
		    inputs->left->input = newres;					/*and assign the result it*/
			inputs->left->value = a1;
			inputs->right->left = inputs->left;
			inputs= inputs->right;
		}
		cntrl = 0;
		j++;

		if(strcmp(gt,"FLIPFLOP") == 0){						/*hold the new flipout in variable*/
			*ff = a1;	
		}
	}
	fprintf(dosya, "%d\n",inputs->value );				/*print to output file*/


}