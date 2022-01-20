#include <stdio.h>

int days(char start_date[], char end_date[], FILE *inp);
void calendar();

int main(){
	FILE *inp;
	char start_date[10], end_date[10];

	inp = fopen("input_data.txt","w");			/*write to file*/
	
	printf("start date : ");					/*başlangıç tarihi kullanıcı girer*/
	scanf("%s",start_date);
	
	printf("end date : ");						/*bitiş tarihi kullanıcı girer*/
	scanf("%s",end_date);
	
	days(start_date,end_date,inp);				/*29/04/2018 şeklinde tarih basıyor*/
	
	fclose(inp);								
//	calendar();									/*aynı anda 2 fonksiyonda çalışmıyor*/
												/*çünkü aynı txt dosyalarını kullanıyorlar*/
	return 0;
}

int days(char start_date[], char end_date[], FILE *inp){
	int i,j=0,day,month,year;						
	
	fprintf(inp,"%s\n",start_date);			/*fonksiyon her tekrar ettiğinde dosyaya yazdırıyor*/
	
	for(i=0;i<10;i++){						/*başlangıç tarihi bitiş tarihine eşit*/
		if(start_date[i] == end_date[i])	/*olduğu zaman return 0 değerini gönder*/
			j++;							/*fonksiyondan çık*/
	}
	if(j == 10)
		return 0;
										/*gün, ay ve yıl değerlerini atama yapıyor*/
	day   = ((start_date[0] - '0') * 10) + (start_date[1] - '0');			
	month = ((start_date[3] - '0') * 10) + (start_date[4] - '0');
	year  = ((start_date[6] - '0') * 1000) + ((start_date[7] - '0')*100) + ((start_date[8] - '0') * 10) + (start_date[9] - '0');
	
	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
	    if(day < 31)						/*31 gün olan ayları kontrol edip*/
			day++;							/*günü ayın son günü olmasu durumuna göre atama yapıyor*/
		else if(day == 31){
			day = 1;
			if(month == 12){				/*son ayın son günü olduğu zaman yeni yıla geçiyor*/
				month = 1;
				year++;
			}
			else
				month++;
		}
				
		start_date[1] = (day % 10) + '0';				/*dosyaya yazdırmak için gün ay ve yılı eski*/
		start_date[0] = (day / 10) + '0'; 				/*haline çeviriyor*/
		
		start_date[4] = (month % 10) + '0';
		start_date[3] = (month / 10) + '0';
		
		start_date[9] = (year % 10) + '0';
		year /= 10;
		start_date[8] = (year % 10) + '0';
		year /= 10;
		start_date[7] = (year % 10) + '0';
		year /= 10;
		start_date[6] = year + '0';		 
		return 	days(start_date,end_date,inp);			/*fonksiyonu tekrar çağırıyor*/
	}
	else if(month == 4 || month == 6 || month == 9 || month == 11){
		if(day < 30)									/*30 gün çeken ayları kontrol ediyor*/
			day++;										/*ve üst taraftaki aynı işleri yapıp*/
		else if(day == 30){								/*fonksiyonu tekrar çağırıyor*/
			day = 1;
			month++;
		}
		start_date[1] = (day % 10) + '0';
		start_date[0] = (day / 10) + '0';
		
		start_date[4] = (month % 10) + '0';
		start_date[3] = (month / 10) + '0';
		
		start_date[9] = (year % 10) + '0';
		year /= 10;
		start_date[8] = (year % 10) + '0';
		year /= 10;
		start_date[7] = (year % 10) + '0';
		year /= 10;
		start_date[6] = year + '0';
		return 	days(start_date,end_date,inp);	
	}
	
	else if(month == 2){
		if(year % 4 == 0 && day == 29){				/*şubat ayı kontrolü*/
			day = 1;			
			month++;								/*her 4 yılda bir artık yıl olduğu için*/
		}											/*burada o kontrolü yapıp tekrardan yukarıdaki işlemleri yapıyor*/
		else if(year % 4 !=0 && day == 28){			/*ve fonksiyonu tekrar çağırıyor*/
			day = 1;
			month++;
		}
		else if(day <= 28)
			day++;
		
		start_date[1] = (day % 10) + '0';
		start_date[0] = (day / 10) + '0';
		
		start_date[4] = (month % 10) + '0';
		start_date[3] = (month / 10) + '0';
		
		start_date[9] = (year % 10) + '0';
		year /= 10;
		start_date[8] = (year % 10) + '0';
		year /= 10;
		start_date[7] = (year % 10) + '0';
		year /= 10;
		start_date[6] = year + '0';
		return 	days(start_date,end_date,inp);	
	}
	return 0;

}

