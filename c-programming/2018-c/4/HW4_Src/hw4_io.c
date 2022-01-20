/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/


#include "hw4_io.h"



int read_polynomial3(double * a0, double * a1, double * a2, double * a3){
								/*read number from user*/
	
	scanf("%lf",a0);			/*they write in write_polynomial funtion*/
	scanf("%lf",a1);			/*every pointer coefficient one x polynom*/
	scanf("%lf",a2);
	scanf("%lf",a3);
	
	return 0;


}

int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4){
							/*read number from user */
	
	scanf("%lf",a0);		/*they write in write_polynomial funtion*/
	scanf("%lf",a1);		/*every pointer coefficient one x polynom*/
	scanf("%lf",a2);
	scanf("%lf",a3);
	scanf("%lf",a4);
	

	return 0;


}

void write_polynomial3(double a0, double a1, double a2, double a3){
	read_polynomial3(&a0,&a1,&a2,&a3);
										/*a0*/
	if(a0 > 0.0){						/*every if control the coefficient value*/
		if(a0==1.0)
			printf("x^3");				/*if coefficient is different from 0 it print polynom*/
		else
			printf("+%.2fx^3",a0);		/*it print number with x*/
	}
	else if(a0 < 0.0){					/*if coefficient small 0 so print negative*/
		if(a0==-1.0)
			printf("-x^3");
		else
			printf("%.2fx^3",a0);
	}
	
	if(a1 > 0.0){						/*a1*/
		if(a1==1.0)
			printf("+x^2");
		else
			printf("+%.2fx^2",a1);
	}
	else if(a1 < 0.0){
	if(a1==-1.0)
			printf("-x^2");
		else
			printf("%.2fx^2",a1);
	}

	if(a2 > 0.0){						/*a2*/
		if(a2==1.0)
			printf("+x");
		else
			printf("+%.2fx",a2);
	}
	else if(a2 < 0.0){
		if(a2==-1.0)
			printf("-x");
		else
			printf("%.2fx",a2);
	}
										/*a3*/
	if(a3 > 0.0){						/*x^0 so just print number*/
			printf("+%.2f",a3);
	}
	else if(a3 < 0.0){
			printf("%.2f",a3);
	}
	printf("\n");


}


void write_polynomial4(double a0, double a1, double a2, double a3, double a4){
	int i;
	
	read_polynomial4(&a0,&a1,&a2,&a3,&a4);
											/*a0*/
	if(a0 > 0.0){							/*every if control the coefficient value*/
		if(a0==1.0)
			printf("x^4");					/*if coefficient is different from 0 it print polynom*/
		else
			printf("%.2fx^4",a0);			/*it print number with x*/
	}
	else if(a0 < 0.0){						/*if coefficient small 0 so print negative*/
		if(a0==-1.0)
			printf("-x^4");
		else
			printf("%.2fx^4",a0);
	}
											/*a1*/
	if(a1 > 0.0){
		if(a1==1.0)
			printf("+x^3");
		else
			printf("+%.2fx^3",a1);
	}
	else if(a1 < 0.0){
		if(a1==-1.0)
			printf("-x^3");
		else
			printf("%.2fx^3",a1);
	}
											/*a2*/
	if(a2 > 0.0){
		if(a2==1.0)
			printf("+x^2");
		else
			printf("+%.2fx^2",a2);
	}
	else if(a2 < 0.0){
	if(a2==-1.0)
			printf("-x^2");
		else
			printf("%.2fx^2",a2);
	}
											/*a3*/
	if(a3 > 0.0){
		if(a3==1.0)
			printf("+x");
		else
			printf("+%.2fx",a3);
	}
	else if(a3 < 0.0){
		if(a3==-1.0)
			printf("-x");
		else
			printf("%.2fx",a3);
	}
											/*a4*/
	if(a4 > 0.0){							/*x^0 so just print number*/
			printf("+%.2f",a4);
	}
	else if(a4 < 0.0){
			printf("%.2f",a4);
	}
	printf("\n");


}
