#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void grades(int studentNumber);

int main(){
	int student;
	/*ogrenci sayisi secimi ve aralik kontrolu*/
	printf("enter student count(between 3 - 50) : ");
	scanf("%d",&student);
	
	while(student<3 || student > 50){
		printf("Not in range!!!\n\n");
		printf("enter student count(between 3 - 50) : ");
		scanf("%d",&student);
	}
	/*ogrenci sayisini fonksiyona gonderip isleme sok*/
	grades(student);
	
	return 0;
}

void grades(int studentNumber){
	int i,mostSuc = 0,mostUnsuc = 100,grade,sum=0,menu;
	int gradeA=0,gradeB=0,gradeC=0,gradeD=0,gradeF=0;
	int indexMostSuc,indexMostUnsuc;
	double averageGrade;
	char mostSucLet, mostUnsucLet;
	srand(40);
	
	for(i=0;i<studentNumber;i++){
		grade = rand() % 101;		/*random puan atama ve ekrana basma*/
		printf("%d ",grade);
		
		if(grade > mostSuc){		/*en yuksek puani belirleme ve yerini tayin etme*/
			mostSuc = grade;
			indexMostSuc = i+1;
									/*aldigi nota gore harf atama*/
			if(mostSuc >= 90)
				mostSucLet = 'A';
		
			else if(mostSuc >= 80)
				mostSucLet = 'B';	
		
			else if(mostSuc >= 70)
				mostSucLet = 'C';	
		
			else if(mostSuc >= 60)
				mostSucLet = 'D';
			
			else 
				mostSucLet = 'F';
		}
		else if(grade < mostUnsuc){		/* en dusuk notu belirleme ve yerini tayin etme*/
			mostUnsuc = grade;
			indexMostUnsuc = i+1;		
			
			if(mostUnsuc >= 90)			/*aldigi puana gore harf atama*/
				mostUnsucLet = 'A';
		
			else if(mostUnsuc >= 80)
				mostUnsucLet = 'B';	
		
			else if(mostUnsuc >= 70)
				mostUnsucLet = 'C';	
		
			else if(mostUnsuc >= 60)
				mostUnsucLet = 'D';
			
			else 
				mostUnsucLet = 'F';
		}
		
										/*harf notunu kaç kisi aldi atamasi*/
		if(grade >= 90)
			gradeA++;
		
		else if(grade >= 80)
			gradeB++;	
	
		else if(grade >= 70)
			gradeC++;	
		
		else if(grade >= 60)
			gradeD++;
			
		else 
			gradeF++;	
		
		sum += grade;				/* toplam not degeri tutma*/
	}
	/*toplam notu ogrenci sayisina bolerek ortalama degeri hesaplama*/
	averageGrade = sum / (double)(studentNumber);	
	
	do{

		/*switch case ile ekrana basilacak bilgileri ayarlama*/
		switch(menu){
			case   1: printf("Most Successfully Student\n");
					  printf("Index : %d\nScore : %d\nLetter grade : %c\n\n",indexMostSuc,
					  mostSuc,mostSucLet);
					  
					  break;
	
			case   2: printf("Most Unsuccessfully Student\n");
					  printf("Index : %d\nScore : %d\nLetter grade : %c\n\n",indexMostUnsuc,
					  mostUnsuc,mostUnsucLet);
					  
					  break;
	
			case   3: printf("%d student got letter grade 'A'\n",gradeA);
					  printf("%d student got letter grade 'B'\n",gradeB);
					  printf("%d student got letter grade 'C'\n",gradeC);
					  printf("%d student got letter grade 'D'\n",gradeD);
					  printf("%d student got letter grade 'F'\n\n",gradeF);
					  	
					  break;
	
			case   4: printf("The average score of %d student is %.2lf\n\n",studentNumber,averageGrade);
		
					  break;
	
			case   5: printf("Most Successfully Student\n");
					  printf("Index : %d\nScore : %d\nLetter grade : %c\n\n",indexMostSuc,
					  mostSuc,mostSucLet);
					  
					  printf("Most Unsuccessfully Student\n");
					  printf("Index : %d\nScore : %d\nLetter grade : %c\n\n",indexMostUnsuc,
					  mostUnsuc,mostUnsucLet);
					  
					  printf("%d student got letter grade 'A'\n",gradeA);
					  printf("%d student got letter grade 'B'\n",gradeB);
					  printf("%d student got letter grade 'C'\n",gradeC);
					  printf("%d student got letter grade 'D'\n",gradeD);
					  printf("%d student got letter grade 'F'\n\n",gradeF);
					  
					  printf("The average score of %d student is %.2lf\n\n",studentNumber,averageGrade);
					  
					  break;
		}
		/*menu*/
		printf("\n\n1) Most Successful Student\n2) Most Unsuccessful Student\n");
		printf("3) Letter Grade Statistics\n4) Calculate Average\n5) Show All Data\n\n");
		
		printf("Make selection : ");
		scanf("%d",&menu);
		
						
		if(menu < 1 || menu > 5)
			printf("False Selection\n\n");
	}
	while(menu != -1);	/*kullanici -1 girene kadar dongu devam etsin*/

}


