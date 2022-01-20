#include <iostream>
#include <string>
#include "academicpersonnel.h"

namespace SavitchEmployees
{
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
	void AcademicPersonnel :: seeSuccessfulStudent(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
	void AcademicPersonnel :: makePublish(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
}