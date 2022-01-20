#ifndef RESEARCHASSISTANT_H
#define RESEARCHASSISTANT_H

#include <string>
#include "academicpersonnel.h"


class ResearchAssistant : public AcademicPersonnel
{
public:
	ResearchAssistant();
	ResearchAssistant(const string NAME,const string SURNAME,const int PID);
	ResearchAssistant(const ResearchAssistant &tempResearchAssistant);
	void research();
	void readHW();
	void work(string action) const;
	void setNameSurname(string NAME,string SURNAME);
	
private:
	string job;	
};



#endif