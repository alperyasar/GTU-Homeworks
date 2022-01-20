#include <iostream>
#include "employee.h"


namespace SavitchEmployees
{
	Employee :: Employee(){
		name = "";
		surname = "";
		pid = 0;
		happinies = 0;
	}
	Employee :: Employee(const string NAME,const string SURNAME,const int PID){
		name.assign(NAME);
		surname.assign(SURNAME);
		pid = PID;
		happinies = 0;
	}
	/*copy constructor*/
	Employee :: Employee(const Employee &tempEmployee){
		this->name.assign(tempEmployee.name);
		this->surname.assign(tempEmployee.surname);
		this->pid = tempEmployee.pid;
		this->uni = tempEmployee.uni;
		this->happinies = tempEmployee.happinies;
	}
	ostream& operator <<(ostream& outputStream,const Employee& employee){
		outputStream << employee.pid << " " << employee.name << " " << employee.surname << endl;
		return outputStream;
	}
	/*check control name and surname are equal?*/
	bool Employee :: controlName(const Employee &tempEmployee){
		return(name.compare(tempEmployee.name)==0 && surname.compare(tempEmployee.surname)==0);
	}
	void Employee :: setHappinies(int happy){
		happinies += happy; 
	}

	void Employee :: setUniversity(University &temp){
		uni = &temp;
	}
	void Employee :: drinkTea(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
	void Employee :: submitPetition(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}

}