#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGHT 100
typedef struct product
{
	char *object;
	double numberofitems;
}product;


double str(struct product *obj,int count,int k);

int main()
{
	product *obj,*root;
	char *entry;			/*definitions of object or subobject*/	
	int i =0,control = 0,controlFirstStruct = 0,controlNext = 0;
	char *temp;
	double price;


	printf("What the object:\n");
	entry = (char*)malloc(MAXLENGHT*sizeof(char));

	   fgets(entry,MAXLENGHT,stdin);
	   	entry[strlen(entry)-1]='\0';
	obj=(product*)malloc(sizeof(product)*100);
	obj[i].object = strtok(entry," ");
	obj[i].numberofitems = 1;
	printf("Define %s?:\n", obj[i].object);

	price = str(obj,i,i+1);

	printf("Total cost of %s is %.2lf\n",obj[i].object,price);

	free(obj);
	free(entry);


 	return 0;
}

double str(struct product *obj,int count,int k){
	int i=0,j=0;
	char *entry;
	char *temp;
	double tempNum,totalPrice=0;
	count+=k;
	
	entry = (char*)malloc(MAXLENGHT*sizeof(char));

	   fgets(entry,MAXLENGHT,stdin);
	   temp = (char*)malloc(MAXLENGHT*sizeof(char));
	temp = strtok(entry," ");
	do{
		if (temp[strlen(temp)-1]=='\n')
		{
			temp[strlen(temp)-1]='\0';
		}
			
		if(i%2==0){
			sscanf(temp,"%lf",&tempNum);
		}
		else if(i%2 == 1){
			j++;

	
				obj[count+j-1].numberofitems = tempNum;
				obj[count+j-1].object =(char*)malloc(MAXLENGHT*sizeof(char));
				strcpy(obj[count+j-1].object,temp);

		}
		i++;

	}while((temp = strtok(NULL," ")) != 0);

	j=1;
	if(i==1){
		totalPrice = tempNum;
	}
	else{
		while(j<=i/2){
			printf("Define %s in %s?:\n",obj[count+j-1].object,obj[count-k].object);
			totalPrice+=str(obj,count+j-1,i/2)*obj[count+j-1].numberofitems;
			j++;

		}
	}

	return totalPrice;
}
