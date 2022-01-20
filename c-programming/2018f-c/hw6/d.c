#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGHT 100
typedef struct product
{
	char *object;
	double numberofitems;
	struct product *next;
	struct product *subobject;
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
//	scanf("%[^\n]s",entry);
	   fgets(entry,MAXLENGHT,stdin);
	   	entry[strlen(entry)-1]='\0';
	obj=(product*)malloc(sizeof(product));
	obj->object = strtok(entry," ");
//	obj[i].price =0;
	obj->numberofitems = 1;
	obj->next = NULL;
	obj->subobject = NULL;
	root = obj;
	printf("Define %s?:\n", obj->object);

	price = str(obj,i,i+1);

	printf("Total cost of %s is %.2lf\n",obj->object,price);


 	return 0;
}

double str(struct product *obj,int count,int k){
	int i=0,j=0;
	char *entry;
	char *temp;
	double tempNum,totalPrice=0;
	obj->next=(product*)malloc(sizeof(product));
	obj = obj->subobject;
	obj->next=NULL;
	
	count+=k;
	entry = (char*)malloc(MAXLENGHT*sizeof(char));
//	scanf("%[^\n]s",entry);
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
			obj->next=(product*)malloc(sizeof(product));
			obj = obj->next;
				obj->numberofitems = tempNum;
				obj->object =(char*)malloc(MAXLENGHT*sizeof(char));
				strcpy(obj->object,temp);
		}
		i++;

	}while((temp = strtok(NULL," ")) != 0);

	j=1;
	if(i==1){
		totalPrice = tempNum;
	}
	else{
		while(j<=(i+1)/2){
			printf("Define %s in %s?:\n",obj[count+j-1].object,obj[count-k].object);
			totalPrice+=str(obj,count+j-1,(i+1)/2)*obj[count+j-1].numberofitems;
			j++;
			printf("\n\n%dcount - %d  +++  %dj--->>%s-%s\n\n",count,count-1,j-1,obj[count-1].object,obj[0].object);

		}
	}
	printf("%.2lf\n",totalPrice );
	return totalPrice;
}
