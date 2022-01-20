#ifndef OFFICER_H
#define OFFICER_H

#include <string>
#include "administrativepersonnel.h"

namespace SavitchEmployees
{
	class Officer : public AdministrativePersonnel
	{
	public:
		Officer();
		Officer(const string NAME,const string SURNAME,const int PID);
		Officer(const Officer &tempOfficer);
		void makeDoc(University &temp,int happy);
	private:
		string job;
	};
}


#endif