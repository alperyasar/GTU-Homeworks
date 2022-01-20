#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <iostream>
#include <vector>
#include "employee.h"
#include "strcutemp.h"
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
	void setContribution(T given);
	bool jobControl(int control,string name, string surname);
	template<class U>
    friend ostream& operator <<(ostream&, const University<U>&);

	void giveJob(Employee emp);
	int sizeEmployee(){return employee.size(); };
	Emp *strEmployee;
	
private:
	T contribution;
	string name;
	vector<Employee> employee;
	
};



#endif
