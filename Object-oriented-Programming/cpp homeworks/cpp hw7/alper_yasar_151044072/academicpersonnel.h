#ifndef ACADEMICPERSONNEL_H
#define ACADEMICPERSONNEL_H

#include <string>
#include "employee.h"

class AcademicPersonnel : public Employee
{
public:
	AcademicPersonnel();
	AcademicPersonnel(const string NAME,const string SURNAME,const int PID);
	AcademicPersonnel(const AcademicPersonnel &tempAcademicPersonnel);
	void seeSuccessfulStudent();
	void makePublish();
	void work(string action) const;
protected:
	string job;
};



#endif