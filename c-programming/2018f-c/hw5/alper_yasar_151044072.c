#include <stdio.h>
#include <string.h>

#define LENGHTofTEXT 250
#define LENGHTofNAME  10

void printing(char text[LENGHTofTEXT],int loc,int lenght,int tree,FILE* outp,int control);
											/*loc = location of characters in input files*/
											/*lenght = lenght of words*/
											/*tree = how many '-' writing to file*/	
											/*control = writing words to file when see ',' or ')'*/
															   /*if ',)' they come by sequantial */
int main(){

	int startSpace = 0,i=0;
	char text[LENGHTofTEXT];
	FILE *inp,*outp;
			/*opening files*/
	inp = fopen("input.txt","r");
	outp = fopen("output.txt","w");

	while(fscanf(inp, "%c", &text[i]) !=EOF){							/*read each character from input file*/
																		/*if has whitespace character at beginning text pass next character*/
		if((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')
		    || startSpace != 0 || text[i]=='('){									/*startSpace for control of whitespace character of beginning*/
			i++;																/*do not increase counter*/
			startSpace = 1;
		}
	}
	
	printing(text,0,0,0,outp,0);
	/*closing files*/
	fclose(inp);
	fclose(outp);
	return 0;
}
							/*location of char || lenght of words*/
void printing(char text[LENGHTofTEXT],int loc,int lenght,int tree,FILE* outp,int control){

	char words[LENGHTofNAME];
	int i;
	if(text[loc] != '\0'){				/*until to NULL character*/
		if(text[loc+lenght] == '('){	/*when see '(' pass the nex character*/
			tree++;						/*and increase variable tree for'-'*/
			loc++;
			lenght=0;					/*equal zero lenght of words*/
		}
		else if(text[loc+lenght] == ')'){
			i = tree;
			if(control == 0){			/*control = writing words if ',)' they come by sequantial */
				while(i>0){					/*writing '-' for tree*/
					fprintf(outp,"-");
					i--;
				}
					/*assign word to words array*/
				strncpy(words,&text[loc],lenght);
				words[lenght] = '\0';			/*assign NULL to last character */
				fprintf(outp, "%s\n", words);	/*writing to file words*/
			}
			tree--;						/*and decrease variable tree for'-'*/
			loc += lenght+1;			/*pass after the next of character')'*/
			lenght=0;
			control = 1;
		}
		else if(text[loc+lenght] == ','){
			if(control == 0){		/*control = writing words if ',)' they come by sequantial */
				i = tree;
				while(i>0){
					fprintf(outp,"-");
					i--;
				}
							/*assign word to words array*/
				strncpy(words,&text[loc],lenght);		
				words[lenght] = '\0';		/*assign NULL to last character */
				fprintf(outp, "%s\n", words);	/*writing to file words*/
				loc += lenght+1;			/*pass after the next of character','*/
				lenght=0;
				control = 1;
			}
			else{		/*if previous character is ')'*/
				loc++;
				control=1;
			}
		}
		else{
			control = 0;				/*if text is a letter or whitespace*/
			lenght++;					/*location number stay stabil and increase lenght*/
										/*for assign words to array*/
			if(text[loc+lenght] == '\0'){		/*if the last character is words*/
				if(text[loc-1] != ')'){			/*print them to file*/
					strncpy(words,&text[loc],lenght);
					words[lenght] = '\0';
					fprintf(outp, "%s\n", words);
				}
				loc += lenght;			/*increase location number*/
			}
		}
		printing(text,loc,lenght,tree,outp,control);		/*recursion*/
	}
}