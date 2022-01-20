#include <stdio.h>

int main(){
	int occur=0,bigNumb,searchNumb,bigControl,searchControl,loopBigControl;
	int bigNumbElse,searchNumbElse,loopSearchControl,searchTemp;

	do{
		printf("please enter the big number : ");
		scanf("%d",&bigNumb);
		printf("please enter the search number : ");
		scanf("%d",&searchNumb);
	
	}while(bigNumb <= searchNumb);
	
	printf("Big Number : %d\nSearch Number : %d\n",bigNumb,searchNumb);
	
	searchTemp = searchNumb;
	
	while(bigNumb != 0){
		searchControl = searchNumb % 10;
		bigControl = bigNumb % 10;

		bigNumb /= 10;
		searchNumb /= 10;
		
		if(searchNumb == 0 && searchControl == bigControl){
			occur++;
		}
		else if(searchNumb > 0 && bigNumb > 0 && searchControl == bigControl){
			searchNumbElse = searchNumb;
			bigNumbElse = bigNumb;
			
			loopBigControl = bigNumbElse % 10;
			loopSearchControl = searchNumbElse % 10;
			
			while(loopSearchControl == loopBigControl){
				bigNumbElse /= 10;
				searchNumbElse /= 10;
				
				loopBigControl = bigNumbElse % 10;
				loopSearchControl = searchNumbElse % 10;
				
				if(searchNumbElse == 0){
					occur++;
					loopSearchControl = loopBigControl + 1;
				}
				

			
			}	
		}
		searchNumb = searchTemp;
	}
	printf("Occurence : %d\n\n",occur);
	
	return 0;
}


