#include <stdio.h>

typedef enum{MIN, MAX, SUM} operation;
int arrOp(int *arr, int size, operation op);

int main(){
	int array[] = {1,2,3,4,5,6,7,-99,200}, size = 9;
	printf("%d",arrOp(array, size, max));
	printf("%d",arrOp(array, size, min));
	printf("%d",arrOp(array, size, sum));
	return 0;
}
int arrOp(int *arr, int size, operation op){

	int i,j,temp,max,min,sum,toplam;
	
	for(i = 0; i < size - 1; ++i){

		for(j = 0; j < size - 1; ++j){

			if(arr[j] > arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		toplam = arr[j];
		
		}		
	}
	sum = toplam / size;
}
