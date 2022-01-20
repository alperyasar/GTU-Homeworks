#include <stdio.h>

void digitNumber(int number);

int main(){
	int number;
	
	/*girilecek deger araligi belirleme*/
	printf("Enter the number(between 23-98760) : ");
	scanf("%d",&number);
	
	while(number < 23 || number > 98760){
		
		printf("Please enter the number(between 23-98760) : ");
		scanf("%d",&number);
	}
	
	printf("\n");		/*bir satir bolsuk birak ve sayiyi digitNumber foksiyonu icinde isleme sok*/
	digitNumber(number);
	
	return 0;
}

void digitNumber(int number){
	int bolen;
	
	if(number >= 10000){			/*eger sayi 10000'den buyuk ise atama yap*/
		bolen = number / 10000;
		printf("the fifth digit is  %d\n",bolen);		/*once 10000'e bolup boleni 5. basamak olarak ata*/
		number = number - (bolen * 10000);				/*kalani bulmak icin boleni 10000 ile carpıp sayıda cikar*/
														/*kalani yeni sayiya ata ve 4. basamagi bulmaya gec*/
		bolen = number / 1000;				
		printf("the fourth digit is %d\n",bolen);		/*yani boleni bulup her bir islemde basamak olarak ekrana yazdir*/
		number = number - (bolen * 1000); 				/*sonra basamagı bulundugu 10'un katı seklinde carpip sayıdan cıkar*/
														/*boylelikle bir sonraki basamak islemine gec*/
		bolen = number / 100;
		printf("the third digit is  %d\n",bolen);
		number = number - (bolen * 100); 
	
		bolen = number / 10;
		printf("the second digit is %d\n",bolen);
		number = number - (bolen * 10); 

		printf("the first digit is  %d\n",number);

	}													/*sayinin 1000'den buyuk olup olmadıgına bak*/
	else if(number >= 1000){
		bolen = number / 1000;
		printf("the fourth digit is %d\n",bolen);
		number = number - (bolen * 1000); 

		bolen = number / 100;
		printf("the third digit is  %d\n",bolen);
		number = number - (bolen * 100); 

		bolen = number / 10;
		printf("the second digit is %d\n",bolen);
		number = number - (bolen * 10); 

		printf("the first digit is  %d\n",number);

	}													/*sayinin 100'den buyuk olup olmadıgına bak*/
	else if(number >= 100){
		bolen = number / 100;
		printf("the third digit is  %d\n",bolen);
		number = number - (bolen * 100); 

		bolen = number / 10;
		printf("the second digit is %d\n",bolen);
		number = number - (bolen * 10); 

		printf("the first digit is  %d\n",number);

	}													/*sayi cift haneli ise yap*/
	else{
		bolen = number / 10;
		printf("the second digit is %d\n",bolen);
		number = number - (bolen * 10); 

		printf("the first digit is  %d\n",number);

	}		
}
