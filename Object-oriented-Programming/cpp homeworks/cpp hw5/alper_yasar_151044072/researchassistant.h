#ifndef RESEARCHASSISTANT_H
#define RESEARCHASSISTANT_H

#include <string>
#include "academicpersonnel.h"

namespace SavitchEmployees
{
	class ResearchAssistant : public AcademicPersonnel
	{
	public:
		ResearchAssistant();
		ResearchAssistant(const string NAME,const string SURNAME,const int PID);
		ResearchAssistant(const ResearchAssistant &tempResearchAssistant);
		void research(University &temp,int happy);
		void readHW(University &temp,int happy);
	private:
		string job;	
	};
}


#endif