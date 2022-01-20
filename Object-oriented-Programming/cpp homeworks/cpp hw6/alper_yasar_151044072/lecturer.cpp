#include <iostream>
#include <string>
#include "lecturer.h"


Lecturer :: Lecturer()
					: AcademicPersonnel()
{	
	job.assign("Lecturer");
}
Lecturer :: Lecturer(const string NAME,const string SURNAME,const int PID) 
					: AcademicPersonnel(NAME,SURNAME,PID)
{	
	job.assign("Lecturer");
}
/*copy constructor*/
Lecturer :: Lecturer(const Lecturer &tempLecturer)
					: AcademicPersonnel(tempLecturer)
{	
	job.assign(tempLecturer.job);
}
void Lecturer :: giveLesson(){
	++happinies; 
}
void Lecturer :: giveHW(){
	happinies += -2;
}
void Lecturer :: work(string action,string verb) const{

	cout << name << " " << surname;
	cout <<" have "<<action<<". Therefore, " << name << " " << surname ;
	cout <<  verb <<" "<< action <<". Happiness of "<< name << " " << surname ;
	cout <<" is " << happinies;
}

void  Lecturer :: setNameSurname(string NAME,string SURNAME){
	this->name.assign(NAME);
	this->surname.assign(SURNAME);

}


