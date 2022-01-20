#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define SIZEOFINUT 100
typedef struct product
{
	char *object;
	double price;
	double numberofitems;
	struct product *next;
	struct product *subobject;			/**/
}product;

int str(struct product *obj,int items);

int main()
{
	product *obj,*root;
	char *entry;			/*definitions of object or subobject*/	
	int i =0,control = 0,controlFirstStruct = 0,controlNext = 0;
	char *temp;
	double tempNum;


	printf("What the object:\n");
	entry = (char*)malloc(300*sizeof(char));
	gets(entry);

	temp = (char*)malloc(30*sizeof(char));
    temp = strtok(entry," ");
    obj=(product*)malloc(sizeof(product));

	do{
		if(i!=0 && i%2 == 1){
			obj = obj->next;
			obj=(product*)malloc(sizeof(product));
			controlNext = i;
		}
		if(temp[0] >= '0' && temp[0] <= '9'){
			sscanf(temp,"%lf",&tempNum);
			control = 1;
		}
		else if(i%2 == 0){
			if(control == 1){
				obj->numberofitems = tempNum;
				obj->object = (char*)malloc(30*sizeof(char));
				strcpy(obj->object,temp);
			//	obj->object[sizeof(temp)] = '\0';
				control = 0;
			}
			else{
				obj->numberofitems = 1.0;
				obj->object = (char*)malloc(30*sizeof(char));
				strcpy(obj->object,temp);
			//	obj->object[sizeof(temp)] = '\0';
				control = 0;
			}
			printf("%lf -> %s\n",obj->numberofitems, obj->object);
			obj->next = NULL;
		}
		if (controlFirstStruct == 0)
		{
			root = obj;
			controlFirstStruct = 1;
		}
		i++;
	//	temp = strtok(NULL," ");
	//	printf("%s\n",temp );
	}while((temp = strtok(NULL," ")) != 0);

	printf("\n%lf -> %s\n",root->numberofitems,root->object );

 /*   obj=(product*)malloc(sizeof(product));
    obj->price =0;
    temp = (char*)malloc(sizeof(char)*sizeof(entry));
    temp = strtok(entry)
    sscanf(entry,"%lf",&obj->numberofitems);
    while(entry[i] != ' ' && entry[i] != '\0'){
    	i++;
    }
    obj->object = (char*)malloc(sizeof(char)*SIZEOFINUT);
	obj->object = strtok(&entry[i], " ");
 i=0;
	while(obj->object[i] != ' ' && obj->object != '\n'){
    	printf("%c %d", obj->object[i],i);
    	i++;
    }
    printf("\n%s %lf %c\n",obj->object,obj->numberofitems,entry[0]);*/
	return 0;
}