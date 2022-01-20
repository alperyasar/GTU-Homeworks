#include <iostream>
#include "employee.h"


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
	this->happinies = tempEmployee.happinies;
}
ostream& operator <<(ostream& outputStream,const Employee& employee){
	outputStream << employee.pid << " " << employee.name << " " << employee.surname << endl;
	return outputStream;
}

void Employee :: drinkTea(){
	happinies += -1;

}
void Employee :: submitPetition(){
	happinies += -1;
}
void Employee :: work(string action) const{
	//do not anything in here
}

