#include <iostream>
#include <string>
#include "officer.h"

namespace SavitchEmployees
{
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
	void Officer :: makeDoc(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
}