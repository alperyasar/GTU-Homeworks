#include <stdio.h>
#include <stdlib.h>

typedef struct Dynamic_array
{
	int *arr1;
	int limit;
	int current_size;

}Dyn_arr;

void init(Dyn_arr *arr){
	int i=0;

	
	arr->limit = 5;
	arr->current_size = 0;
	

	while(arr->current_size < arr->limit){
		arr->arr1 =(int *) malloc(sizeof(int));
		arr->arr1[arr->current_size] = 0;
		arr->current_size++;
	}



}

void add_to_last(Dyn_arr *arr,int input_value){
	int i=0,j=0,flag=0;
	Dyn_arr *temp;
	while(i<5 && flag == 0){
		if(arr->arr1[i] == 0){
			
			arr->arr1[i] = input_value;
			printf("%d\n", arr->arr1[i]);
			flag = 1;
		}
		i++;
	}
	temp = arr;
	if(flag == 0){
		init(temp);
	}
	i=0;
	while(i<5 && flag == 0){
		if(temp->arr1[i] == 0){
			temp->arr1[i] = input_value;
			printf("%d\n", temp->arr1[i]);
			flag = 1;
		}
		i++;
	}

}

void insert_after(Dyn_arr *arr, int index, int input_value){
	Dyn_arr *temp;
	int temp_ind,flag=0,i=0;


	printf("\n\n");
	while(i<5 && flag == 0){
		if(arr->arr1[i] == 0){
			flag = 1;
		}
		i++;
	}
	if(flag = 1){
		while(index < 4){
			arr->arr1[index+1] = input_value;
			printf("%d\n",arr->arr1[index+1]); 
			index++;
		}
	}
	if(flag == 0){
		init(temp);
	}
	i=0;
	while(i<5 && flag == 0){
		if(temp->arr1[i] == 0){
			temp->arr1[i] = input_value;
			printf("%d\n", temp->arr1[i]);
			flag = 1;
		}
		i++;
	}

}

int main(){
	Dyn_arr *arr;
	Dyn_arr *temp;

	arr=(Dyn_arr*) malloc (sizeof(Dyn_arr));
	init(arr);

	temp = arr;
	add_to_last(temp,1);
	add_to_last(temp,2);
	add_to_last(temp,3);
	add_to_last(temp,4);
	add_to_last(temp,5);
	add_to_last(temp,6);


	insert_after(arr,1,1);
	insert_after(arr,0,2);
	insert_after(arr,1,3);
	insert_after(arr,1,4);
	insert_after(arr,1,5);
	return 0;
}