void calendar(){
	char *arr,temp_arr[10];
	int result,day,month,year,last_digit,j,i=0;
	int ay[12] = {1,4,4,0,2,5,0,3,6,1,4,6};			/*ay ce century array'leri ilk günü hesaplamak için kullanıldı*/
	int century[4] = {6,4,2,0};
	
	
	FILE *inp;	
	FILE *outp;							
	inp = fopen("input_data.txt","r");				/*dosyadan okuma ve dosyaya yazmak için 2 dosya açıldı.*/
	outp = fopen("new_data.txt","w");			
	
	fscanf(inp,"%c",&arr[i]);
	
	while(arr[i] != '\n'){							/*ilk günün haftanın hangi günü olduğunu*/
		temp_arr[i] = arr[i];						/*belirlemek için ilk satır alınıp*/
		i++;
		fscanf(inp,"%c",&arr[i]);					/*gerekli işlmeler yapıldı*/
	}
													/*gün ay ve yıl değişkenlere atıldı*/
	day   = ((temp_arr[0] - '0') * 10) + (temp_arr[1] - '0');
	month = ((temp_arr[3] - '0') * 10) + (temp_arr[4] - '0');
	year  = ((temp_arr[6] - '0') * 1000) + ((temp_arr[7] - '0')*100) + ((temp_arr[8] - '0') * 10) + (temp_arr[9] - '0');

	last_digit = year % 100;				/*28/08/1978 -- last_digit = 78 */
	
	result = (last_digit / 4) + day + ay[month-1];			
	if(year%4 == 0 && (month == 1 || month == 2))
		result++;
	for(i=0;i<4;i++){
		if(i == (year / 100) % 4)
			result += century[i];
	}
	result = (result + last_digit) % 7;
	if(result == 1)							/*çıkan sonuca göre haftanın günü belirlendi*/
		fprintf(outp,"Sunday,   ");
	else if(result == 2)
		fprintf(outp,"Monday,   ");
	else if(result == 3)
		fprintf(outp,"Tuesday,  ");
	else if(result == 4)
		fprintf(outp,"Wednesday,");
	else if(result == 5)
		fprintf(outp,"Thursday, ");
	else if(result == 6)
		fprintf(outp,"Friday,   ");
	else if(result == 0)
		fprintf(outp,"Saturday, ");
	if(month == 1)
		fprintf(outp,"January   %c%c,",temp_arr[0],temp_arr[1]);		/*günden sonra ay ve gün yazıldı*/
	else if(month == 2)
		fprintf(outp,"Febuary   %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 3)
		fprintf(outp,"March     %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 4)
		fprintf(outp,"April     %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 5)
		fprintf(outp,"May       %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 6)
		fprintf(outp,"June	    %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 7)
		fprintf(outp,"July 	    %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 8)
		fprintf(outp,"August    %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 9)
		fprintf(outp,"September %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 10)
		fprintf(outp,"October   %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 11)
		fprintf(outp,"November  %c%c,",temp_arr[0],temp_arr[1]);
	else if(month == 12)
		fprintf(outp,"December  %c%c,",temp_arr[0],temp_arr[1]);
		
	fprintf(outp,"%c%c%c%c\n",temp_arr[6],temp_arr[7],temp_arr[8],temp_arr[9]);		/*yıl yazıldı*/
	
	result = (result + 1) % 7;
	i=0;
	j=0;
	fscanf(inp,"%c",&arr[i]);
	while(arr[i] != EOF){						/*dosyayı sonuna kadar okudu ve tüm takvimi yeni dosyaya yazdırdı*/*/
		if(arr[i] == '/' && j == 0){
			j++;
			if(result == 1)
				fprintf(outp,"Sunday,   ");
			else if(result == 2)
				fprintf(outp,"Monday,   ");
			else if(result == 3)
				fprintf(outp,"Tuesday,  ");
			else if(result == 4)
				fprintf(outp,"Wednesday,");
			else if(result == 5)
				fprintf(outp,"Thursday, ");
			else if(result == 6)
				fprintf(outp,"Friday,   ");
			else if(result == 0)
				fprintf(outp,"Saturday, ");
			result = (result + 1) % 7;
		}
		else if(arr[i] == '/' && j == 1){
			month = (arr[i-2] - '0') * 10 + arr[i-1] - '0';
			j=0;
			if(month == 1)
				fprintf(outp,"January   %c%c,",arr[i-5],arr[i-4]);
			else if(month == 2)
				fprintf(outp,"Febuary   %c%c,",arr[i-5],arr[i-4]);
			else if(month == 3)
				fprintf(outp,"March     %c%c,",arr[i-5],arr[i-4]);
			else if(month == 4)
				fprintf(outp,"April     %c%c,",arr[i-5],arr[i-4]);
			else if(month == 5)
				fprintf(outp,"May       %c%c,",arr[i-5],arr[i-4]);
			else if(month == 6)
				fprintf(outp,"June	    %c%c,",arr[i-5],arr[i-4]);
			else if(month == 7)
				fprintf(outp,"July 	    %c%c,",arr[i-5],arr[i-4]);
			else if(month == 8)
				fprintf(outp,"August    %c%c,",arr[i-5],arr[i-4]);
			else if(month == 9)
				fprintf(outp,"September %c%c,",arr[i-5],arr[i-4]);
			else if(month == 10)
				fprintf(outp,"October   %c%c,",arr[i-5],arr[i-4]);
			else if(month == 11)
				fprintf(outp,"November  %c%c,",arr[i-5],arr[i-4]);
			else if(month == 12)
				fprintf(outp,"December  %c%c,",arr[i-5],arr[i-4]);
		}
		else if(arr[i] == '\n'){
			
			fprintf(outp,"%c%c%c%c\n",arr[i-4],arr[i-3],arr[i-2],arr[i-1]);
		}
		i++;
		fscanf(inp,"%c",&arr[i]);
	}	
	
	fclose(inp);
	fclose(outp);			/*dosyaları kapat*/


}

