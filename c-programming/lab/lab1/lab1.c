#include <stdio.h>

int readInt();
double readDouble();
char readChar();
double calculateBMI(int height, double weight);
double getInfoAndCalculateBMI();
void printPersonalInfo(int id, char name, int height, double weight);
void getAndPrintPersonalInfo();


int main(){
	double BMI1, BMI2;
	BMI1 = calculateBMI(170, 75.5);
	printf("%lf\n",BMI1);
	BMI2 = getInfoAndCalculateBMI();
	printf("%lf\n",BMI2);
	
	printPersonalInfo(2, 'A', 170, 75.5);
	getAndPrintPersonalInfo();
	return 0;
}

int readInt(){
	int number;
	scanf("%d",&number);
	return number;
}

double readDouble(){
	double number;
	scanf("%lf",&number);
	return number;
}

char readChar(){
	char character;
	scanf(" %c",&character);
	return character;
}

double calculateBMI(int height, double weight){
	double BMI;
	BMI = weight / ((height * 1.0) * (height * 1.0) / 10000) ;
	return BMI;
}

double getInfoAndCalculateBMI(){
	int height;
	double weight, BMI;
	printf("please enter height");
	height = readInt();
	printf("please enter weight");
	weight = readDouble();
	BMI = calculateBMI(height, weight);
	return BMI;
}

void printPersonalInfo(int id, char name, int height, double weight){
	double BMI;
	BMI = calculateBMI(height, weight);
	printf("ID:%d\nName:%c\nHeight:%d\nWeight:%lf\nBMI:%lf\n",id, name, height, 
		weight, BMI);
}

void getAndPrintPersonalInfo(){
	int id, height;
	char name;
	double weight;
	printf("please enter id");
	id = readInt();
	printf("please enter name");
	name = readChar();
	printf("please enter height");
	height = readInt();
	printf("please enter weight");
	weight = readDouble();
	printPersonalInfo(id, name, height, weight);
}
