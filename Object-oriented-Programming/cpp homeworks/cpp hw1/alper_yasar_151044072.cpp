/*Prints the fibonacci pyramid which has L+1 number of rows.
  Prints the largest number in the pyramid.
  Prints the heart of the pyramid.*/

#include <iostream>
using namespace std;

void pyramid(int numberOfPyramid);

int main()
{
	int L;
				/*take heigh of the pyramid*/
	cout << "Enter the number of Fibonacci pyramid : ";
	cin >> L;
			/*cheking number and error message if number is not correct number*/
	if(L<0)
		cout << "The number must be positive number" << endl;
	else if(L==0) 
		cout << 1 <<endl<< "This is not a pyramid. " << "Heart of the pyramid: -" << endl;
	else if (L > 46) 
		cout << "This is too big number for int, please choose one number between 0 and 46"<<endl;
	
	else		/*if number is between 0 and 46*/
		pyramid(L);

	return 0;
}

void pyramid(int numberOfPyramid){
	int k=0;
	unsigned int heartOfpyramidNumber,heartOfpyramidcoordinate;
	int sizeOfArray;
						/*find heart of pyramid coordinate point*/
	heartOfpyramidcoordinate = (numberOfPyramid+1)/2;
	if(numberOfPyramid % 2 == 0)
		++heartOfpyramidcoordinate;
					/*assign size of array size, sum of the all number in pyramid*/
	sizeOfArray = ((numberOfPyramid+1)*(numberOfPyramid+2))/2;
	unsigned int pyramid[sizeOfArray];
		/*finding number in array*/
	for (int i = 0; i < numberOfPyramid+1; ++i)
	{
		for (int j = 0; j < i+1; ++j)
		{
			if(i == 0 && j == 0)	/*first number*/
				pyramid[k] = 1;
			
			else if(i == 1)
				pyramid[k] = 1;			/*second row*/

			else if(j == 0)
				pyramid[k] = pyramid[((i-1)*i/2)] + pyramid[((i-2)*(i-1)/2)];	/*first coulomn*/
			
			
			else if(j == 1)							/*second coulomn*/
				pyramid[k] = pyramid[((i-1)*i/2)];

			else
				pyramid[k] = pyramid[((i-1)*i/2)+(j-1)] + pyramid[((i-2)*(i-1)/2)+(j-2)];
								/*the value of heart of the pyramid*/
			if(i == heartOfpyramidcoordinate && j == (heartOfpyramidcoordinate+1)/2 ){
				heartOfpyramidNumber = pyramid[k];
			}
						/*write numbers*/
			cout << pyramid[k] << " ";
			k++;
		}
		cout << endl;
	}

	cout << "Biggest number: " << pyramid[sizeOfArray-1] << endl;
	/*check the heart if 1 number or 2 number*/
	if((heartOfpyramidcoordinate+1) % 2 == 0)
		cout << "Heart of the pyramid: " << heartOfpyramidNumber << " " << heartOfpyramidNumber << endl;
	else
		cout << "Heart of the pyramid: " << heartOfpyramidNumber << endl;
}