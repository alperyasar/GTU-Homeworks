#include <stdio.h>

typedef enum{MIN, MAX, SUM} operation;

int arrOp(int *arr, int size, operation op);

int main(){
	int array[] = {1,2,3,4,5,6,7,-99,200}, size = 0;
	
	printf("%d\n",arrOp(array, size, MAX));
	printf("%d\n",arrOp(array, size, MIN));
	printf("%d\n",arrOp(array, size, SUM));
	return 0;
}
int arrOp(int *arr, int size, operation op){

	int i,j,temp, toplam = 0;
	
	if(size < 1)
		return -34566;	
	
	switch(op)
	{
		case MIN:
			for(i = 0; i < size; ++i)
			{
				for(j = 1; j < size; ++j)
				{
					if(arr[i] > arr[j])
					{
						temp = arr[i];
						arr[i] = arr[j];
						arr[j] = temp;
					}
				}
				
			}
			return arr[0]; break;
			
		case MAX:
			for(i = 0; i < size; ++i)
			{
				for(j = 1; j < size; ++j)
				{
					if(arr[i] < arr[j])
					{
						temp = arr[i];
						arr[i] = arr[j];
						arr[j] = temp;
					}
				}
				
			}
			return arr[0]; break;
		
		case SUM:
			for(i = 0; i < size; ++i)
				toplam += arr[i];
			return toplam; break;
			
		default:
			return -1002; break;
			
	}
	return 0;
}
