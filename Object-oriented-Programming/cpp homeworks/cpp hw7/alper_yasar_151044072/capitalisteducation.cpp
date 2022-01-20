#include "capitalisteducation.h"
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
#include "employee.h"
#include "university.h"
#include "university.cpp"
#include "strcutemp.h"

Capitalist::Capitalist(){
  technical=new University<int>(0,"GTU");

}

template<class T>
void Capitalist::giveJob(T& employee,string name,string surname){
	employee.setNameSurname(name,surname);
	cout << employee.getName() << employee.getSurname() << " ";	
}
template<class U>
bool Capitalist::foundUni(University<U> uni,string uniName){
	return(uniName.compare(uni.getName()));
}
enum Actions{ document, slackness, project, lesson, seminar, academicPaper,
              administration,HomeworkTime,homeworkTimeout,incident,solution };
enum jobs{ lecturer,officer,researchassistant,secretary};

enum UniversityNames{research,linguistic,technical};

void Capitalist::process(){
    string name,getSurname,line;
    vector<Employee> employees,broker;
    Secretary secretaries;
    ResearchAssistant researchAssistants;
    Officer officers;
    Lecturer lecturers;
    vector<int> counter;
    char job;
    int size=0;
   

    srand((unsigned)time(nullptr));
    /*open file*/
    ifstream employeeFile;
    employeeFile.open("personnellist.txt");

    /*read file*/
    if(!employeeFile)        cerr << "Open Faiulre" << endl;
    /*read each employee from file and assign randomly two's complement*/
    /*if size reach to goal enough*/
    /*if size does not reach to goal select (reach-size (eg. 10-7=3)) unassigned employee*/

    while(getline(employeeFile, line)){    
        istringstream some_stream(line);
        some_stream >> name >> getSurname >> job;
        employees.push_back( Employee(name,getSurname,job,++size));
        
    }

    while (broker.size()<4)
    {
    	int randomNumber = rand() %employees.size();
    	if(employees[randomNumber].getChar() == 'B'){
    		broker.push_back(Employee(employees[randomNumber]));
    		cout << broker[broker.size()-1].getName() <<  " " << broker[broker.size()-1].getSurname() << "choose 2 worker : \n"; 
    		int i =0;
    		while(i < 2){
    			randomNumber = rand() %30;
    			if(employees[randomNumber].getChar() == 'W'){
	    			if(isExist(technical->strEmployee,employees[randomNumber].getName(),employees[randomNumber].getSurname()) == false){
	    				assign(technical->strEmployee,employees[randomNumber].getName(),employees[randomNumber].getSurname(),employees[randomNumber].getPid());
	    				++i;
 		   			}

    			}
    		}
    		
    	}
    }





    cout << endl << endl;
        cout << "_______________________________________________________________________________\n";

       /*choose employee to university*/
    for (int i = 0; i < 15; ++i)
    {
        int randomActions = rand() % 11;
        int randomNumber,check=1,control=0,uniControl=1;
        switch(randomActions)
        {
            case document:          
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
	                if(isExistPid(technical->strEmployee,randomNumber+1))
	                {                                             
	                    officers.makeDoc();
	                    control = 100;
		                employees[randomNumber].setMoney(3*3/2-1);
		                employees[randomNumber].work("document");
	                    technical->setContribution(3);
	                    cout << ", contribution of GTU is " << technical->getCont() << endl;
	                    break;
	                }
	                control++;
	            }
	            break;
            
            case slackness:         
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
	                int rand2 = rand() % 4;
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 0)
	                {                                                
	                    officers.drinkTea();
	                    control = 100;
		                employees[randomNumber].setMoney(-2*3/2+1);
	                    employees[randomNumber].work("slackness");
	                    technical->setContribution(-2);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 1) 
	                {                                                    
                        lecturers.drinkTea();
                        control = 100;
		                employees[randomNumber].setMoney(-2*3/2-1);
                        employees[randomNumber].work("slackness");
                        technical->setContribution(-2);
                        cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        break;
                    
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 2)
	                {                                                
	                    secretaries.drinkTea();
	                    control = 100;
		                employees[randomNumber].setMoney(-2*3/2+1);
	                    employees[randomNumber].work("slackness");
	                    technical->setContribution(-2);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 3)
	                {                                                
                        researchAssistants.drinkTea();
                        control = 100;
		                employees[randomNumber].setMoney(-2*3/2+1);
                        employees[randomNumber].work("slackness");
                        technical->setContribution(-2);
                        cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        break;
                    
	                }                 
	                control++;
	            }
           		break;
            case project:           
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
	                if(isExistPid(technical->strEmployee,randomNumber+1))
	                {                                              
	                    researchAssistants.research();
	                    control = 100;
		                employees[randomNumber].setMoney(4*3/2-1);
	                    employees[randomNumber].work("project");
	                    technical->setContribution(4);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }  
	                control++;
	            }
	            break;
            case lesson:            
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
	                if(isExistPid(technical->strEmployee,randomNumber+1))
	                {                                                
	                    lecturers.giveLesson();
	                    control = 100;
		                employees[randomNumber].setMoney(5*3/2-1);
	                    employees[randomNumber].work("lesson");
	                    technical->setContribution(5);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                control++;
	            }
	            break;
            case seminar:           
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
		            int rand2 = rand() % 2;
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 0)
	                {                                                
	                    lecturers.seeSuccessfulStudent();
	                    control = 100;
		                employees[randomNumber].setMoney(0*3/2-1);
	                    employees[randomNumber].work("HomeworkTime");
	                    technical->setContribution(0);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 1)
	                {                                                
	                    researchAssistants.seeSuccessfulStudent();
	                    control = 100;
		                employees[randomNumber].setMoney(0*3/2-1);
	                    employees[randomNumber].work("HomeworkTime");
	                    technical->setContribution(0);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                control++;
	            }
	            break;
            case academicPaper:     
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
		            int rand2 = rand() % 2;
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 0)
	                {                                                
	                    lecturers.makePublish();
	                    control = 100;
		                employees[randomNumber].setMoney(5*3/2-1);
	                    lecturers.work("academicPaper");
	                    technical->setContribution(5);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 1 )
	                {                                                
	                    researchAssistants.makePublish();
	                    control = 100;
		                employees[randomNumber].setMoney(5*3/2-1);
	                    employees[randomNumber].work("academicPaper");
	                    technical->setContribution(5);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                control++;
	            }
	            break;
            case administration:    
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
		            int rand2 = rand() % 2;
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 0)
	                {                                                
	                    officers.manageProcess();
	                    control = 100;
		                employees[randomNumber].setMoney(2*3/2-1);
	                    employees[randomNumber].work("administration");
	                    technical->setContribution(2);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 1)
	                {                                                
	                    secretaries.manageProcess();
	                    control = 100;
		                employees[randomNumber].setMoney(2*3/2-1);
	                    employees[randomNumber].work("administration");
	                    technical->setContribution(2);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                control++;
	            }
	            break;
            case HomeworkTime:      
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
	                if(isExistPid(technical->strEmployee,randomNumber+1))
	                {                                                
	                    lecturers.giveHW();
	                    control = 100;
		                employees[randomNumber].setMoney(1*3/2-1);
	                    employees[randomNumber].work("HomeworkTime");
	                    technical->setContribution(1);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                control++;
	            }
	            break;
            case homeworkTimeout:  
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
	                if(isExistPid(technical->strEmployee,randomNumber+1))
	                {                                                
	                    researchAssistants.readHW();
	                    control = 100;
		                employees[randomNumber].setMoney(2*3/2-1);
	                    employees[randomNumber].work("homeworkTimeout");
	                    technical->setContribution(2);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                control++;
	            }
	            break;
            case incident:          
	            while(control < 100)
	            {
	                randomNumber = rand()%employees.size();
	                if(isExistPid(technical->strEmployee,randomNumber+1))
	                {                                                
	                    secretaries.receivePetition();
	                    control = 100;
		                employees[randomNumber].setMoney(-1*3/2+1);
	                    employees[randomNumber].work("incident");
	                    technical->setContribution(-1);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                
	                }
	                control++;
	            }
            	break;
            case solution:          
		        while(control < 100)
		        {
	                randomNumber = rand()%employees.size();
	                int rand2 = rand() % 4;
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 0)
	                {                                                
	                    officers.submitPetition();
	                    control = 100;
		                employees[randomNumber].setMoney(-2*3/2+1);
	                    employees[randomNumber].work("solution");
	                    technical->setContribution(-2);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 1)                                                
                    { 
                        lecturers.submitPetition();
                        control = 100;
		                employees[randomNumber].setMoney(-2*3/2+1);
                        employees[randomNumber].work("solution");
                        technical->setContribution(-2);
                        cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        break;
                    
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 2)
	                {                                                
	                    secretaries.submitPetition();
	                    control = 100;
		                employees[randomNumber].setMoney(-2*3/2+1);
	                    employees[randomNumber].work("solution");
	                    technical->setContribution(-2);
	                    cout << ", contribution of GTU is " << technical->getCont()<<endl;
	                    break;
	                }
	                if(isExistPid(technical->strEmployee,randomNumber+1) && rand2 == 3)
	                {                                                
                        researchAssistants.submitPetition();
                        control = 100;
		                employees[randomNumber].setMoney(-2*3/2+1);
                        employees[randomNumber].work("solution");
                        technical->setContribution(-2);
                        cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        break;
                    
	                } 
            control++;
		    }
        	break;
        }
        if(technical->getCont()<0){
        	cout << "FIREEEEEEEEEEEEEEEEEEEE\n";
        		remove(technical->strEmployee,employees[randomNumber].getPid());
        		cout << "Broker resigns with ";
        		randomNumber = rand() %30;
    			int j =0;
	    		while(j < 1){
	    			randomNumber = rand() %30;
	    			if(employees[randomNumber].getChar() == 'W'){
		    			if(isExist(technical->strEmployee,employees[randomNumber].getName(),employees[randomNumber].getSurname()) == false){
		    				assign(technical->strEmployee,employees[randomNumber].getName(),employees[randomNumber].getSurname(),employees[randomNumber].getPid());
		    				++j;
	 		   			}

	    			}
	    		}
	    		cout << "New worker will be found. \n";
        	cout << "RESIGNNNNNNNNNNNNNNNNNN\n";

        	}
    }   
    cout << "_______________________________________________________________________________\n\n";
    cout << "Contribution of GTU is   " << technical->getCont() << endl;

}