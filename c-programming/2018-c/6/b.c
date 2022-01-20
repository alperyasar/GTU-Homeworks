#include <stdio.h>

int main(){
int key,j=0,k,l,i=0,input_status,in=0;
	FILE *inp;
	FILE *outp;
	char arr[1024],temp_ch;

	inp = fopen("open_msg.txt","r");
	outp = fopen("secret_msg.txt","w");
	
	input_status = fscanf(inp,"%c",&arr[i]);
	
	printf("enter key number :");
	scanf("%d",&key);
	
	while(input_status == 1){
		printf("%c",arr[i]);
		i++;
		in++;
		input_status = fscanf(inp,"%c",&arr[i]);	
	}
	printf("\n");
	i=0;
	while(arr[i] != NULL){
		
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
	while(arr[i] != NULL){
		fprintf(outp,"%c",arr[i]);
		i++;
	}
	
	
	fclose(inp);
	fclose(outp);							
	return 0;
}

