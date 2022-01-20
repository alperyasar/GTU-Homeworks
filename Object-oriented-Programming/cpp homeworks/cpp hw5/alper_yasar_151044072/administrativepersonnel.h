#ifndef ADMINISTRATIVEPERSONNEL_H
#define ADMINISTRATIVEPERSONNEL_H

#include <string>
#include "employee.h"

namespace SavitchEmployees
{
	class AdministrativePersonnel : public Employee
	{
	public:
		AdministrativePersonnel();
		AdministrativePersonnel(const string NAME,const string SURNAME,const int PID);
		AdministrativePersonnel(const AdministrativePersonnel &tempAdministrativePersonnel);
		void manageProcess(University &temp,int happy);
	protected:
		string job;
	};
}


#endif