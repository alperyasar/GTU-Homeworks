#include <stdio.h>
#include <string.h>
#include <math.h>


#define POLYNOMLENGHT 1000
#define NUMBERLENGHT  100

void funtcion();
void evaluate(char polynm[POLYNOMLENGHT],double numb[NUMBERLENGHT],double results[NUMBERLENGHT],
			  int sizeofnumber, int sizeofpolynom);

int main()
{
	funtcion();
	return 0;
}

void funtcion(){
	int i,sizeofpolynom,sizeofnumber;
	FILE *poly,*value,*evaluation;
	char polynm[POLYNOMLENGHT];
	double numb[NUMBERLENGHT], results[NUMBERLENGHT];

	/*open files*/
	poly = fopen("polynomial.txt","r");
	value = fopen("values.txt","r");
	evaluation = fopen("evaluations.txt","w");
	while(fscanf(poly, "%c", &polynm[i]) !=EOF){		/*read each character from polynomial file*/
		if(polynm[i] != ' ')							/*if has whitespace character pass next character*/
			i++;										/*do not increase counter*/
	}
	sizeofpolynom=i;			/*assign counter another variable*/
	
	i=0;
	while(fscanf(value, "%lf", &numb[i]) !=EOF){		/*read each value from values file*/
		i++;
	}
	printf("%d\n",i);	
	sizeofnumber = i;							/*assign counter another variable*/
	
	evaluate(polynm,numb,results,sizeofnumber,sizeofpolynom);

	for (i = 0; i < sizeofnumber; ++i){				/*write to evaluations file*/
		fprintf(evaluation, "%.2lf\n", results[i]);
	}
	/*close all*/
	fclose(poly);
	fclose(value);
	fclose(evaluation);

}

void evaluate(char polynm[POLYNOMLENGHT],double numb[NUMBERLENGHT],double results[NUMBERLENGHT],
			  int sizeofnumber, int sizeofpolynom){
	int i=0,j,k=0,ust;
	char addORsub;						/*symbol of add or substraction*/
	double mult=1.0,exp,lastMult;      /*mult => multiplier, exp => exponential*/
	double res=0;			/*res => result*/

	while(i<sizeofnumber){
		j=0;
		results[i] = 0;
		addORsub = '+';		/*if first character of polynom is not '-' and there is not any mark
							  in front of them so first mark is '+'*/
		lastMult = 0;
		while(j<sizeofpolynom){		/*loop condition chech everytime one mark to another mark*/
			res = 0;				

			if(polynm[j] == '-'){	/*if see this character assign addORsub '-'*/
				addORsub = '-';
				j++;
			}
			else if(polynm[j] == '+'){	/*if see this character assign addORsub '+'*/
				addORsub = '+';
				j++;
			}
			if(polynm[j]>= '0' && polynm[j]<= '9'){	/*check the character is a number*/
													/*if the character is number assign it to mult */
				sscanf(&polynm[j], "%lf", &mult);	
				j++;								/*and increase control to after the mult*/
				while((polynm[j]>= '0' && polynm[j]<= '9') || polynm[j] == '.'){
					j++;
				}
				
				if(polynm[j] != 'x') /*check the number if is a multipler or just adding or substracting number*/
					lastMult = mult;	/*if after the number does not exist 'x' assign mult to lastMult*/
				else lastMult = 0;		/*it's require for adding to result*/
				
			}
			else if(polynm[j] == 'x' && !(polynm[j]>= '0' && polynm[j]<= '9')) 
				mult = 1.0;		/*if before the 'x' character does not any number*/
								/*assign mult 1 for multiplier*/
			if(polynm[j] == EOF || polynm[j] == '+' || polynm[j] == '-'){ 	/*if next character equal them*/
				if(addORsub == '-')								/*add mult to result or substract mult from result*/
					results[i] -= mult;
				else if(addORsub == '+')
					results[i] += mult;

			}			/*if next char equal 'x'*/
			if(polynm[j] == 'x'){		
				j++;		/*check the next char is '^'*/
				if(polynm[j] == '^'){	/*it's mean exponantial*/
					j++;
					sscanf(&polynm[j], "%d", &ust);
								/*and increase control to after the ust*/
					while((polynm[j]>= '0' && polynm[j]<= '9') || polynm[j] == '.'){ 
						j++;
					}
					exp = pow(numb[i],ust);		/* numb^ust*/
					res += mult*exp;			/* mult*numb^ust*/

					if(addORsub == '-')		/*add mult to result or substract mult from result*/
						results[i] -= res;
					else if(addORsub == '+')
						results[i] += res;
				}
				else{					/*if next char not equal to '^'*/
					res += mult*numb[i];	/*mult*numb*/
					
					if(addORsub == '-')
						results[i] -= res;
					else if(addORsub == '+')
						results[i] += res;
				}
			}
			
		}			/*if ending of polynom is a number*/
		if(polynm[j-1] >= '0' && polynm[j-1] <= '9'){
			if(addORsub == '-')
				results[i] -= lastMult;
			else if(addORsub == '+')
				results[i] += lastMult;

		}
		i++;
	}


}
