#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct prime_numb{							/*linked list icin struct*/
	int numb;
	struct prime_numb * next;
}node;

double prime1(int size);
double prime2(int size);

int main()
{
	clock_t begin=clock();

	FILE *outp1;											/*2 tane yazma dosyası*/
	FILE *outp2;

	outp1 = fopen("output_prime_LiknedList.txt","w");	
	outp2 = fopen("output_prime_dynamic_array.txt","w");	

	fprintf(outp1,"1) Between 1 and 500.000 : %.0lf\n", prime1(500000));				/*sirasiyla 500 bin 750 bin ve 1 milyon'a kadar olan */
	fprintf(outp2,"1) Between 1 and 500.000 : %.0lf\n", prime2(500000));				/*degerler prime1 ve prime2 fonksiyonlarina gonderiliyor*/ 

	fprintf(outp1,"2) Between 1 and 750.000 : %.0lf\n", prime1(750000));				/*fonksiyonlarda return edilen degerler dosyalara yazdirilir*/
	fprintf(outp2,"2) Between 1 and 750.000 : %.0lf\n", prime2(750000));

	fprintf(outp1,"3) Between 1 and 1.000.000 : %.0lf\n", prime1(1000000));
	fprintf(outp2,"3) Between 1 and 1.000.000 : %.0lf\n", prime2(1000000));

																			/*dosyalari kapat*/
	fclose(outp1);
	fclose(outp2);

	clock_t end = clock();													/*toplam gecen sureyi ekrana bastir*/
	printf("\n\nThe file written time : %.0lf\n",(end - begin)*1000.0 / CLOCKS_PER_SEC);

	return 0;
}

double prime1(int size){
	clock_t begin=clock();									/*gecen sureyi gormek icin baslangıc*/
	node *root;												/*2 adet pointer struct olarak tanımlı*/
	node *iter;
	double a;
	int i=0,flag=0;											/*flag : bir sayının herhangi bir sayiya tam bolunup */
	char line[100];			/*okunan satırlar*/	            /*bolunmedigini kontrol etmek icin*/
	FILE * inp;				/*dosya okumak icin pointer*/									

	printf("a");
	inp = fopen("data.txt","r");					/*dosya okuma*/			
	
	fgets(line,100,inp);
	sscanf(line,"%lf",&a);								/*ilk satırı okuyup eger var ise double tanımlı a degerine atar*/
	root = (node*)malloc(sizeof(node));					/*root icin bir node boyutunda yer ayırır*/
	root->numb = (int)a;								/*double a degerini integer olarak root'a atar*/
	root->next = NULL;									/*bir sonraki degere '/0' karakteri atılır*/
	i++;
	

 	iter = root;										/*root ilk degeri gostermesi icin iter adlı yeni pointer'a atadik*/
	while(i<size){										/*iter baglı olan diger memorylerde gezinir ve root ilk degeri gostemeye devam eder*/
		fgets(line,100,inp);
		if(1==sscanf(line,"%lf",&a)){  					/*boylece ilk degeri korumus oluruz ve sonrasına iter ile baglamis oluruz*/
			iter->next = (node*)malloc(sizeof(node));
			iter = iter->next;							/*ve dongu icinde main fonksiyonunda belirlenen degere kadar*/
			iter->numb = (int)a;						/*dosyadan okuyup, yer ayırır ve linked list ile sıralar*/
	 		iter->next = NULL;
	 	}
	 	i++;
	}
	iter = root;
	while(iter ->next != NULL){							/*en sondaki kutu null degeri olarak atama yaptiydik ve*/
		if(iter->numb == 1){							/*burada NULL karakterini gorene kadar next ile kontrol yapiyoruz*/
			iter = iter ->next;
		}
		else if(iter->numb == 2){						/*iter->numb 2 ise asal deger olarak atiyoruz*/
			printf("%d\n", iter->numb);
			iter = iter->next;
		}

		else{
			for(i=2;i<=iter->numb/2;i++){				/*diger asal sayilari bolunup bolunemedigine gore asallik konrolu yapiyoruz*/
				if(iter->numb%i == 0){
					flag = 1;
				}
			}
			if(flag == 0){								/*eger bolen yoksa flag = 0 degeri kalir o deger ekrana asal diye yazdirilir*/
				printf("%d\n", iter->numb);				/*fakat bolen varsa ise flag'e 1 degeri atanir ve bir sonraki deger iter'e atanir*/
				iter = iter->next;
			}
			else{
				iter = iter->next;
				flag =0;
			}
		}	

	}
	
	free(root);											/*memory'de ayrilan alanlar temizlenir*/
	free(iter);

	fclose(inp);										/*dosyayi kapat*/

	clock_t end = clock();								/*gecen sureyi hesaplamak icin son zaman bakilir*/
	return (end - begin)*1000.0 / CLOCKS_PER_SEC;		/*aradaki toplam deger milisaniye cinsinden return edilir*/
}

double prime2(int size){
	clock_t begin=clock();								/*gecen sureyi gormek icin baslangıc*/
	double a;
	int *arr,j,i=0,flag=0;						/*flag : bir sayının herhangi bir sayiya tam bolunup */
	char line[100];										/*line satiri okumak icin*/
	FILE * inp;

	inp = fopen("data.txt","r");					/*dosya okuma*/

	arr = (int*)malloc(size*sizeof(int));			/*main'den gonderilen sayi kadar hafizada yer ayrilir*/


	while(i < size){								/*her bir array'a dosyadana degerler double olarak okunur */
		fgets(line,100,inp);						/*ve integer olarak atanir*/
		if(1==sscanf(line,"%lf",&a)){  	
			arr[i] = (int)a;
			i++;
	 	}
	}
	i=0;
	while(i<size){									/*tum degerler kontrol edilir*/
		if(arr[i] == 1){ }

		else if(arr[i] == 2){						/*2 degeri asal sayi olarak yazdirilir*/
			printf("%d\n", arr[i]);
		}

		else{										/*diger degerler boleni varsa flag'a 1 atanir yapilmaz */
			for(j=2;j<=arr[i]/2;j++){				/*yoksa flag 0 olarak kalir */
				if(arr[i]%j == 0)
					flag = 1;
				
			}
			if(flag == 0)							/*flag 0 iken asaldir*/
				printf("%d\n", arr[i]);				/*ekrana yazdirir*/
			
			else
				flag =0;							/*aksi halde flag 0 atamasi bir sonraki kontrol icin atanir*/
			
		}
		i++;	

	}
	free(arr);										/*memory temizle*/

	fclose(inp);									/*dosyayi kapat*/

	clock_t end = clock();							/*gecen sureyi hesapla ve return et*/
	return (end - begin)*1000.0 / CLOCKS_PER_SEC;

}

