#include "liberaleducation.h"
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


Liberal::Liberal(){
  research=new University<int>(0,"IYTE");
  linguistic=new University<double>(0,"BOGAZICI");
  technical=new University<complex<int> >("GTU");

}

template<class T>
void Liberal::giveJob(T& employee,string name,string surname){
	employee.setNameSurname(name,surname);
	cout << employee.getName() << employee.getSurname() << " ";	
}
template<class U>
bool Liberal::foundUni(University<U> uni,string uniName){
	return(uniName.compare(uni.getName()));
}
enum Actions{ document, slackness, project, lesson, seminar, academicPaper,
              administration,HomeworkTime,homeworkTimeout,incident,solution };
enum jobs{ lecturer,officer,researchassistant,secretary};

//enum UniversityNames{research,linguistic,technical};
void Liberal::process(){
    string job,name,getSurname,line;
    vector<Employee> employees;
    vector<Secretary> secretaries;
    vector<ResearchAssistant> researchAssistants;
    vector<Officer> officers;
    vector<Lecturer> lecturers;
    Secretary tempsecretary;
    ResearchAssistant tempresearchassistant;
    Officer tempofficer;
    Lecturer templecturer;
    vector<int> counter;
    int size=0;
   


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
        some_stream >> name >> getSurname;
        employees.push_back( Employee(name,getSurname,++size));
        
    }

 /*   University<int> research(0,"IYTE");
    University<double> linguistic(0,"BOGAZICI");
    University<complex<int>> technical("GTU");*/

    for (int i = 0; i < 30; ++i)
    {
        int control =0;
        int randomNumber = rand() % 4;
        switch(randomNumber)
        {
            case lecturer :           
                job.assign("lecturer");
                break;
            case officer :
                job.assign("officer");
                break;        
            case researchassistant :
                job.assign("researchassistant");
                break;
            case secretary :
                job.assign("secretary");
                break;                
        }
        randomNumber = rand() % 3;
        if(randomNumber == 0 && research->sizeEmployee() < 10){
            cout << "IYTE requests " << job<<endl;
            
            if(job.compare("officer") == 0){
                giveJob(tempofficer,employees[i].getName(),employees[i].getSurname());
                officers.push_back(tempofficer);
            }
            else if(job.compare("researchassistant") == 0){
                giveJob(tempresearchassistant,employees[i].getName(),employees[i].getSurname());
                researchAssistants.push_back(tempresearchassistant);
            }
            else if(job.compare("secretary") == 0){
                giveJob(tempsecretary,employees[i].getName(),employees[i].getSurname());
                secretaries.push_back(tempsecretary);
            }
            else if(job.compare("lecturer") == 0){
                giveJob(templecturer,employees[i].getName(),employees[i].getSurname());
                lecturers.push_back(templecturer);
            }
            research->giveJob(employees[i]);
            cout << "YOK give job to "<< employees[i].getName() << " " << employees[i].getSurname() << " as " << job << endl;
            control++;
        }
        else if(randomNumber == 1 && linguistic->sizeEmployee() < 10){
            cout << "BOGAZICI requests " << job<<endl;
            if(job.compare("officer") == 0){
                giveJob(tempofficer,employees[i].getName(),employees[i].getSurname());
                officers.push_back(tempofficer);
            }
            else if(job.compare("researchassistant") == 0){
                giveJob(tempresearchassistant,employees[i].getName(),employees[i].getSurname());
                researchAssistants.push_back(tempresearchassistant);
            }
            else if(job.compare("secretary") == 0){
                giveJob(tempsecretary,employees[i].getName(),employees[i].getSurname());
                secretaries.push_back(tempsecretary);
            }
            else if(job.compare("lecturer") == 0){
                giveJob(templecturer,employees[i].getName(),employees[i].getSurname());
                lecturers.push_back(templecturer);
            }
            linguistic->giveJob(employees[i]);
            cout << "YOK give job to "<< employees[i].getName() << " " << employees[i].getSurname() << " as " << job << endl;
            control++;
        }
        else if(randomNumber == 2 && technical->sizeEmployee() < 10){
            cout << "GTU requests " << job<<endl;
            if(job.compare("officer") == 0){
                giveJob(tempofficer,employees[i].getName(),employees[i].getSurname());
                officers.push_back(tempofficer);
            }
            else if(job.compare("researchassistant") == 0){
                giveJob(tempresearchassistant,employees[i].getName(),employees[i].getSurname());
                researchAssistants.push_back(tempresearchassistant);
            }
            else if(job.compare("secretary") == 0){
                giveJob(tempsecretary,employees[i].getName(),employees[i].getSurname());
                secretaries.push_back(tempsecretary);
            }
            else if(job.compare("lecturer") == 0){
                giveJob(templecturer,employees[i].getName(),employees[i].getSurname());
                lecturers.push_back(templecturer);
            }     
            technical->giveJob(employees[i]);
            cout << "YOK give job to "<< employees[i].getName() << " " << employees[i].getSurname() << " as " << job << endl;
            control++;
        }
        if(control == 0)    --i;
    }
    cout << endl << endl;
        cout << "_______________________________________________________________________________\n";

       /*choose employee to university*/
    for (int i = 0; i < 50; ++i)
    {
        int randomActions = rand() % 11;
        int randomNumber,check=1,control=0,uniControl=1;
        switch(randomActions)
        {
            case document:          
            while(control < 100)
            {
                randomNumber = rand()%30;
                for(int k = 0; k < officers.size();k++){
                    if(employees[randomNumber].getName().compare(officers[k].getName())==0 && employees[randomNumber].getSurname().compare(officers[k].getSurname())==0)
                    {                                             
                        officers[k].makeDoc();
                        control = 100;
                        officers[k].work("document");
                        if(uniControl){
                            uniControl = research->setCont(officers[k].getName(),officers[k].getSurname(),3);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = linguistic->setCont(officers[k].getName(),officers[k].getSurname(),3);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = technical->setCont(officers[k].getName(),officers[k].getSurname(),3);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                control++;
            }
            break;
            case slackness:         
            while(control < 100)
            {
                randomNumber = rand()%30;
                for(int k = 0; k < officers.size();k++){
                    if(employees[randomNumber].getName().compare(officers[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(officers[k].getSurname())==0)
                    {
                                                                         
                        officers[k].drinkTea();
                        control = 100;
                        officers[k].work("slackness");
                        if(uniControl){
                            uniControl = research->setCont(officers[k].getName(),officers[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = linguistic->setCont(officers[k].getName(),officers[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = technical->setCont(officers[k].getName(),officers[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                for(int k = 0; k < lecturers.size();k++){
                    if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                    {
                                                                         
                        lecturers[k].drinkTea();
                        control = 100;
                        lecturers[k].work("slackness");
                        if(uniControl){
                            uniControl = research->setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = linguistic->setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = technical->setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                for(int k = 0; k < researchAssistants.size();k++){
                    if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                    {
                                                                         
                        researchAssistants[k].drinkTea();
                        control = 100;
                        researchAssistants[k].work("slackness");
                        if(uniControl){
                            uniControl = research->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = linguistic->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = technical->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                for(int k = 0; k < secretaries.size();k++){
                    if(employees[randomNumber].getName().compare(secretaries[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(secretaries[k].getSurname())==0)
                    {
                                                                         
                        secretaries[k].drinkTea();
                        control = 100;
                        secretaries[k].work("slackness");
                        if(uniControl){
                            uniControl = research->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = technical->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }                                  
                control++;
            }
            break;
            case project:           
            while(control < 100)
            {
                randomNumber = rand()%30;
               
                for(int k = 0; k < researchAssistants.size();k++){
                    if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                    {
                                                                         
                        researchAssistants[k].research();
                        control = 100;
                        researchAssistants[k].work("project");
                        if(uniControl){
                           uniControl =  research->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),4);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),4);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = technical->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),4);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }  
                control++;
            }
            break;
            case lesson:            
            while(control < 100)
            {
                randomNumber = rand()%30;
                for(int k = 0; k < lecturers.size();k++){
                    if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                    {
                                                                         
                        lecturers[k].giveLesson();
                        control = 100;
                       lecturers[k].work("lesson");
                        if(uniControl){
                          uniControl =   research->setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = technical->setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                control++;
            }
            break;
            case seminar:           
            while(control < 100)
            {
                randomNumber = rand()%30;
                
                for(int k = 0; k < lecturers.size();k++){
                    if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                    {
                                                                         
                        lecturers[k].seeSuccessfulStudent();
                        control = 100;
                        lecturers[k].work("HomeworkTime");
                        if(uniControl){
                           uniControl =  research->setCont(lecturers[k].getName(),lecturers[k].getSurname(),0);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(lecturers[k].getName(),lecturers[k].getSurname(),0);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  technical->setCont(lecturers[k].getName(),lecturers[k].getSurname(),0);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                for(int k = 0; k < researchAssistants.size();k++){
                    if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                    {
                                                                         
                        researchAssistants[k].seeSuccessfulStudent();
                        control = 100;
                        researchAssistants[k].work("HomeworkTime");
                        if(uniControl){
                           uniControl =  research->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),0);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),0);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  technical->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),0);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                control++;
            }
            break;
            case academicPaper:     
            while(control < 100)
            {
                randomNumber = rand()%30;
                
                for(int k = 0; k < lecturers.size();k++){
                    if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                    {
                                                                         
                        lecturers[k].makePublish();
                        control = 100;
                        lecturers[k].work("HomeworkTime");
                        if(uniControl){
                           uniControl =  research->setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = linguistic->setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = technical->setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                for(int k = 0; k < researchAssistants.size();k++){
                    if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                    {
                                                                         
                        researchAssistants[k].makePublish();
                        control = 100;
                        researchAssistants[k].work("HomeworkTime");
                        if(uniControl){
                           uniControl =  research->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  technical->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),5);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                control++;
            }
            break;
            case administration:    
            while(control < 100)
            {
                randomNumber = rand()%30;
                for(int k = 0; k < officers.size();k++){
                    if(employees[randomNumber].getName().compare(officers[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(officers[k].getSurname())==0)
                    {
                                                                         
                        officers[k].manageProcess();
                        control = 100;
                        officers[k].work("HomeworkTime");
                        if(uniControl){
                           uniControl =  research->setCont(officers[k].getName(),officers[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(officers[k].getName(),officers[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                          uniControl =   technical->setCont(officers[k].getName(),officers[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                for(int k = 0; k < secretaries.size();k++){
                    if(employees[randomNumber].getName().compare(secretaries[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(secretaries[k].getSurname())==0)
                    {
                                                                         
                        secretaries[k].manageProcess();
                        control = 100;
                        secretaries[k].work("HomeworkTime");
                        if(uniControl){
                           uniControl =  research->setCont(secretaries[k].getName(),secretaries[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                            uniControl = linguistic->setCont(secretaries[k].getName(),secretaries[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  technical->setCont(secretaries[k].getName(),secretaries[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                control++;
            }
            break;
            case HomeworkTime:      
            while(control < 100)
            {
                randomNumber = rand()%30;
                for(int k = 0; k < lecturers.size();k++){
                    if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                    {
                                                                         
                        lecturers[k].giveHW();
                        control = 100;
                        lecturers[k].work("HomeworkTime");
                        if(uniControl){
                          uniControl =   research->setCont(lecturers[k].getName(),lecturers[k].getSurname(),1);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(lecturers[k].getName(),lecturers[k].getSurname(),1);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  technical->setCont(lecturers[k].getName(),lecturers[k].getSurname(),1);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                control++;
            }
            break;
            case homeworkTimeout:  
            while(control < 100)
            {
                randomNumber = rand()%30;
                for(int k = 0; k < researchAssistants.size();k++){
                    if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                    {
                                                                         
                        researchAssistants[k].readHW();
                        control = 100;
                        researchAssistants[k].work("homeworkTimeout");
                        if(uniControl){
                          uniControl =   research->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                          uniControl =   linguistic->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  technical->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),2);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                control++;
            }
            break;
            case incident:          
            while(control < 100)
            {
                randomNumber = rand()%30;
                for(int k = 0; k < secretaries.size();k++){
                    if(employees[randomNumber].getName().compare(secretaries[k].getName())==0 && 
                       employees[randomNumber].getSurname().compare(secretaries[k].getSurname())==0)
                    {
                                                                         
                        secretaries[k].receivePetition();
                        control = 100;
                        secretaries[k].work("incident");
                        if(uniControl){
                          uniControl =   research->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-1);
                           if(uniControl == 0)
                            cout << ", contribution of IYTE is " << research->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  linguistic->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-1);
                           if(uniControl == 0)
                            cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                        }
                        if(uniControl){
                           uniControl =  technical->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-1);
                           if(uniControl == 0)
                            cout << ", contribution of GTU is " << technical->getCont()<<endl;
                        }
                        break;
                    }
                }
                control++;
            }
            break;
            case solution:          
        while(control < 100)
        {
            randomNumber = rand()%30;
            for(int k = 0; k < officers.size();k++){
                if(employees[randomNumber].getName().compare(officers[k].getName())==0 && 
                   employees[randomNumber].getSurname().compare(officers[k].getSurname())==0)
                {
                                                                     
                    officers[k].submitPetition();
                    control = 100;
                    officers[k].work("solution");
                    if(uniControl){
                      uniControl =   research->setCont(officers[k].getName(),officers[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of IYTE is " << research->getCont() << endl;
                    }
                    if(uniControl){
                      uniControl =   linguistic->setCont(officers[k].getName(),officers[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                    }
                    if(uniControl){
                      uniControl =   technical->setCont(officers[k].getName(),officers[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of GTU is " << technical->getCont() << endl;
                    }
                    break;
                }
            }
            for(int k = 0; k < lecturers.size();k++){
                if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                   employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                {
                                                                     
                    lecturers[k].submitPetition();
                    control = 100;
                    lecturers[k].work("solution");
                    if(uniControl){
                       uniControl =  research->setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of IYTE is " << research->getCont() << endl;
                    }
                    if(uniControl){
                       uniControl =  linguistic->setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                    }
                    if(uniControl){
                      uniControl =   technical->setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of GTU is " << technical->getCont() << endl;
                    }
                    break;
                }
            }
            for(int k = 0; k < researchAssistants.size();k++){
                if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                   employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                {
                                                                     
                    researchAssistants[k].submitPetition();
                    control = 100;
                    researchAssistants[k].work("solution");
                    if(uniControl){
                       uniControl =  research->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of IYTE is " << research->getCont() << endl;
                    }
                    if(uniControl){
                      uniControl =   linguistic->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                    }
                    if(uniControl){
                       uniControl =  technical->setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of GTU is " << technical->getCont() << endl;
                    }
                    break;
                }
            }
            for(int k = 0; k < secretaries.size();k++){
                if(employees[randomNumber].getName().compare(secretaries[k].getName())==0 && 
                   employees[randomNumber].getSurname().compare(secretaries[k].getSurname())==0)
                {
                                                                     
                    secretaries[k].submitPetition();
                    control = 100;
                    secretaries[k].work("solution");
                    if(uniControl){
                       uniControl =  research->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of IYTE is " << research->getCont() << endl;
                    }
                    if(uniControl){
                       uniControl =  linguistic->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of BOGAZICI is " << linguistic->getCont() << endl;
                    }
                    if(uniControl){
                       uniControl =  technical->setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                       if(uniControl == 0)
                        cout << ", contribution of GTU  is " << technical->getCont() << endl;
                    }
                    break;
                }
            }
            control++;
        }
        break;
        }
    }   
    cout << "_______________________________________________________________________________\n\n";
    cout << "Contribution of GTU is   " << technical->getCont() << endl;
    cout << "Contribution of BOGAZICI is         " << linguistic->getCont() << endl;
    cout << "Contribution of IYTE is " << research->getCont() << endl;
}