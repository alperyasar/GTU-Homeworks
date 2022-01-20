#include "stdio.h"

int main()
{
	double argc,a;
	int status;
	status = scanf("%lf %lf",&argc,&a);

	while(status != 0){
		printf("%lf %lf %d\n",argc,a,status);
		status = scanf("%lf %lf",&argc, &a);
	}
	printf("%d\n", status);
	return 0;
}