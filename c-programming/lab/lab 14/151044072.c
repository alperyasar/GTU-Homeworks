#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int val;
	struct node * next;
}node_t;



void delete_numb(node_t * root, int number){
	node_t * iter,*iter2,*root2;
	int i =0;
	iter = root;

	printf("Output : ");
	while(iter->next != NULL){
		if(iter->val <= number){
			if(i==0){
				root2 = (node_t*)malloc(sizeof(node_t));
				root2->val = root->val;
				root2->next = NULL;
				iter2 = root2;
				printf("%d", iter->val);
				i++;
				iter=iter->next;	
			}
			else{
				iter2->next = (node_t*)malloc(sizeof(node_t));
				iter2 = iter2->next;
				iter2->val=iter->val;
				iter2->next = NULL;
				printf("->%d", iter->val);
				iter=iter->next;
			}
		}
		else{
			iter = iter->next;
		}
	}
	if(iter->val <= number){
		iter2->next = (node_t*)malloc(sizeof(node_t));
		iter2 = iter2->next;
		iter2->val=iter->val;
		iter2->next = NULL;
		printf("->%d\n",iter->val);
	}
	else
		printf("\n");

	while(root2->next != NULL){
		printf("%d\n",root2->val);
		root2 = root2->next;
	}
	printf("%d\n",root2->val);

	free(root);
	free(iter);
	free(iter2);


}



int main()
{
	node_t *root;
	node_t *iter;
	int i=0,number;
	srand(time(NULL));

	printf("Input : list: ");
	root = (node_t*)malloc(sizeof(node_t));					
	root->val = (rand() % 9) +1;	
	printf("%d", root->val);						
	root->next = NULL;									
	i++;

	iter = root;
	while(i<6){
		iter->next = (node_t*)malloc(sizeof(node_t));
		iter = iter->next;							
		iter->val = (rand() % 9) +1;
		printf("->%d", iter->val);						
	 	iter->next = NULL;
	 	i++;
	}
	printf("\n\t x = ");
	scanf("%d",&number);

	delete_numb(root,number);

	free(root);

	
	return 0;
}