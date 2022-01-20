#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct prime_numb{
	int numb;
	struct prime_numb * next;
}node;

//double prime1(int size);
double prime2(int size);

int main()
{
	clock_t begin=clock();

//	FILE *outp1;
	FILE *outp2;

//	outp1 = fopen("output_prime_LiknedList.txt","w");	
	outp2 = fopen("output_prime_dynamic_array.txt","w");	

//	fprintf(outp1,"%.0lf\n", prime21(500000));
	fprintf(outp2,"%.0lf\n", prime2(500000));
/*
	fprintf(outp1,"%.0lf\n", prime1(750000));
	fprintf(outp2,"%.0lf\n", prime2(750000));

	fprintf(outp1,"%.0lf\n", prime1(1000000));
	fprintf(outp2,"%.0lf\n", prime2(1000000));*/


//	fclose(outp1);
	fclose(outp2);

	clock_t end = clock();
	printf("%.0lf",(end - begin)*1000.0 / CLOCKS_PER_SEC);

	return 0;
}	
/*
double prime1(int size){
	clock_t begin=clock();
	node *root;
	node *iter;
	double a;
	int i=0,flag=0;
	char line[100];
	FILE * inp;

	printf("a");

	inp = fopen("data.txt","r");
	
	fgets(line,100,inp);
	if(1==sscanf(line,"%lf",&a)){  	
		root = (node*)malloc(sizeof(node));
		root->numb = (int)a;
 		root->next = NULL;
 		i++;
 	}
 	iter = root;
	while(i<=size){
		fgets(line,100,inp);
		if(1==sscanf(line,"%lf",&a)){  	
			iter->next = (node*)malloc(sizeof(node));
			iter = iter->next;
			iter->numb = (int)a;
	 		iter->next = NULL;
	 	}
	}
	iter = root;					
	while(iter ->next != NULL){
		if(iter->numb == 1){
			iter = iter ->next;
		}
		else if(iter->numb == 2){
			printf("%d\n", iter->numb);
			iter = iter->next;
		}

		else{
			for(i=2;i<=iter->numb/2;i++){
				if(iter->numb%i == 0){
					flag = 1;
				}
			}
			if(flag == 0){
				printf("%d\n", iter->numb);
				iter = iter->next;
			}
			else{
				iter = iter->next;
				flag =0;
			}
		}	

	}
	
	free(root);

	fclose(inp);

	clock_t end = clock();
	return (end - begin)*1000.0 / CLOCKS_PER_SEC;
}
*/
double prime2(int size){
	clock_t begin=clock();
	double a;
	int *arr,count = 0,j,i,flag=0;
	char line[100];
	FILE * inp;

	inp = fopen("data.txt","r");

	arr = (int*)malloc(size*sizeof(int));

	fgets(line,100,inp);
	if(1==sscanf(line,"%lf",&a)){  	
		arr[count] = (int)a;
		count++;
 	}

	while(count <=size){
		fgets(line,100,inp);
		if(1==sscanf(line,"%lf",&a)){  	
			arr[count] = (int)a;
			count++;
	 	}
	}
	i=0;
	while(i<count){
		if(arr[i] == 1){

		}

		else if(arr[i] == 2){
			printf("%d\n", arr[i]);
		}

		else{
			for(j=2;j<=arr[i]/2;j++){
				if(arr[i]%j == 0){
					flag = 1;
				}
			}
			if(flag == 0){
				printf("%d\n", arr[i]);
			}
			else{
				flag =0;
			}
		}
		i++;	

	}
	free(arr);
		


	fclose(inp);

	clock_t end = clock();
	return (end - begin)*1000.0 / CLOCKS_PER_SEC;

}
