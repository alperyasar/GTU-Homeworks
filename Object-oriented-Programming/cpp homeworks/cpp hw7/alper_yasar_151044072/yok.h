//  foundUni(UniType):University
//	giveJob(name,surname,empType):Employee
#ifndef YOK_H
#define YOK_H

#include <iostream>
#include "employee.h"
#include "university.h"
#include <complex>

using namespace std;
class YOK
{
public:
	YOK() ;
	template<class T>
	void giveJob(T& employee,string name,string surname);
	template<class U>
	bool foundUni(University<U> uni,string name);
	
	University<int> *research;
 	University<double> *linguistic;
	University<complex<int>> *technical;
};

#endif