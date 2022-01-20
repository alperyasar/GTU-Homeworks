#ifndef OFFICER_H
#define OFFICER_H

#include <string>
#include "administrativepersonnel.h"


class Officer : public AdministrativePersonnel
{
public:
	Officer();
	Officer(const string NAME,const string SURNAME,const int PID);
	Officer(const Officer &tempOfficer);
	void makeDoc();
	void work(string action) const;
	void setNameSurname(string NAME,string SURNAME);
	
private:
	string job;
};


#endif