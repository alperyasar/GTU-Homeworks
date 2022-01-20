#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
char* find_operations(int arr[], int expected_val, char operations[], size_t arr_len, int cursor, int current){
	char operator = {'+','-','*'};
	if(current == expected_val)
		return operations;
	else{
		if(arr_len == cursor){
			current = arr[];
			find_operations(arr,expected_val,operations,arr_len,cursor,current)
		}
		else if()

	}
}



int main()
{
	size_t arr_len;
	int n,arr[arr_len],expected_val;
	int cursor=0, current=0,i;
	char operations[arr_len-1];

	srand(time(NULL));

	printf("enter size of array :");
	scanf("%d",&n);

	for (i = 0; i < n; ++i)
	{
		printf("enter numbers %d :",i+1);
		scanf("%d",&arr[i]);
	}
	arr_len = sizeof arr;

	printf("expected value :");
	scanf("%d",expected_val)
	for (int i = 0; i < arr_len-1; ++i)
	{
		operations[i] = ' ';
	}

	
//	operations[]


	return 0;
}