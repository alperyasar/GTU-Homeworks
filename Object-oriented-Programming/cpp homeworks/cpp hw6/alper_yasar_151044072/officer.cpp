#include <iostream>
#include <string>
#include "officer.h"


Officer :: Officer()
					: AdministrativePersonnel()
{	
	job.assign("Officer");
}
Officer :: Officer(const string NAME,const string SURNAME,const int PID) 
					: AdministrativePersonnel(NAME,SURNAME,PID)
{	
	job.assign("Officer");
}
/*copy constructor*/
Officer :: Officer(const Officer &tempOfficer)
					: AdministrativePersonnel(tempOfficer)
{	
	job.assign(tempOfficer.job);
}
void Officer :: makeDoc(){
	happinies += -2;

}
void Officer :: work(string action,string verb) const{
	cout << name << " " << surname;
	cout <<" have "<<action<<". Therefore, " << name << " " << surname ;
	cout <<  verb<<" "<< action <<". Happiness of "<< name << " " << surname ;
	cout <<" is " << happinies;
}
void  Officer :: setNameSurname(string NAME,string SURNAME){
	this->name.assign(NAME);
	this->surname.assign(SURNAME);
}