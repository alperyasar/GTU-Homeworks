#ifndef LECTURER_H
#define LECTURER_H

#include <string>
#include "academicpersonnel.h"

namespace SavitchEmployees
{
	class Lecturer : public AcademicPersonnel
	{
	public:
		Lecturer();
		Lecturer(const string NAME,const string SURNAME,const int PID);
		Lecturer(const Lecturer &tempLecturer);
		void giveLesson(University &temp,int happy);
		void giveHW(University &temp,int happy);
	private:
		string job;
	};
}


#endif