#ifndef ACADEMICPERSONNEL_H
#define ACADEMICPERSONNEL_H

#include <string>
#include "employee.h"

namespace SavitchEmployees
{
	class AcademicPersonnel : public Employee
	{
	public:
		AcademicPersonnel();
		AcademicPersonnel(const string NAME,const string SURNAME,const int PID);
		AcademicPersonnel(const AcademicPersonnel &tempAcademicPersonnel);
		void seeSuccessfulStudent(University &temp,int happy);
		void makePublish(University &temp,int happy);
	protected:
		string job;
	};
}


#endif