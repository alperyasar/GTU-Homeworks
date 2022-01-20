#include <iostream>
#include <string>
#include "researchassistant.h"


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
void ResearchAssistant :: research(){
	happinies += 3;
}
void ResearchAssistant :: readHW(){
	happinies += -3;
}
void ResearchAssistant :: work(string action,string verb) const{
	cout << name << " " << surname;
	cout <<" have "<<action<<". Therefore, " << name << " " << surname ;
	cout <<  verb <<" "<< action <<". Happiness of "<< name << " " << surname ;
	cout <<" is " << happinies;
}
void ResearchAssistant :: setNameSurname(string NAME,string SURNAME){
	this->name.assign(NAME);
	this->surname.assign(SURNAME);
}