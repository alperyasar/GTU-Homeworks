#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <ctime> 

#include "secretary.h"
#include "researchassistant.h"
#include "officer.h"
#include "lecturer.h"
#include "university.h"

using namespace std;
using namespace SavitchEmployees;
//using SavitchEmployees :: Employee;

enum Actions{ document, slackness, project, lesson, seminar, academicPaper,
	 		  administration,HomeworkTime,homeworkTimeout,incident,solution };


int main(){
	vector<Secretary> secretaries;
	vector<ResearchAssistant> researchAssistants;
	vector<Officer> officers;
	vector<Lecturer> lecturers;
	//vector<Employee> secretaries,researchAssistants,officers,lecturers;
	string job,name,getSurname,line;
    vector<Employee> employees,unassigned;
    vector<int> counter;
	int size=0;
	
	srand((unsigned)time(nullptr));
	/*open file*/
	ifstream employeeFile;
    employeeFile.open("personnellist.txt");

    /*read file*/
    if(!employeeFile)        cerr << "Open Faiulre" << endl;
    /*read each employee from file and assing randomly two's complement*/
    /*if size reach to goal enough*/
    /*if size does not reach to goal select (reach-size (eg. 10-7=3)) unassigned employee*/
    while(getline(employeeFile, line)){    
    	istringstream some_stream(line);
		some_stream >> job >> name >> getSurname;
		if(job.compare("Lecturer") == 0){
    		lecturers.push_back( Lecturer(name,getSurname,++size));
		}
    	else if(job.compare("Officer") == 0){
    		officers.push_back( Officer(name,getSurname,++size));
		}
    	else if(job.compare("ResearchAssistant") == 0){
    		researchAssistants.push_back( ResearchAssistant(name,getSurname,++size));
    	}
    	else if(job.compare("Secretary") == 0){
    		secretaries.push_back( Secretary(name,getSurname,++size));
    	}
    	
    }
    for (int i = 0; i < 10; ++i)
    {
    	int couterControl =0;
    	int randomNumber = rand() % size;
    	for (int j = 0; j < counter.size(); ++j)
    	{
    		if(randomNumber == counter[j]){
    			couterControl++;
    			i--;
    		}
    	}
    	if(couterControl == 0)
    		counter.push_back(randomNumber);
    }

       /*choose employee to university*/

    University GebzeTechnicalUniversity;
    cout << "_____________________________________________________\n" << endl;
    int i;
    for (i = 0; i < 10; ++i)
    {
		for (int k = 0; k < lecturers.size(); ++k)
		{
			if(lecturers[k].getPid() == counter[i]){
				lecturers[k].setUniversity(GebzeTechnicalUniversity);
				cout << i+1 << " " << lecturers[k].getName() << " " << lecturers[k].getSurname() << " selected by Gebze Technical University\n";
			}
		}
		for (int k = 0; k < officers.size(); ++k)
		{
			if(officers[k].getPid() == counter[i]){
				officers[k].setUniversity(GebzeTechnicalUniversity);
				cout << i+1 << " "  << officers[k].getName() << " " << officers[k].getSurname() << " selected by Gebze Technical University\n";
			}
		}
		for (int k = 0; k < researchAssistants.size(); ++k)
		{
			if(researchAssistants[k].getPid() == counter[i]){
				researchAssistants[k].setUniversity(GebzeTechnicalUniversity);
				cout << i+1 << " "  << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() << " selected by Gebze Technical University\n";
			}
		}
		for (int k = 0; k < secretaries.size(); ++k)
		{
			if(secretaries[k].getPid() == counter[i]){
				secretaries[k].setUniversity(GebzeTechnicalUniversity);
				cout << i+1 << " "  << secretaries[k].getName() << " " << secretaries[k].getSurname() << " selected by Gebze Technical University\n";
			}
		
    	}
    }
    cout << "_____________________________________________________\n" <<  endl;

    /*write story*/ 

    for (i = 0; i < 50; ++i)
    {
    	int randomActions = rand() % 11;
    	int randomNumber,check=1,control=0;

    	switch(randomActions)
    	{
    		case document:			
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < officers.size(); ++k)
    											{
    												if(officers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(3);													
    													officers[k].makeDoc(GebzeTechnicalUniversity,-2);
    													check = 0;
    													cout << officers[k].getName() << " " << officers[k].getSurname() ;
    													cout <<" have document. Therefore, " << officers[k].getName() << " " << officers[k].getSurname() ;
    													cout << " make Document. Happiness of "<< officers[k].getName() << " " << officers[k].getSurname() ;
    													cout <<" is " << officers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case slackness: 		
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < secretaries.size(); ++k)
    											{
    												if(secretaries[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-2);													
    													secretaries[k].drinkTea(GebzeTechnicalUniversity,5);
    													check = 0;
    													cout << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout <<" have slackness. Therefore, " << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout << " drinks tea. Happiness of "<< secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout <<" is " << secretaries[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < researchAssistants.size(); ++k)
    											{
    												if(researchAssistants[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-2);													
    													researchAssistants[k].drinkTea(GebzeTechnicalUniversity,5);
    													check = 0;
    													cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout <<" have slackness. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout << " drinks tea. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout <<" is " << researchAssistants[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < lecturers.size(); ++k)
    											{
    												if(lecturers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-2);													
    													lecturers[k].drinkTea(GebzeTechnicalUniversity,5);
    													check = 0;
    													cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" have slackness. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout << " drinks tea. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" is " << lecturers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < officers.size(); ++k)
    											{
    												if(officers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-2);													
    													officers[k].drinkTea(GebzeTechnicalUniversity,5);
    													check = 0;
    													cout << officers[k].getName() << " " << officers[k].getSurname() ;
    													cout <<" have slackness. Therefore, " << officers[k].getName() << " " << officers[k].getSurname() ;
    													cout << " drinks tea. Happiness of "<< officers[k].getName() << " " << officers[k].getSurname();
    													cout <<" is " << officers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case project:   		
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < researchAssistants.size(); ++k)
    											{
    												if(researchAssistants[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(4);													
    													researchAssistants[k].research(GebzeTechnicalUniversity,3);
    													check = 0;
    													cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout <<" have project. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout << " research. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout <<" is " << researchAssistants[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case lesson:    		
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < lecturers.size(); ++k)
    											{
    												if(lecturers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(5);													
    													lecturers[k].giveLesson(GebzeTechnicalUniversity,1);
    													check = 0;
    													cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" have lesson. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout << " give lesson. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" is " << lecturers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case seminar:			
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											
    											for (int k = 0; k < researchAssistants.size(); ++k)
    											{
    												if(researchAssistants[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(0);													
    													researchAssistants[k].seeSuccessfulStudent(GebzeTechnicalUniversity,10);
    													check = 0;
    													cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout <<" have seminar. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout << " see successful student. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname(); 
    													cout <<" is " << researchAssistants[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < lecturers.size(); ++k)
    											{
    												if(lecturers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(0);													
    													lecturers[k].seeSuccessfulStudent(GebzeTechnicalUniversity,10);
    													check = 0;
    													cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" have seminar. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout << " see successful student. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname(); 
    													cout <<" is " << lecturers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case academicPaper:		
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < researchAssistants.size(); ++k)
    											{
    												if(researchAssistants[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(5);													
    													researchAssistants[k].makePublish(GebzeTechnicalUniversity,2);
    													check = 0;
    													cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout <<" have academic paper. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout << " make publish. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ; 
    													cout <<" is " << researchAssistants[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < lecturers.size(); ++k)
    											{
    												if(lecturers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(5);													
    													lecturers[k].makePublish(GebzeTechnicalUniversity,2);
    													check = 0;
    													cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" have academic paper. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout << " make publish. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" is " << lecturers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case administration:	
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < secretaries.size(); ++k)
    											{
    												if(secretaries[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(2);													
    													secretaries[k].manageProcess(GebzeTechnicalUniversity,-1);
    													check = 0;
    													cout << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout <<" have administration. Therefore, " << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout << " manage process. Happiness of "<< secretaries[k].getName() << " " << secretaries[k].getSurname(); 
    													cout <<" is " << secretaries[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < officers.size(); ++k)
    											{
    												if(officers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(2);													
    													officers[k].manageProcess(GebzeTechnicalUniversity,-1);
    													check = 0;
    													cout << officers[k].getName() << " " << officers[k].getSurname() ;
    													cout <<" have administration. Therefore, " << officers[k].getName() << " " << officers[k].getSurname() ;
    													cout << " manage process. Happiness of "<< officers[k].getName() << " " << officers[k].getSurname() ;
    													cout <<" is " << officers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case HomeworkTime: 		
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < lecturers.size(); ++k)
    											{
    												if(lecturers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(1);													
    													lecturers[k].giveHW(GebzeTechnicalUniversity,-2);
    													check = 0;
    													cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" have homework time. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout << " give homework. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname();
    													cout <<" is " << lecturers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case homeworkTimeout:	
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < researchAssistants.size(); ++k)
    											{
    												if(researchAssistants[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(2);													
    													researchAssistants[k].readHW(GebzeTechnicalUniversity,-3);
    													check = 0;
    													cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout <<" have homework timeout. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout << " read homework. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname(); 
    													cout <<" is " << researchAssistants[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case incident:			
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < secretaries.size(); ++k)
    											{
    												if(secretaries[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-1);													
    													secretaries[k].receivePetition(GebzeTechnicalUniversity,-1);
    													check = 0;
    													cout << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout <<" have incident. Therefore, " << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout << " receive petition. Happiness of "<< secretaries[k].getName() << " " << secretaries[k].getSurname(); 
    													cout <<" is " << secretaries[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    		case solution:			
    								while(check && control < 100)
    								{
    									randomNumber = rand()%25;
    									for (int j = 0; j < counter.size(); ++j)
    									{
    										if(counter[j] == randomNumber)
    										{
    											for (int k = 0; k < secretaries.size(); ++k)
    											{
    												if(secretaries[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-2);													
    													secretaries[k].submitPetition(GebzeTechnicalUniversity,1);
    													check = 0;
    													cout << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout <<" have solution. Therefore, " << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
    													cout << " submit petition. Happiness of "<< secretaries[k].getName() << " " << secretaries[k].getSurname(); 
    													cout <<" is " << secretaries[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < researchAssistants.size(); ++k)
    											{
    												if(researchAssistants[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-2);													
    													researchAssistants[k].submitPetition(GebzeTechnicalUniversity,1);
    													check = 0;
    													cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout <<" have solution. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
    													cout << " submit petition. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname(); 
    													cout <<" is " << researchAssistants[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < lecturers.size(); ++k)
    											{
    												if(lecturers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-2);													
    													lecturers[k].submitPetition(GebzeTechnicalUniversity,1);
    													check = 0;
    													cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout <<" have solution. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
    													cout << " submit petition. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname();
    													cout <<" is " << lecturers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    											for (int k = 0; k < officers.size(); ++k)
    											{
    												if(officers[k].getPid() == counter[j])
    												{
    													GebzeTechnicalUniversity.setCont(-2);													
    													officers[k].submitPetition(GebzeTechnicalUniversity,1);
    													check = 0;
    													cout << officers[k].getName() << " " << officers[k].getSurname() ;
    													cout <<" have solution. Therefore, " << officers[k].getName() << " " << officers[k].getSurname() ;
    													cout << " submit petition. Happiness of "<< officers[k].getName() << " " << officers[k].getSurname();
    													cout <<" is " << officers[k].getHappinies() << ", contribution of Gebze Technical University is ";
    													cout << GebzeTechnicalUniversity.getCont()<<".\n";
    													break;
    												}
    											}
    										}
    									}
                                        control++;
    								}
    								break;
    	}
    }
    cout << "_____________________________________________________\n";
    cout << "Total contribution of Gebze Technical University is : " << GebzeTechnicalUniversity.getCont()<<endl;

}