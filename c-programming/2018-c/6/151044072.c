#include <stdio.h>

int find_size_of_line(char line[]){
	int i=0,size;
	
	while(line[i] != NULL){			/*loop until null*/
		i++;
	}
	return i-1;
}
void reverse_line(char line[], int line_lenght){
	int i,temp_ch,k;
	
	temp_ch = line[0];
	for(i=line_lenght;i>=0;i++){
		
		for(k=1;k<=i;k++){				/*reverse each line*/
			line[k-1]=line[k];				
			}
	}
	line[line_lenght] = temp_ch;
}

void encrypt_open_msg(){
	int key,j=0,k,l,i=0,input_status,in=0;
	FILE *inp;
	FILE *outp;
	char arr[1024],temp_ch;

	inp = fopen("open_msg.txt","r");			/*read from file*/
	outp = fopen("secret_msg.txt","w");			/*write to file*/
	
	input_status = fscanf(inp,"%c",&arr[i]);
	
	printf("enter key number :");
	scanf("%d",&key);
	
	while(input_status == 1){					/*assign to array in file*/
		printf("%c",arr[i]);
		i++;
		in++;
		input_status = fscanf(inp,"%c",&arr[i]);	
	}
	printf("\n");
	i=0;
	while(arr[i] != NULL){					/*encrypt each character in file*/
		
		if(arr[i] == ' '){
			arr[i] = '_';
			j++;
		}
		else if(arr[i] >= 'a' && arr[i] <= 'z' && arr[i] - key < 'a'){
			arr [i] = arr[i] + 26 - key;
			j++;
		}
		else if(arr[i] >= 'a' && arr[i] <= 'z'){
			arr[i] -= key;
			j++;
		}
		else if(arr[i] == '.'){
			arr[i] = '*';				/*ilk satıra kadar çevirmesi lazım*/
			j++;
		}
		else if(arr[i] == '\n'){
			i--;					
			for(k=i;k>=i-j;k--){
				temp_ch = arr[i-j];
				for(l=i-j+1;l<=k;l++){
					arr[l-1]=arr[l];				

				}	
				arr[k] = temp_ch;
			}
			j=0;
			i++;	
		}
		if(i == in){
			for(k=i;k>=i-j;k--){
				temp_ch = arr[i-j];
				for(l=i-j+1;l<=k;l++){
					arr[l-1]=arr[l];				

				}	
				arr[k] = temp_ch;
			}
			j=0;
		}
		i++;	 
	}
	printf("%s\n",arr);
	i=0;
	while(arr[i] != NULL){				/*print to file*/
		fprintf(outp,"%c",arr[i]);
		i++;
	}
	
	
	fclose(inp);
	fclose(outp);							
	
//	reverse_line(arr, i);
								
}
void decrypt_secret_msg(){
	int key,j=0,k,l,i=0,input_status,in=0;
	FILE *inp;
	FILE *outp;
	char arr[1024],temp_ch;

	inp = fopen("secret_msg.txt","r");			/*read from file*/
	outp = fopen("open_msg.txt","w");			/*write to file*/
	
	input_status = fscanf(inp,"%c",&arr[i]);
	
	printf("enter key number :");				/*key for decrypty*/
	scanf("%d",&key);
	
	while(input_status == 1){					/*assign array from file*/
		printf("%c",arr[i]);
		i++;
		in++;
		input_status = fscanf(inp,"%c",&arr[i]);	
	}
	printf("\n");
	i=0;
	while(arr[i] != NULL){					/*decrypty each character in file*/
		
		if(arr[i] == '_'){
			arr[i] = ' ';
			j++;
		}
		else if(arr[i] >= 'a' && arr[i] <= 'z' && arr[i] + key > 'z'){
			arr [i] = arr[i] - 26 + key;
			j++;
		}
		else if(arr[i] >= 'a' && arr[i] <= 'z'){
			arr[i] += key;
			j++;
		}
		else if(arr[i] == '*'){
			arr[i] = '.';				/*ilk satıra kadar çevirmesi lazım*/
			j++;
		}
		else if(arr[i] == '\n'){
			i--;
			for(k=i;k>=i-j;k--){
				temp_ch = arr[i-j];
				for(l=i-j+1;l<=k;l++){
					arr[l-1]=arr[l];				

				}	
				arr[k] = temp_ch;
			}
			j=0;
			i++;	
		}
		if(i == in-1){
			for(k=i;k>=i-j;k--){
				temp_ch = arr[i-j];
				for(l=i-j+1;l<=k;l++){
					arr[l-1]=arr[l];				

				}	
				arr[k] = temp_ch;
			}
			j=0;
		}
		i++;	 
	}
	printf("%s\n",arr);					/*print to terminal*/
	i=0;
	while(arr[i] != NULL){				/*print to file*/
		fprintf(outp,"%c",arr[i]);
		i++;
	}
	
//	reverse_line(arr, i);
	fclose(inp);
	fclose(outp);							

}


void menu(){
	int choose;
	
	do{														/*it will write menu*/
	
	printf("1. Encrypt \n2. Decrypt \n0. Exit \nChoice: ");
	scanf("%d",&choose);										/*user choose a section fo do one of them*/
	
	switch(choose){						
		case 1: encrypt_open_msg();
			   break;
		
		case 2:decrypt_secret_msg();
			   break;
	}
	
	}while(choose != 0);


}


int main(){
	menu();			/*just call menu*/

	return 0;
}


