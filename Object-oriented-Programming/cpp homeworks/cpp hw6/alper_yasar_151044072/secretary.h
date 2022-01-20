#ifndef SECRETARY_H
#define SECRETARY_H

#include <string>
#include "administrativepersonnel.h"


class Secretary : public AdministrativePersonnel
{
public:
	Secretary();
	Secretary(const string NAME,const string SURNAME,const int PID);
	Secretary(const Secretary &tempSecretary);
	void receivePetition();
	void work(string action,string verb) const;
	void setNameSurname(string NAME,string SURNAME);
	
private:
	string job;	
};


#endif