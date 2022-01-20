#include "stdio.h"

void readFile(double* number);
void avarage(double* number);

#define p1 0.5
#define p2 20
#define LenghtofSequence 1000
#define LenghtofChunk 100

int main()
{
	double number[LenghtofSequence];

	readFile(number);	/*read from file to number[]*/

	avarage(number);	/*calculate average and order and write to file*/

	return 0;
}

void readFile(double* number)
{										/*reading from file*/
	int i,input_status;
	FILE *inp; 
	inp = fopen("input.txt","r");		
	i = 0;
	
	while(!feof(inp))						/*loop until to EOF and scan double variable to array*/
	{
		fscanf(inp, "%lf", &number[i]);
			i++;	
	}

	number[i-1] = EOF;							/*beacuse of overread*/		

	fclose(inp);
}

void avarage(double* number)
{
	int i=0,j = 0,k=0,counter=0;
	double chunk[LenghtofChunk][3];				/*first row of every chunks is average of chunk (eg.chunk[0][0],chunk[1][0]*/
	double addedAverage,temp[3];				/*second array holds the number where starting in number array[] (k) 	
												(eg. chunk[0][1] = 0(12.432 number[0]),chunk[1][1] = 2(344.6 number[2])) */
												/*third row hold the number of chunks*/
	FILE *outp; 
	outp = fopen("output.txt","w");				/*file open*/
	
	chunk[i][0] = number[k];					/*first chunk first element, because first element is average*/
	chunk[i][1] = k;							
	chunk[i][2] = 1;
	
	while(number[k+1] != EOF){					/*loop until end of file*/
		k++;									/*read the next element of number(number[1])*/

												/*new awerage = (average of chunk(chunk[0][0])*number of chunks(chunk[0][2])
																+ array (number[1])) / (number of array + 1(chunk[0][2]+1)))*/
		addedAverage = ((chunk[i][0]*(chunk[i][2]) + number[k]) / ((chunk[i][2]+1)));
		
		if(!(addedAverage > chunk[i][0]*(1+p1) || addedAverage < chunk[i][0]*(1-p1) || /*condition of giving*/
			 chunk[i][0] > number[k]*p2 || chunk[i][0] < number[k]/p2))
		{
			chunk[i][2]++; 						/*increase number of element*/
			chunk[i][0] = addedAverage;			/*renew average*/
		}

		else
		{
			i++;										
			chunk[i][0] = number[k];			/*make a new chunk*/
			chunk[i][1] = k;
			chunk[i][2] = 1;
		}
	}
	
	j=0;
	
	while(j<i)									/*ordered as stacked lines based on the calculated average of each*/
	{
		k=j+1;
		
		while(k<=i)
		{        
			if(chunk[j][0] > chunk[k][0])		/*eg. if chunk[0][0] > chunk[1][0]*/
			{
				temp[0] = chunk[j][0];			/*change averages*/
				temp[1] = chunk[j][1];
				temp[2] = chunk[j][2];
				chunk[j][0] = chunk[k][0];		/*change starting number of chunks*/
				chunk[j][1] = chunk[k][1];
				chunk[j][2] = chunk[k][2];
				chunk[k][0] = temp[0];			/*change number of chunks*/
				chunk[k][1] = temp[1];
				chunk[k][2] = temp[2];
			}
 			k++;
		}
		j++;
	}	
	
	j=0;
	
	while(j<=i)								/*loop until to chunk number*/
	{
		for (k = 0; k < chunk[j][2]; ++k)		/*loop until number of chunk*/
		{
			fprintf(outp,"%.4lf ",number[(int)(chunk[j][1])+k]);	/*write to file with ordering*/
		}
		
		j++;	
		fprintf(outp, "\n");		/*write newline to file*/
	}
	
	fclose(outp);

}