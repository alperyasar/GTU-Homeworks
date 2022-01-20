/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

#include "hw4_lib.h"

double integral(double f(double x), double xs, double xe, double delta){
	int area=0;	
												/*when xs(first number of function) small from xe(last number of funtion)*/
												/*loop will return*/
											
	while(xs<xe){
		area += f(xs)*delta;					/*xs will increase for other rectangle calculate of area*/
		xs += delta;							/*so it sum with delta*/
	}											/*delta is the edge of rectangle*/
	
	return area;								/*it's return calculate area*/
}


double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta){
	int area=0,tempy;
											/*when xs(first number of function) small from xe(last number of funtion)*/
											/*loop will return*/
	while(xs<xe){					
		tempy = ys;
		while(tempy<ye){					/*ys must be same so we assign ys to tempy*/
											/*when tempy(first number of function) small from tempy(last number of funtion)*/
											/*loop will return*/
			area += f(xs,tempy) * delta;	
			tempy += delta;
		}
											/*it like 3d graph*/
		xs += delta;
	}
	return area;							/*it's return calculate area*/
}


int derivatives(double f(double a), double x, double eps, double * d1, double * d2){
	double c,b;								  /*'a' use for assign to pointer *d1,b for *d2 */
	
	if(eps == 0)
		return -1;
	else{
		c = ((f(x+eps)-f(x-eps)) / (2.0*eps));    /*it's derivative function*/
		*d1 = c;
	
		b = ((f(x+eps)-2.0*f(x)+f(x-eps))/(eps*eps));	  /*it's double derivative function*/
		*d2 = b;
	}
	
	return 1;
}


int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double * e1, double *e2){
	double t1,t2;						/*t1 = derivative *d1, t2 = derivative *d2*/
	
	derivatives(f,x,eps,&t1,&t2);
	
	if(d1(x) >= t1){					/*if reel result bigger than or equal to calculator result*/
		*e1 = d1(x) - t1;				/*extract two result each other*/
	else 
		*e1 = t1 - d1(x);				/*calculator result bigger than reel result*/
	
	
	if(d2(x) >= t2){					/*same proccess for double derivate*/
		*e2 = d2(x) - t2;
	else 
		*e2 = t2 - d2(x);

}


int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4){
	double i=-100.0;
	int a=0;
									
	while(i<=100.0){					/*determine rangle(-100 to 100) for root*/
		if(f(i)==0){				/*if funtion = 0 this number is root*/
			if(a==0){				/*control each 0.1 number*/
				*x1=i;
				a++;
			}	
			else if(a==1){
				*x2=i;
				a++;
			}
			else if(a==2){
				*x3=i;
				a++;
			}
			else if(a==3){
				*x4=i;
				a++;
			}
		}
		i+=0.1;
	
	
	}
	return 0;
}

