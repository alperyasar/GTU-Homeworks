#ifndef ADMINISTRATIVEPERSONNEL_H
#define ADMINISTRATIVEPERSONNEL_H

#include <string>
#include "employee.h"


class AdministrativePersonnel : public Employee
{
public:
	AdministrativePersonnel();
	AdministrativePersonnel(const string NAME,const string SURNAME,const int PID);
	AdministrativePersonnel(const AdministrativePersonnel &tempAdministrativePersonnel);
	void manageProcess();
	void work(string action) const;
protected:
	string job;
};



#endif