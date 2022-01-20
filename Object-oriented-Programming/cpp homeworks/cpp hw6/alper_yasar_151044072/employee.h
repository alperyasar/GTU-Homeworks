#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

using namespace std;


class Employee{
public:
	Employee();
	Employee(const string name,const string surname,const int pid);
	Employee(const Employee &tempEmployee);
//	~Employee();
	friend ostream& operator <<(ostream& outputStream,const Employee& employee);
	string getName(){ return name; };
	string getSurname(){ return surname; };
	virtual void work(string action) const;
	int getHappinies(){ return happinies; };
	int getPid(){ return pid; };

	void drinkTea();
	void submitPetition();

protected:
	string name,surname;
	int pid,happinies;

};

#endif

