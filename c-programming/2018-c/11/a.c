#include "stdio.h"
#include <stdlib.h>

#include <stdlib.h>

typedef struct customer
{
	int room;
	char surname[20];
	char name[20];
	int age;
	char gender[7];
	struct customer *next;
}node_customer;
typedef struct room
{
	int number;
	int capacity;
	int floor;
	struct room * next;
	struct customer *cust;
}node_room;

int main()
{ 
	node_room *room1,*room2;
	node_customer *customer1,*customer2;
	char line[50],a;
	int i=0;
	FILE *fp_rooms,*fp_customers;

	fp_rooms = fopen("rooms.txt","r");
	fp_customers = fopen("customers.txt","r");

	fgets(line,50,fp_rooms);
	room1 = (node_room*)malloc(sizeof(node_room));
	sscanf(line,"%d%c%d%c%d",&room1->number,&a,&room1->capacity,&a,&room1->floor);	
	room1->next = NULL;
	printf("%d %d %d\n",room1->number,room1->capacity,room1->floor );
	room2 = room1;
	while(fgets(line,50,fp_rooms)){
		room2->next = (node_room*)malloc(sizeof(node_room));
		room2 = room2->next;
		sscanf(line,"%d%c%d%c%d",&room2->number,&a,&room2->capacity,&a,&room2->floor);	
		room2->next = NULL;
		printf("%d %d %d\n",room2->number,room2->capacity,room2->floor );
	}

	fgets(line,50,fp_customers); 
	while(line[i] != '\n'){
		if(line[i] == ',')
			line[i] = ' ';
		i++;
	}
	i=0;
	customer1 = (node_customer*)malloc(sizeof(node_customer));
	sscanf(line,"%d%c%s%c%s%c%d%c%s",&customer1->room,&a,customer1->surname,&a,customer1->name,&a,&customer1->age,&a,customer1->gender);	
	customer1->next = NULL;
	printf("%d %s %s %d %s\n", customer1->room,customer1->name,customer1->surname,customer1->age,customer1->gender);
	customer2 = customer1;
	while(fgets(line,50,fp_customers)){
		while(line[i] != '\n'){
			if(line[i] == ',')
				line[i] = ' ';
			i++;
		}
		i=0;
		customer2->next = (node_customer*)malloc(sizeof(node_customer));
		customer2 = customer2->next;
		sscanf(line,"%d%c%s%c%s%c%d%c%s",&customer2->room,&a,customer2->surname,&a,customer2->name,&a,&customer2->age,&a,customer2->gender);	
		customer2->next = NULL;
			printf("%d %s %s %d %s\n", customer2->room,customer2->name,customer2->surname,customer2->age,customer2->gender);

	}
	room1->cust = customer1;

	printf("%s\n",room1->cust->name);


	fclose(fp_rooms);
	fclose(fp_customers);


	return 0;
}