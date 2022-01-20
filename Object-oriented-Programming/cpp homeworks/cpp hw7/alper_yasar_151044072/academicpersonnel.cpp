#include <iostream>
#include <string>
#include "academicpersonnel.h"


AcademicPersonnel :: AcademicPersonnel()
					: Employee()
{	
	job.assign("AcademicPersonnel");
}
AcademicPersonnel :: AcademicPersonnel(const string NAME,const string SURNAME,const int PID) 
					: Employee(NAME,SURNAME,PID)
{	
	job.assign("AcademicPersonnel");
}
/*copy constructor*/
AcademicPersonnel :: AcademicPersonnel(const AcademicPersonnel &tempAcademicPersonnel)
					: Employee(tempAcademicPersonnel)
{	
	job.assign(tempAcademicPersonnel.job);
}
void AcademicPersonnel :: seeSuccessfulStudent(){
	happinies +=10;
}
void AcademicPersonnel :: makePublish(){
	happinies += 2;
}
void AcademicPersonnel :: work(string action) const{
	
}
