#include <iostream>
#include <string>
#include "lecturer.h"

namespace SavitchEmployees
{
	Lecturer :: Lecturer()
						: AcademicPersonnel()
	{	
		job.assign("Lecturer");
	}
	Lecturer :: Lecturer(const string NAME,const string SURNAME,const int PID) 
						: AcademicPersonnel(NAME,SURNAME,PID)
	{	
		job.assign("Lecturer");
	}
	/*copy constructor*/
	Lecturer :: Lecturer(const Lecturer &tempLecturer)
						: AcademicPersonnel(tempLecturer)
	{	
		job.assign(tempLecturer.job);
	}
	void Lecturer :: giveLesson(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
	void Lecturer :: giveHW(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
}