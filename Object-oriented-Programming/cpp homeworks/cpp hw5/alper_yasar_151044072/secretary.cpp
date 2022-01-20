#include <iostream>
#include <string>
#include "secretary.h"

namespace SavitchEmployees
{
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
	void Secretary :: receivePetition(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
}