//  foundUni(UniType):University
//	giveJob(name,surname,empType):Employee
#ifndef CAPITALISTEDUCATION_H
#define CAPITALISTEDUCATION_H

#include <iostream>
#include "employee.h"
#include "university.h"
#include "yok.h"
#include <complex>

using namespace std;
class Capitalist
{
public:
	Capitalist() ;
	template<class T>
	void giveJob(T& employee,string name,string surname);
	template<class U>
	bool foundUni(University<U> uni,string name);
	void process();
	
	University<int> *technical;
};

#endif