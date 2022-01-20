#include "strcutemp.h"



bool isExist(const Emp *temp, string name, string surname){
	while(temp != NULL){
		if(temp->name.compare(name) == 0 && temp->surname.compare(surname) == 0)
			return true;
		temp = temp->next;
	}
	return false;

}

bool isExistPid(const Emp *temp, int pid){
	while(temp != NULL){
		if(temp->pid  == pid)
			return true;
		temp = temp->next;
	}
	return false;

}

void assign(Emp *&strEmployee,string name,string surname,int pid){
	Emp* temp = strEmployee;
	if(strEmployee == NULL){
		strEmployee = new Emp;
		strEmployee->name.assign(name);
		strEmployee->surname.assign(surname);
		strEmployee->pid = pid;
		strEmployee->next = NULL;
		cout << strEmployee->name << " " << strEmployee->surname << endl;
		
	}
	else 
	{
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = new Emp;
		temp = temp->next;
		temp->name.assign(name);
		temp->surname.assign(surname);
		cout << temp->name << " " << temp->surname << endl;
		temp->next = NULL;
	}
}
void remove(Emp *&strEmployee,int pid){
	Emp* temp = strEmployee,*temp2;

	while((strEmployee->pid != pid && temp->next->pid != pid) && temp->next != NULL){
		temp = temp->next;
	}
	cout << "Broker fires " << temp->next->name << " "<< temp->next->name << endl;
	temp2 = new Emp;
	temp2 = temp->next;
	temp->next = temp2->next;
	delete temp2;

}
