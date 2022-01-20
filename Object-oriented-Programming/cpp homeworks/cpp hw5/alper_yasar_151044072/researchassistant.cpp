#include <iostream>
#include <string>
#include "researchassistant.h"

namespace SavitchEmployees
{
	ResearchAssistant :: ResearchAssistant()
						: AcademicPersonnel()
	{	
		job.assign("ResearchAssistant");
	}
	ResearchAssistant :: ResearchAssistant(const string NAME,const string SURNAME,const int PID) 
						: AcademicPersonnel(NAME,SURNAME,PID)
	{	
		job.assign("ResearchAssistant");
	}
	/*copy constructor*/
	ResearchAssistant :: ResearchAssistant(const ResearchAssistant &tempResearchAssistant)
						: AcademicPersonnel(tempResearchAssistant)
	{
		job.assign(tempResearchAssistant.job);
	}
	void ResearchAssistant :: research(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
	void ResearchAssistant :: readHW(University &temp,int happy){
		setHappinies(happy);
		setUniversity(temp);
	}
}