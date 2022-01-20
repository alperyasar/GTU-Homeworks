#include <stdio.h>

void alphabeticalSort(char *arr, int size);

int main(){
	int i;
	char arr[] = {'m','e','r','h','a','b','a','A','l','i'};
	alphabeticalSort(arr,10);
	for(i = 0; i < 10; ++i)
		printf("%c",arr[i]);
	printf("\n");

	return 0;
}
void alphabeticalSort(char *arr, int size){
	int i,j,temp;

	for(i = 0; i < size; ++i){
		for(j = 0; j < size - 1; ++j){

			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
