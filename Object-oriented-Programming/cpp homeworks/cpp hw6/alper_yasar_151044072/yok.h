//  foundUni(UniType):University
//	giveJob(name,surname,empType):Employee
#ifndef YOK_H
#define YOK_H

#include <iostream>
#include "employee.h"
#include "university.h"

using namespace std;
class YOK
{
public:
	YOK() {};
	template<class T>
	void giveJob(T& employee,string name,string surname);
	template<class U>
	bool foundUni(University<U> uni,string name);
};

#endif