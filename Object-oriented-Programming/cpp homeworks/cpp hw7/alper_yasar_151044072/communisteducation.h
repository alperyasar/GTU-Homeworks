//  foundUni(UniType):University
//	giveJob(name,surname,empType):Employee
#ifndef COMMUNISTEDUCATION_H
#define COMMUNISTEDUCATION_H

#include <iostream>

#include "university.h"
#include <complex>

using namespace std;
class Communist
{
public:
	Communist() ;
	template<class T>
	void giveJob(T& employee,string name,string surname);
	template<class U>
	bool foundUni(University<U> uni,string name);
	void process();
	
	University<int> *research;
 	University<double> *linguistic;
	University<complex<int>> *technical;
};

#endif