#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <iostream>
#include <vector>
#include "employee.h"
using namespace std;

template <class T>
class University
{
public:
	University();
	University(const University<T> &temp);
	University(string name);
	University(T cont,string name);
	int setCont(string name,string surname,int cont);
	string getName() { return name; };
	T getCont();
	bool jobControl(int control,string name, string surname);
	template<class U>
    friend ostream& operator <<(ostream&, const University<U>&);

	void giveJob(Employee emp);
	int sizeEmployee(){return employee.size(); };
	
private:
	T contribution;
	string name;
	vector<Employee> employee;
};



#endif
