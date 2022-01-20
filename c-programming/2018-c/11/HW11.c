#include <stdio.h>
#include <stdlib.h>

typedef struct customer
{
	int room;
	char surname[10];
	char name[10];
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




void add_room_to_end(node_room *room); 										//The function add a room to the end of the room list.
void add_room_after_room_number (node_room * room,int numb);  				//The function add a room to after the given room number. If the given room does not exists, add it to the end of the list.
void add_customer_to_end(node_customer *customer); 							//The function add a customer to the end of the partial customer list.
void link_customers_to_room(node_room *room, node_customer *customer);	 	//The function adds partial customer list to a room.
node_room * remove_room (node_room* room,int numb);								//The function removes the room indicated by the room number.
void show_vacancy(node_room *room);			 								//The function list all available rooms that don’t have any customer.
void get_by_floor(node_room * room, int floor);		 						//The function lists the rooms with the given floor number.
void print_list (node_room *room);  										//The function prints the room list with customers as shown below:

int main(){
	node_room *room1,*room2;
	node_room sira1,sira2;
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
	fclose(fp_rooms);
	fclose(fp_customers);


	return 0;
}


void add_room_to_end(node_room *room){					 //The function add a room to the end of the room list.
	node_room * iter;

	iter = room;

	while(iter->next != NULL){
		iter = iter->next;
	}
	iter->next = (node_room*)malloc(sizeof(node_room));
	printf("room Number : ");
	scanf("%d",&iter->number);

	printf("room Number : ");
	scanf("%d",&iter->capacity);
	printf("room Number : ");
	scanf("%d",&iter->floor);

	iter->next = NULL;
}
void add_room_after_room_number (node_room * room,int numb){      //The function add a room to after the given room number. If the given room does not exists, add it to the end of the list.
	node_room * iter,*temp1,*temp2;
	int a=0;


	printf("which number to add room : \n");
	scanf("%d",&numb);

	temp1 = (node_room*)malloc(sizeof(node_room));

	printf("room Number : ");
	scanf("%d",&temp1->number);

	printf("room Number : ");
	scanf("%d",&temp1->capacity);
	
	printf("room Number : ");
	scanf("%d",&temp1->floor);
	temp1->next = NULL;

	iter = room;

	while(iter->next != NULL){
		if(iter->number == numb){
			temp2 = iter->next;
			iter->next = temp1;
			iter = iter->next;
			iter->next = temp2;
			a++;
		}
		iter = iter->next;
	}
	if(a==0){
		iter->next=temp1;
	}


}
void add_customer_to_end(node_customer *customer){ 			 //The function add a customer to the end of the partial customer list.
	node_customer * iter;

	iter = customer;

	while(iter->next != NULL){
		iter = iter->next;
	}
	iter->next = (node_customer*)malloc(sizeof(node_customer));
	printf("room Number : ");
	scanf("%d",&iter->room);

	printf("customer surname : ");
	scanf("%s",iter->surname);
	
	printf("customer name : ");
	scanf("%s",iter->name);

	printf("customer age : ");
	scanf("%d",&customer->age);

	printf("customer gender");
	scanf("%s",customer->gender);
	iter->next = NULL;

}
void link_customers_to_room(node_room* room, node_customer *customer){	  	     //The function adds partial customer list to a room.
	node_room *room1=room,*temp;
	node_customer *customer1;

	while(room1->next != NULL){
		customer1=customer;
		while(customer1->next != NULL){
			if(customer1->room == room1->number){
				room->cust = customer1;
				room->cust->next = NULL; 
			}	
		}

	}



}
node_room * remove_room (node_room* room,int numb){					 //The function removes the room indicated by the room number.
	node_room * iter,*temp1;

	iter = room;
	if(iter->number == numb){
		temp1 = room;
		room = iter->next;
		free(temp1);
	}
	else{
		while(iter->next->number != numb){
			iter = iter->next;
		}
		temp1 = iter->next;
		iter->next = iter->next->next;
		free(temp1);
	}
	return room;

}
void show_vacancy(node_room *room){ 					 //The function list all available rooms that don’t have any customer.
 

}
void get_by_floor(node_room * room, int floor){		 			 //The function lists the rooms with the given floor number.


}
void print_list (node_room *room){




}  