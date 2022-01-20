#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu();
int getint(int mini,int maxi);
int numberGeneratorBetweenRange(int mini,int maxi);
void horseRacingRace();
void countOccurence();
void triangleOfSequences();

int main(){
	
	menu();
	
	return(0);
}

/*menu*/

void menu(){
	int men;			/*menu*/
	
	
	
	do{
		printf("1) Horse racing game\n");
		printf("2) Occurence counter\n");
		printf("3) Triangle of sequences\n");
		printf("0) Exit\n");
	
		men = getint(0,3);
	
		switch(men){
			case 1:	horseRacingRace();
					break;
					 
			case 2:	countOccurence();
					break;
					
			case 3: triangleOfSequences();
					break;
		
		}
	}
	while(men != 0);

}

/*menu degeri*/
/*kullanicidan sayi alacak ve bu sayinin menu icinde olup olmadigini kontrol eder*/ 

int getint(int mini,int maxi){
	int chooseNumber;
	
	do{
		printf("\nEnter the number (between %d - %d)",mini,maxi);
		scanf("%d",&chooseNumber);
	}
	while(chooseNumber < mini || chooseNumber > maxi);
	
	return chooseNumber;
	
}
/*maxi degerinden mini degerini cikarip rastgele sayi alacak*/

int numberGeneratorBetweenRange(int mini,int maxi){
	int randomNumber,result;
	
	srand(time(NULL));
						/*random degerleri maxi ve mini modu'nu alip birbirinden
						  cikarip istenilen deger arasindaki sayiyi hesaplama*/
	result = maxi - mini;
	randomNumber = rand() % (result+1);
	randomNumber += mini;
	
	return randomNumber;
}
/*At yarisi*/

void horseRacingRace(){
	int numberOfHorse,j,i=1,horse;
	int chooseHorse,temp=20,result,winnerHorse;			/*temp'i at kosu mesafeleri olarak atacagım
										  				  en az sureyi belirmelemek icinde baslangic
										  				  olarak temp'i 20 aldim  */
	srand(time(NULL));
	
	numberOfHorse = numberGeneratorBetweenRange(3,5);

	printf("\nplease choose horse (between 1-%d)",numberOfHorse);
	chooseHorse = getint(1,numberOfHorse);
	
	
	while(i <= numberOfHorse){
		horse = (rand() % 10) + 10;		/*horse degerini numberGeneratorBetweenRange*/
										/*fonksiyonundan alamiyorum cunku dongu icinde*/
		printf("Horse %d : ",i);		/*ayni degeri basiyor bu yuzden yeniden random*/
		for(j=0;j<horse;j++){			/*degeri atiyorum*/
			printf("-");
		}
		printf("\n");
		
		if(horse < temp){
			temp = horse;
			result = 1;					/*result 1 ise kazanan var 2 ise beraberlik*/
			winnerHorse = i;
		}
		else if(horse == temp){			
			result = 2;
		}		
		i++;
	}
	if(result == 1){
		if(chooseHorse == winnerHorse)
			printf("\nYou win!!!\n\n");
		else
			printf("\nYou lose! Winner is horse %d.\n\n",winnerHorse); 
	}
	else if(result == 2)
		printf("\nNo winner!\n\n");
	


}
/*kullanicidan bir iki sayi alacak ve buyuk sayi icinde kucuk sayiyi arayacak*/
void countOccurence(){
	int occur=0,bigNumb,searchNumb,bigControl,searchControl,loopBigControl;
	int bigNumbElse,searchNumbElse,loopSearchControl,searchTemp;

	do{
		printf("please enter the big number : ");			/*do while icinde bigNumber degerinini*/
		scanf("%d",&bigNumb);								/*searchNumber degerinden daha buyuk olup */
		printf("please enter the search number : ");		/*olmadigini kontrol ediyor*/
		scanf("%d",&searchNumb);
	
	}while(bigNumb <= searchNumb);
	
	printf("Big Number : %d\nSearch Number : %d\n",bigNumb,searchNumb);
	
	searchTemp = searchNumb;		/*searchTemp'i while döngüsüne tekrar searchNumb 
									  degerini atamak icin tutuyoruz cunku iceride 
									  searchNumb degeri degisiyor*/
	
	while(bigNumb != 0){
		searchControl = searchNumb % 10;	/*modları alıp kontrol yapiyoruz*/
		bigControl = bigNumb % 10;				

		bigNumb /= 10;						/*ve sondan 1 basamak cikarioruz*/
		searchNumb /= 10;
		
		if(searchNumb == 0 && searchControl == bigControl){	/*search degeri tek basamak ise */
			occur++;										/*bu if'te buluyoruz*/
		}													
		
															/*searchNumb basamak sayisi 1'den fazla ise
															  searchNumb ve bigNumb'ın basamak azaltiginda
															  0 olmadigini kontrol edip iceride search ediyoruz*/
		else if(searchNumb > 0 && bigNumb > 0 && searchControl == bigControl){
			searchNumbElse = searchNumb;					/*searchNumb ve bigNumb degeri dongu icinde bozulmasin*/
			bigNumbElse = bigNumb;							/*diye farkli degeri atiyoruz*/
			
			loopBigControl = bigNumbElse % 10;				/*modu alip yeni degiskenler ile kontrol ediyoruz*/
			loopSearchControl = searchNumbElse % 10;		
			
			while(loopSearchControl == loopBigControl){
				bigNumbElse /= 10;
				searchNumbElse /= 10;
				
				loopBigControl = bigNumbElse % 10;
				loopSearchControl = searchNumbElse % 10;
				
				if(searchNumbElse == 0){						/*eger search basamagi bittiyse ve kontroller*/
					occur++;									/*uyuyorsa occur degerini arttırıyoruz*/
					loopSearchControl = loopBigControl + 1;		/*tekrar donguye sokmamak icin controlleri esitlikten*/
				}												/*cikariyoruz*/
			}	
		}
		searchNumb = searchTemp;
	}
	printf("Occurence : %d\n\n",occur);

}
/*2 ile 10 arasinda rastgele sayi uretecek ve katlari seklinde ucgen olustaracak*/

void triangleOfSequences(){
	int i,j,ucgen;
	
	for(i=1;i<numberGeneratorBetweenRange(2,10)+1;i++){
		for(j=1;j<=i;j++){								/*i = kacinci sira*/
			printf("%d ",j*i);							/*i*j = yazilacak rakamın carpimi*/				
		}
		printf("\n");
	}
	printf("\n");
}






