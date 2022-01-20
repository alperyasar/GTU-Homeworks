#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "university.h"

using namespace std;


namespace SavitchEmployees
{
	class Employee{
	public:
		Employee();
		Employee(const string name,const string surname,const int pid);
		Employee(const Employee &tempEmployee);
	//	~Employee();
		friend ostream& operator <<(ostream& outputStream,const Employee& employee);
		bool controlName(const Employee &tempEmployee);
		string getName(){ return name; };
		string getSurname(){ return surname; };
		void setHappinies(int happy);
		int getHappinies(){ return happinies; };
		int getPid(){ return pid; };
		void deneme() {pid++;   cout << "bos " << pid << endl; };
		void setUniversity(University &temp);
		void drinkTea(University &temp,int happy);
		void submitPetition(University &temp,int happy);

	private:
		string name,surname;
		int pid,happinies;
		University *uni;
	};
}
#endif