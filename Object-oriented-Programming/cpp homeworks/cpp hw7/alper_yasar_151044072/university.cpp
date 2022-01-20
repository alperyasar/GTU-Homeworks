#include "university.h"

template <class T>
University<T> :: University() : contribution() {
	strEmployee = new Emp;
	strEmployee = NULL;
}

template <class T>
University<T> :: University(T cont,string name) : contribution(cont) {
	this->name.assign(name);
	strEmployee = new Emp;
	strEmployee = NULL;
}

template <class T>
University<T> :: University(string name) : contribution() {
	this->name.assign(name);
	strEmployee = new Emp;
	strEmployee = NULL;
}

template <class T>
University<T>:: University(const University<T> &temp){
	contribution = temp.contribution;
	strEmployee = temp.strEmployee;
}

template <class T>
int University<T> ::  setCont(string name,string surname,int cont){
	for (int i = 0; i < 10; ++i)
	{
		if(name.compare(employee[i].getName()) == 0 && surname.compare(employee[i].getSurname()) == 0 ){
			contribution += cont;
			return 0;
		}
	}
	return 1;
	
}
template <class T>
void University<T>::setContribution(T given){
	contribution += given;
}
template <class T>
T University<T> ::  getCont(){
	return contribution;
}
template<typename T>
ostream& operator <<(ostream& os, const University<T>& temp) {
    os << temp.name << " - "<<  temp.contribution;
    return os;
}
template<class T>
void University<T> :: giveJob(Employee emp){
	employee.push_back(emp);

}

template<class T>
bool University<T> :: jobControl(int control,string name, string surname){
	return (employee[control].name.compare(name)==0 && employee[control].surname.compare(surname)==0);
}
