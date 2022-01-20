#ifndef SECRETARY_H
#define SECRETARY_H

#include <string>
#include "administrativepersonnel.h"

namespace SavitchEmployees
{
	class Secretary : public AdministrativePersonnel
	{
	public:
		Secretary();
		Secretary(const string NAME,const string SURNAME,const int PID);
		Secretary(const Secretary &tempSecretary);
		void receivePetition(University &temp,int happy);
	private:
		string job;	
	};
}


#endif