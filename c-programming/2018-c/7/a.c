#include <stdio.h>

int main(){

	char *arr,temp_arr[10];
	int result,day,month,year,last_digit,j,i=0;
	int ay[12] = {1,4,4,0,2,5,0,3,6,1,4,6};
	int century[4] = {6,4,2,0};
	
	
	FILE *inp;
	FILE *outp;
	inp = fopen("input_data.txt","r");			
	outp = fopen("new_data.txt","w");			
	
	fscanf(inp,"%c",&arr[i]);
	
	while(arr[i] != '\n'){
		temp_arr[i] = arr[i];
		i++;
		fscanf(inp,"%c",&arr[i]);
	}

	day   = ((temp_arr[0] - '0') * 10) + (temp_arr[1] - '0');
	month = ((temp_arr[3] - '0') * 10) + (temp_arr[4] - '0');
	year  = ((temp_arr[6] - '0') * 1000) + ((temp_arr[7] - '0')*100) + ((temp_arr[8] - '0') * 10) + (temp_arr[9] - '0');

	last_digit = year % 100;
	
	result = (last_digit / 4) + day + ay[month-1];
	if(year%4 == 0 && (month == 1 || month == 2))
		result++;
	for(i=0;i<4;i++){
		if(i == (year / 100) % 4)
			result += century[i];
	}
	result = (result + last_digit) % 7;
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
	if(month == 1)
		fprintf(outp,"January   %c%c,",temp_arr[0],temp_arr[1]);
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
		
	fprintf(outp,"%c%c%c%c\n",temp_arr[6],temp_arr[7],temp_arr[8],temp_arr[9]);
	
	result = (result + 1) % 7;
	i=0;
	j=0;
	fscanf(inp,"%c",&arr[i]);
	while(arr[i] != EOF){
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
	fclose(outp);

	return 0;
}

/*j=0;


result = (result + last_digit) % 7;
	
	
	
	if(result == 1)
		fprintf(outp,"Sunday,");
	else if(result == 2)
		fprintf(outp,"Monday,");
	else if(result == 3)
		fprintf(outp,"Tuesday,");
	else if(result == 4)
		fprintf(outp,"Wednesday,");
	else if(result == 5)
		fprintf(outp,"Thursday,");
	else if(result == 6)
		fprintf(outp,"Friday,");
	else if(result == 0)
		fprintf(outp,"Saturday,");
	result = (result + 1) % 7;
	if(month == 1)
		fprintf(outp,"January %d,%d",day,year);
	else if(month == 2)
		fprintf(outp,"Febuary %d,%d",day,year);
	else if(month == 3)
		fprintf(outp,"March %d,%d,",day,year);
	else if(month == 4)
		fprintf(outp,"April %d,%d,",day,year);
	else if(month == 5)
		fprintf(outp,"May %d,%d,",day,year);
	else if(month == 6)
		fprintf(outp,"June %d,%d,",day,year);
	else if(month == 7)
		fprintf(outp,"July %d,%d,",day,year);
	else if(month == 8)
		fprintf(outp,"August %d,%d,",day,year);
	else if(month == 9)
		fprintf(outp,"September %d,%d,",day,year);
	else if(month == 10)
		fprintf(outp,"October %d,%d,",day,year);
	else if(month == 11)
		fprintf(outp,"November %d,%d,",day,year);
	else if(month == 12)
		fprintf(outp,"December %d,%d,",day,year);

*/

