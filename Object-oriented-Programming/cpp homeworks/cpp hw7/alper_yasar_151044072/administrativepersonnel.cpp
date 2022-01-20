#include <iostream>
#include <string>
#include "administrativepersonnel.h"

AdministrativePersonnel :: AdministrativePersonnel()
					: Employee()
{	
	job.assign("AdministrativePersonnel");
}
AdministrativePersonnel :: AdministrativePersonnel(const string NAME,const string SURNAME,const int PID) 
					: Employee(NAME,SURNAME,PID)
{	
	job.assign("AdministrativePersonnel");
}
/*copy constructor*/
AdministrativePersonnel :: AdministrativePersonnel(const AdministrativePersonnel &tempAdministrativePersonnel)
					: Employee(tempAdministrativePersonnel)
{	
	job.assign(tempAdministrativePersonnel.job);
}
void AdministrativePersonnel :: manageProcess(){
	--happinies;
}
void AdministrativePersonnel :: work(string action) const{
	
}
