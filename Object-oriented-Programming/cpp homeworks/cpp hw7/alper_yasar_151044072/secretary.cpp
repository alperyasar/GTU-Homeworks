#include <iostream>
#include <string>
#include "secretary.h"

Secretary :: Secretary()
					: AdministrativePersonnel()
{	
	job.assign("Secretary");
}
Secretary :: Secretary(const string NAME,const string SURNAME,const int PID) 
					: AdministrativePersonnel(NAME,SURNAME,PID)
{	
	job.assign("Secretary");
}
/*copy constructor*/
Secretary :: Secretary(const Secretary &tempSecretary)
					: AdministrativePersonnel(tempSecretary)
{	
	job.assign(tempSecretary.job);
}
void Secretary :: receivePetition(){
	happinies += -1;
}
void Secretary :: work(string action) const{
	cout << name << " " << surname;
	cout <<" have "<<action<<". Therefore, " << name << " " << surname ;
	cout <<  " " << action <<". Happiness of "<< name << " " << surname ;
	cout <<" is " << happinies << " and money is "<< money ;
}
void Secretary ::  setNameSurname(string NAME,string SURNAME){
		this->name.assign(NAME);
	this->surname.assign(SURNAME);

}