#ifndef LECTURER_H
#define LECTURER_H

#include <string>
#include "academicpersonnel.h"


class Lecturer : public AcademicPersonnel
{
public:
	Lecturer();
	Lecturer(const string NAME,const string SURNAME,const int PID);
	Lecturer(const Lecturer &tempLecturer);
	void giveLesson();
	void giveHW();
	void setNameSurname(string NAME,string SURNAME);
	void work(string action,string verb) const;


private:
	string job;
};




#endif