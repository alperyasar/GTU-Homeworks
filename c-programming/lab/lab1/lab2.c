#include <stdio.h>

double mean();

int main(){
	double ort;
	ort = mean();
	printf("%lf\n",ort);

	return 0;
}	
	double mean(){
		double sayi,toplam,size,ort;
		toplam=0;
		size=0;
		scanf("%lf",&sayi);
		
		while(sayi >= 0){
			++size;
			toplam += sayi;
			scanf("%lf",&sayi);
			
		}
		ort = toplam / size;
		return ort;
	
	}
