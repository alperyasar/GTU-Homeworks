//  foundUni(UniType):University
//	giveJob(name,surname,empType):Employee
#ifndef LIBERALEDUCATION_H
#define LIBERALEDUCATION_H

#include <iostream>
#include "employee.h"
#include "university.h"
#include <complex>

using namespace std;
class Liberal
{
public:
	Liberal() ;
	template<class T>
	void giveJob(T& employee,string name,string surname);
	template<class U>
	bool foundUni(University<U> uni,string name);
	void process();

	University<int> *research;
 	University<double> *linguistic;
	University<complex<int> > *technical;
};

#endif