#include "stdio.h"

 
#define COORDINATE 20

void classified(double class1_x,double class1_y,double class2_x,double class2_y);

int main()
{
	double class1_x,		class1_y,		 class2_x,		  class2_y;
	double class1_sumx = 0, class1_sumy = 0, class2_sumx = 0, class2_sumy = 0;
	double class1_xavg,		class1_yavg,	 class2_xavg,	  class2_yavg;			/*average of coordinate points*/

	int i;

	for(i = 0; i < COORDINATE; i++){
		if(i >= COORDINATE/2){					/*half of enters points for class 2*/
			scanf("%lf %lf", &class2_x, &class2_y);
			class2_sumx += class2_x;			/*add all x coordinate for class 2*/
			class2_sumy += class2_y;			/*add all y coordinate for class 2*/	
			
		}
		else{								
			scanf("%lf %lf", &class1_x, &class1_y);
			class1_sumx += class1_x;			/*add all x coordinate for class 1*/
			class1_sumy += class1_y;			/*add all y coordinate for class 1*/
			
		}
		
	}
	/*average coordinate points each class*/
	class1_xavg = class1_sumx / (COORDINATE / 2);
	class1_yavg = class1_sumy / (COORDINATE / 2);
	class2_xavg = class2_sumx / (COORDINATE / 2);
	class2_yavg = class2_sumy / (COORDINATE / 2);

	classified(class1_xavg,class1_yavg,class2_xavg,class2_yavg);

	return 0;
}
/*Foundation of each coordinate which class*/
void classified(double class1_x,double class1_y,double class2_x,double class2_y){
	double mid_x,mid_y,class_x,class_y,dividing;
	double inc;							/*incline*/
	int status;							/*for exitting loop*/
	
	/*it's necessary for avoid divide-by-zero*/
	if (class2_x - class1_x == 0)				/*if dividing number is 0 then we equal it's small number*/
		dividing = 0.0001;
	else
		dividing = class2_x - class1_x; 
	

	mid_x = (class2_x + class1_x)/2;			/*middle of the line average classes */
	mid_y = (class2_y + class1_y)/2;

	inc = (class2_y - class1_y) / (dividing);	/*incline of the line averages classes*/
	inc = -1 / inc;								/*incline of the seperating line*/

	status = scanf("%lf %lf", &class_x, &class_y);
														/*if scanf don't read number status will be 0*/
	while(status != 0){									/*so exit from loop*/
														
														/*if average points of class 1 bigger than mid point */
		if(class1_x + class1_y > mid_x + mid_y){		/*upper of seperating line will be class 1*/
			
												/*we looking where is the y points on seperating line*/
			if(class_x + class_y > class_x + (inc * (class_x - mid_x)) + mid_y)	/*y = inc * (class_x - mid_x)) + mid_y */
				printf("class 1\n");					/*it's important for which point bigger.*/
			else 										/*if entering point bigger than so it will be class 1, else class 2*/
				printf("class 2\n");

		}
		else{										/*upper of seperating line will be class 1*/
			if(class_x + class_y > class_x + (inc * (class_x - mid_x)) + mid_y){	/*same operation in there*/
				
				printf("class 2\n");
			}
			else	
				printf("class 1\n");
			
		}
		
		status = scanf("%lf %lf", &class_x, &class_y);			/*read next line it's number or something else*/
	}

}




