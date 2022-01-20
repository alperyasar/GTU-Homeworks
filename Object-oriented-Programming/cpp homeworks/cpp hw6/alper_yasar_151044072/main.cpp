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
#include "university.cpp"
#include "complex.h"
#include "complex.cpp"
#include "yok.h"
#include "yok.cpp"

using namespace std;

enum Actions{ document, slackness, project, lesson, seminar, academicPaper,
              administration,HomeworkTime,homeworkTimeout,incident,solution };
enum jobs{ lecturer,officer,researchassistant,secretary};

enum UniversityNames{research,linguistic,technical};

int main(){

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
    YOK yok;
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
        some_stream >> name >> getSurname;
        employees.push_back( Employee(name,getSurname,++size));
        
    }
    University<int> research(0,"IYTE");
    University<double> linguistic(0,"BOGAZICI");
    Complex<int> complex;
    University<Complex<int>> technical(complex,"GTU");


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
        if(randomNumber == 0 && research.sizeEmployee() < 10){
            cout << "IYTE requests " << job<<endl;
            
            if(job.compare("officer") == 0){
                yok.giveJob(tempofficer,employees[i].getName(),employees[i].getSurname());
                officers.push_back(tempofficer);
            }
            else if(job.compare("researchassistant") == 0){
                yok.giveJob(tempresearchassistant,employees[i].getName(),employees[i].getSurname());
                researchAssistants.push_back(tempresearchassistant);
            }
            else if(job.compare("secretary") == 0){
                yok.giveJob(tempsecretary,employees[i].getName(),employees[i].getSurname());
                secretaries.push_back(tempsecretary);
            }
            else if(job.compare("lecturer") == 0){
                yok.giveJob(templecturer,employees[i].getName(),employees[i].getSurname());
                lecturers.push_back(templecturer);
            }
            research.giveJob(employees[i]);
            cout << "YOK give job to "<< employees[i].getName() << " " << employees[i].getSurname() << " as " << job << endl;
            control++;
        }
        else if(randomNumber == 1 && linguistic.sizeEmployee() < 10){
            cout << "BOGAZICI requests " << job<<endl;
            if(job.compare("officer") == 0){
                yok.giveJob(tempofficer,employees[i].getName(),employees[i].getSurname());
                officers.push_back(tempofficer);
            }
            else if(job.compare("researchassistant") == 0){
                yok.giveJob(tempresearchassistant,employees[i].getName(),employees[i].getSurname());
                researchAssistants.push_back(tempresearchassistant);
            }
            else if(job.compare("secretary") == 0){
                yok.giveJob(tempsecretary,employees[i].getName(),employees[i].getSurname());
                secretaries.push_back(tempsecretary);
            }
            else if(job.compare("lecturer") == 0){
                yok.giveJob(templecturer,employees[i].getName(),employees[i].getSurname());
                lecturers.push_back(templecturer);
            }
            linguistic.giveJob(employees[i]);
            cout << "YOK give job to "<< employees[i].getName() << " " << employees[i].getSurname() << " as " << job << endl;
            control++;
        }
        else if(randomNumber == 2 && technical.sizeEmployee() < 10){
            cout << "GTU requests " << job<<endl;
            if(job.compare("officer") == 0){
                yok.giveJob(tempofficer,employees[i].getName(),employees[i].getSurname());
                officers.push_back(tempofficer);
            }
            else if(job.compare("researchassistant") == 0){
                yok.giveJob(tempresearchassistant,employees[i].getName(),employees[i].getSurname());
                researchAssistants.push_back(tempresearchassistant);
            }
            else if(job.compare("secretary") == 0){
                yok.giveJob(tempsecretary,employees[i].getName(),employees[i].getSurname());
                secretaries.push_back(tempsecretary);
            }
            else if(job.compare("lecturer") == 0){
                yok.giveJob(templecturer,employees[i].getName(),employees[i].getSurname());
                lecturers.push_back(templecturer);
            }     
            technical.giveJob(employees[i]);
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
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        for(int k = 0; k < officers.size();k++){
                                            if(employees[randomNumber].getName().compare(officers[k].getName())==0 && employees[randomNumber].getSurname().compare(officers[k].getSurname())==0)
                                            {                                             
                                                officers[k].makeDoc();
                                                check = 0;
                                                cout << officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout <<" have document. Therefore, " << officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout << " make Document. Happiness of "<< officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout <<" is " << officers[k].getHappinies();
                                                if(uniControl){
                                                    uniControl = research.setCont(officers[k].getName(),officers[k].getSurname(),3);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = linguistic.setCont(officers[k].getName(),officers[k].getSurname(),3);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = technical.setCont(officers[k].getName(),officers[k].getSurname(),3);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        control++;
                                    }
                                    break;
            case slackness:         
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        for(int k = 0; k < officers.size();k++){
                                            if(employees[randomNumber].getName().compare(officers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(officers[k].getSurname())==0)
                                            {
                                                                                                 
                                                officers[k].drinkTea();
                                                check = 0;
                                                cout << officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout <<" have slackness. Therefore, " << officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout << " drinks tea. Happiness of "<< officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout <<" is " << officers[k].getHappinies();
                                                if(uniControl){
                                                    uniControl = research.setCont(officers[k].getName(),officers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = linguistic.setCont(officers[k].getName(),officers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = technical.setCont(officers[k].getName(),officers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < lecturers.size();k++){
                                            if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                                            {
                                                                                                 
                                                lecturers[k].drinkTea();
                                                check = 0;
                                                cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" have slackness. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout << " drinks tea. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" is " << lecturers[k].getHappinies();
                                                if(uniControl){
                                                    uniControl = research.setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = linguistic.setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = technical.setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < researchAssistants.size();k++){
                                            if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                                            {
                                                                                                 
                                                researchAssistants[k].drinkTea();
                                                check = 0;
                                                cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" have slackness. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout << " drinks tea. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" is " << researchAssistants[k].getHappinies();
                                                if(uniControl){
                                                    uniControl = research.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = linguistic.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = technical.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < secretaries.size();k++){
                                            if(employees[randomNumber].getName().compare(secretaries[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(secretaries[k].getSurname())==0)
                                            {
                                                                                                 
                                                secretaries[k].drinkTea();
                                                check = 0;
                                                cout << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout <<" have slackness. Therefore, " << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout << " drinks tea. Happiness of "<< secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout <<" is " << secretaries[k].getHappinies();
                                                if(uniControl){
                                                    uniControl = research.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = technical.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }                                  
                                        control++;
                                    }
                                    break;
            case project:           
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                       
                                        for(int k = 0; k < researchAssistants.size();k++){
                                            if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                                            {
                                                                                                 
                                                researchAssistants[k].research();
                                                check = 0;
                                                cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" have project. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout << " research. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" is " << researchAssistants[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),4);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),4);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = technical.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),4);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }  
                                        control++;
                                    }
                                    break;
            case lesson:            
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        for(int k = 0; k < lecturers.size();k++){
                                            if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                                            {
                                                                                                 
                                                lecturers[k].giveLesson();
                                                check = 0;
                                                cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" have lesson. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout << " give lesson. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" is " << lecturers[k].getHappinies();
                                                if(uniControl){
                                                  uniControl =   research.setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = technical.setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        control++;
                                    }
                                    break;
            case seminar:           
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        
                                        for(int k = 0; k < lecturers.size();k++){
                                            if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                                            {
                                                                                                 
                                                lecturers[k].seeSuccessfulStudent();
                                                check = 0;
                                                cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" have seminar. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout << " see successful student. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" is " << lecturers[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(lecturers[k].getName(),lecturers[k].getSurname(),0);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(lecturers[k].getName(),lecturers[k].getSurname(),0);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(lecturers[k].getName(),lecturers[k].getSurname(),0);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < researchAssistants.size();k++){
                                            if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                                            {
                                                                                                 
                                                researchAssistants[k].seeSuccessfulStudent();
                                                check = 0;
                                                cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" have seminar. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout << " see successful student. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" is " << researchAssistants[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),0);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),0);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),0);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        control++;
                                    }
                                    break;
            case academicPaper:     
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        
                                        for(int k = 0; k < lecturers.size();k++){
                                            if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                                            {
                                                                                                 
                                                lecturers[k].makePublish();
                                                check = 0;
                                                cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" have academic paper. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout << " make publish. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" is " << lecturers[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = linguistic.setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = technical.setCont(lecturers[k].getName(),lecturers[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < researchAssistants.size();k++){
                                            if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                                            {
                                                                                                 
                                                researchAssistants[k].makePublish();
                                                check = 0;
                                                cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" have academic paper. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout << " make publish. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" is " << researchAssistants[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),5);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        control++;
                                    }
                                    break;
            case administration:    
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        for(int k = 0; k < officers.size();k++){
                                            if(employees[randomNumber].getName().compare(officers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(officers[k].getSurname())==0)
                                            {
                                                                                                 
                                                officers[k].manageProcess();
                                                check = 0;
                                                cout << officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout <<" have administration. Therefore, " << officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout << " drinks tea. Happiness of "<< officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout <<" is " << officers[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(officers[k].getName(),officers[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(officers[k].getName(),officers[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                  uniControl =   technical.setCont(officers[k].getName(),officers[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < secretaries.size();k++){
                                            if(employees[randomNumber].getName().compare(secretaries[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(secretaries[k].getSurname())==0)
                                            {
                                                                                                 
                                                secretaries[k].manageProcess();
                                                check = 0;
                                                cout << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout <<" have administration. Therefore, " << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout << " manage process. Happiness of "<< secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout <<" is " << secretaries[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(secretaries[k].getName(),secretaries[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                    uniControl = linguistic.setCont(secretaries[k].getName(),secretaries[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(secretaries[k].getName(),secretaries[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        control++;
                                    }
                                    break;
            case HomeworkTime:      
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        for(int k = 0; k < lecturers.size();k++){
                                            if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                                            {
                                                                                                 
                                                lecturers[k].giveHW();
                                                check = 0;
                                                cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" have homework time. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout << " give homework. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" is " << lecturers[k].getHappinies();
                                                if(uniControl){
                                                  uniControl =   research.setCont(lecturers[k].getName(),lecturers[k].getSurname(),1);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(lecturers[k].getName(),lecturers[k].getSurname(),1);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(lecturers[k].getName(),lecturers[k].getSurname(),1);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        control++;
                                    }
                                    break;
            case homeworkTimeout:  
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        for(int k = 0; k < researchAssistants.size();k++){
                                            if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                                            {
                                                                                                 
                                                researchAssistants[k].readHW();
                                                check = 0;
                                                cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" have homework timeout. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout << " read homework. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" is " << researchAssistants[k].getHappinies();
                                                if(uniControl){
                                                  uniControl =   research.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                  uniControl =   linguistic.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        control++;
                                    }
                                    break;
            case incident:          
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        for(int k = 0; k < secretaries.size();k++){
                                            if(employees[randomNumber].getName().compare(secretaries[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(secretaries[k].getSurname())==0)
                                            {
                                                                                                 
                                                secretaries[k].receivePetition();
                                                check = 0;
                                                cout << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout <<" have incident. Therefore, " << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout << " receive petition. Happiness of "<< secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout <<" is " << secretaries[k].getHappinies();
                                                if(uniControl){
                                                  uniControl =   research.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-1);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-1);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-1);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont()<<endl;
                                                }
                                                break;
                                            }
                                        }
                                        control++;
                                    }
                                    break;
            case solution:          
                                    while(check && control < 100)
                                    {
                                        randomNumber = rand()%30;
                                        for(int k = 0; k < officers.size();k++){
                                            if(employees[randomNumber].getName().compare(officers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(officers[k].getSurname())==0)
                                            {
                                                                                                 
                                                officers[k].submitPetition();
                                                check = 0;
                                                cout << officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout <<" have solution. Therefore, " << officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout << " submit petition. Happiness of "<< officers[k].getName() << " " << officers[k].getSurname() ;
                                                cout <<" is " << officers[k].getHappinies();
                                                if(uniControl){
                                                  uniControl =   research.setCont(officers[k].getName(),officers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                  uniControl =   linguistic.setCont(officers[k].getName(),officers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                  uniControl =   technical.setCont(officers[k].getName(),officers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont() << endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < lecturers.size();k++){
                                            if(employees[randomNumber].getName().compare(lecturers[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(lecturers[k].getSurname())==0)
                                            {
                                                                                                 
                                                lecturers[k].submitPetition();
                                                check = 0;
                                                cout << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" have solution. Therefore, " << lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout << " submit petition. Happiness of "<< lecturers[k].getName() << " " << lecturers[k].getSurname() ;
                                                cout <<" is " << lecturers[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                  uniControl =   technical.setCont(lecturers[k].getName(),lecturers[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont() << endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < researchAssistants.size();k++){
                                            if(employees[randomNumber].getName().compare(researchAssistants[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(researchAssistants[k].getSurname())==0)
                                            {
                                                                                                 
                                                researchAssistants[k].submitPetition();
                                                check = 0;
                                                cout << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" have solution. Therefore, " << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout << " submit petition. Happiness of "<< researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() ;
                                                cout <<" is " << researchAssistants[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                  uniControl =   linguistic.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(researchAssistants[k].getName(),researchAssistants[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont() << endl;
                                                }
                                                break;
                                            }
                                        }
                                        for(int k = 0; k < secretaries.size();k++){
                                            if(employees[randomNumber].getName().compare(secretaries[k].getName())==0 && 
                                               employees[randomNumber].getSurname().compare(secretaries[k].getSurname())==0)
                                            {
                                                                                                 
                                                secretaries[k].submitPetition();
                                                check = 0;
                                                cout << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout <<" have solution. Therefore, " << secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout << " submit petition. Happiness of "<< secretaries[k].getName() << " " << secretaries[k].getSurname() ;
                                                cout <<" is " << secretaries[k].getHappinies();
                                                if(uniControl){
                                                   uniControl =  research.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  linguistic.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Bogaizici University is " << linguistic.getCont() << endl;
                                                }
                                                if(uniControl){
                                                   uniControl =  technical.setCont(secretaries[k].getName(),secretaries[k].getSurname(),-2);
                                                   if(uniControl == 0)
                                                    cout << ", contribution of Gebze Technical University is " << technical.getCont() << endl;
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
    cout << "Contribution of Gebze Technical University is   " << technical.getCont() << endl;
    cout << "Contribution of Bogaizici University is         " << linguistic.getCont() << endl;
    cout << "Contribution of Izmir Instutiy of Technoloji is " << research.getCont() << endl;

}