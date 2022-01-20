#include "communisteducation.h"
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

Communist::Communist(){
  research=new University<int>(0,"IYTE");
  linguistic=new University<double>(0,"BOGAZICI");
  technical=new University<complex<int>>("GTU");

}

template<class T>
void Communist::giveJob(T& employee,string name,string surname){
	employee.setNameSurname(name,surname);
	cout << employee.getName() << employee.getSurname() << " ";	
}
template<class U>
bool Communist::foundUni(University<U> uni,string uniName){
	return(uniName.compare(uni.getName()));
}

enum Actions{ document, slackness, project, lesson, seminar, academicPaper,
              administration,HomeworkTime,homeworkTimeout,incident,solution };


void Communist::process(){
    vector<Secretary> secretaries;
    vector<ResearchAssistant> researchAssistants;
    vector<Officer> officers;
    vector<Lecturer> lecturers;
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
        some_stream >>  name >> getSurname >> job;
        int a = rand()%4;
        if(a == 0){
            lecturers.push_back( Lecturer(name,getSurname,++size));
        }
        else if(a == 1){
            officers.push_back( Officer(name,getSurname,++size));
        }
        else if(a == 2){
            researchAssistants.push_back( ResearchAssistant(name,getSurname,++size));
        }
        else if(a == 3){
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

    University<int> GebzeTechnicalUniversity;
    cout << "_____________________________________________________\n" << endl;
    int i;
    for (i = 0; i < 10; ++i)
    {
        for (int k = 0; k < lecturers.size(); ++k)
        {
            if(lecturers[k].getPid() == counter[i]){
            //    lecturers[k].setUniversity(GebzeTechnicalUniversity);
                cout << i+1 << " " << lecturers[k].getName() << " " << lecturers[k].getSurname() << " selected by Gebze Technical University\n";
            }
        }
        for (int k = 0; k < officers.size(); ++k)
        {
            if(officers[k].getPid() == counter[i]){
         //       officers[k].setUniversity(GebzeTechnicalUniversity);
                cout << i+1 << " "  << officers[k].getName() << " " << officers[k].getSurname() << " selected by Gebze Technical University\n";
            }
        }
        for (int k = 0; k < researchAssistants.size(); ++k)
        {
            if(researchAssistants[k].getPid() == counter[i]){
         //       researchAssistants[k].setUniversity(GebzeTechnicalUniversity);
                cout << i+1 << " "  << researchAssistants[k].getName() << " " << researchAssistants[k].getSurname() << " selected by Gebze Technical University\n";
            }
        }
        for (int k = 0; k < secretaries.size(); ++k)
        {
            if(secretaries[k].getPid() == counter[i]){
            //    secretaries[k].setUniversity(GebzeTechnicalUniversity);
                cout << i+1 << " "  << secretaries[k].getName() << " " << secretaries[k].getSurname() << " selected by Gebze Technical University\n";
            }
        
        }
    }
    cout << "_____________________________________________________\n" <<  endl;

    /*write story*/ 
    int officersSize=0,lecturersSize=0,researchAssistantsSize=0,secretariesSize=0;
   for (int i = 0; i < 12; ++i)
    {
        int randomActions = rand() % 11,done=0;
        int randomNumber,check=1,control=0,uniControl=1;
        switch(randomActions)
        {
            case document:          
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
	                	for(int k = 0; k < officers.size() && officersSize < 4;k++){
	                    	if(officers[k].getPid() == counter[j])
		                    {                                             
		                        officers[k].makeDoc();
		                        control = 100;
		                        officers[k].work("document");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(3);
		                        officers[k].setMoney(3);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
	                	}
                	}
                }
                control++;
            }
            break;
            case slackness:         
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < officers.size() && officersSize < 4;k++){
		                    if(officers[k].getPid() == counter[j])
		                    {
		                                                                         
		                        officers[k].drinkTea();
		                        control = 100;
		                        officers[k].work("slackness");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(-2);
		                        officers[k].setMoney(-2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < lecturers.size() && lecturersSize < 4;k++){
		                    if(lecturers[k].getPid() == counter[j])
		                    {
		                                                                         
		                        lecturers[k].drinkTea();
		                        control = 100;
		                        lecturers[k].work("slackness");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(-2);
		                        lecturers[k].setMoney(-2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < researchAssistants.size() && researchAssistantsSize < 4;k++){
		                    if(researchAssistants[k].getPid() == counter[j])
		                    {
		                                                                         
		                        researchAssistants[k].drinkTea();
		                        control = 100;
		                        researchAssistants[k].work("slackness");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(-2);
		                        researchAssistants[k].setMoney(-2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < secretaries.size() && secretariesSize < 4;k++){
		                    if(secretaries[k].getPid() == counter[j])
		                    {
		                                                                         
		                        secretaries[k].drinkTea();
		                        control = 100;
		                        secretaries[k].work("slackness");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(-2);
		                        secretaries[k].setMoney(-2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                } 
			        }
			    }                                 
                control++;
            }
            break;
            case project:           
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < researchAssistants.size() && researchAssistantsSize < 4;k++){
		                    if(researchAssistants[k].getPid() == counter[j])
		                    {
		                                                                         
		                        researchAssistants[k].research();
		                        control = 100;
		                        researchAssistants[k].work("project");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(4);
		                        researchAssistants[k].setMoney(4);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }  
			        }
			    }
                control++;
            }
            break;
            case lesson:            
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < lecturers.size() && lecturersSize < 4;k++){
		                    if(lecturers[k].getPid() == counter[j])
		                    {
		                                                                         
		                        lecturers[k].giveLesson();
		                        control = 100;
		                       lecturers[k].work("lesson");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(5);
		                        lecturers[k].setMoney(5);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                control++;
            }
            break;
            case seminar:           
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < lecturers.size() && lecturersSize < 4;k++){
		                    if(lecturers[k].getPid() == counter[j])
		                    {
		                                                                         
		                        lecturers[k].seeSuccessfulStudent();
		                        control = 100;
		                        lecturers[k].work("seminar");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(0);
		                        lecturers[k].setMoney(0);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < researchAssistants.size() && researchAssistantsSize < 4;k++){
		                    if(researchAssistants[k].getPid() == counter[j])
		                    {
		                                                                         
		                        researchAssistants[k].seeSuccessfulStudent();
		                        control = 100;
		                        researchAssistants[k].work("seminar");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(0);
		                        researchAssistants[k].setMoney(0);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                control++;
            }
            break;
            case academicPaper:     
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < lecturers.size() && lecturersSize < 4;k++){
		                    if(lecturers[k].getPid() == counter[j])
		                    {
		                                                                         
		                        lecturers[k].makePublish();
		                        control = 100;
		                        lecturers[k].work("academicPaper");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(5);
		                        lecturers[k].setMoney(5);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < researchAssistants.size() && researchAssistantsSize < 4;k++){
		                    if(researchAssistants[k].getPid() == counter[j])
		                    {
		                                                                         
		                        researchAssistants[k].makePublish();
		                        control = 100;
		                        researchAssistants[k].work("academicPaper");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(5);
		                        researchAssistants[k].setMoney(5);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                control++;
            }
            break;
            case administration:    
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < officers.size() && officersSize < 4;k++){
		                    if(officers[k].getPid() == counter[j])
		                    {
		                                                                         
		                        officers[k].manageProcess();
		                        control = 100;
		                        officers[k].work("administration");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(2);
		                        officers[k].setMoney(2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < secretaries.size() && secretariesSize < 4;k++){
		                    if(secretaries[k].getPid() == counter[j])
		                    {
		                                                                         
		                        secretaries[k].manageProcess();
		                        control = 100;
		                        secretaries[k].work("administration");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(2);
		                        secretaries[k].setMoney(2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                control++;
            }
            break;
            case HomeworkTime:      
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < lecturers.size() && lecturersSize < 4;k++){
		                    if(lecturers[k].getPid() == counter[j])
		                    {
		                                                                         
		                        lecturers[k].giveHW();
		                        control = 100;
		                        lecturers[k].work("HomeworkTime");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(1);
		                        lecturers[k].setMoney(1);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                control++;
            }
            break;
            case homeworkTimeout:  
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < researchAssistants.size() && researchAssistantsSize < 4;k++){
		                    if(researchAssistants[k].getPid() == counter[j])
		                    {
		                                                                         
		                        researchAssistants[k].readHW();
		                        control = 100;
		                        researchAssistants[k].work("homeworkTimeout");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(2);
		                        researchAssistants[k].setMoney(2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
                control++;
            }
            break;
            case incident:          
            while(control < 100)
            {
                randomNumber = rand()%30;
                for (int j = 0; j < counter.size(); ++j)
                {
                    if(counter[j] == randomNumber)
                    {
		                for(int k = 0; k < secretaries.size() && secretariesSize < 4;k++){
		                    if(secretaries[k].getPid() == counter[j])
		                    {
		                                                                         
		                        secretaries[k].receivePetition();
		                        control = 100;
		                        secretaries[k].work("incident");
		                        done = 1;
		                        GebzeTechnicalUniversity.setContribution(-1);
		                        secretaries[k].setMoney(-1);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
		                        break;
		                    }
		                }
			        }
			    }
		                control++;
		    }
            break;
            case solution:          
	        while(control < 100)
	        {
	            randomNumber = rand()%30;
	                for (int j = 0; j < counter.size(); ++j)
	                {
	                    if(counter[j] == randomNumber)
	                    {
				            for(int k = 0; k < officers.size() && officersSize < 4;k++){
				                if(officers[k].getPid() == counter[j])
				                {
				                                                                     
				                    officers[k].submitPetition();
				                    control = 100;
				                    officers[k].work("solution");
				                        done = 1;
			                        GebzeTechnicalUniversity.setContribution(-2);
		                        officers[k].setMoney(-2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
				                    break;
				                }
				            }
				        }
				    }
	                for (int j = 0; j < counter.size(); ++j)
	                {
	                    if(counter[j] == randomNumber)
	                    {
				            for(int k = 0; k < lecturers.size() && lecturersSize < 4;k++){
				                if(lecturers[k].getPid() == counter[j])
				                {
				                                                                     
				                    lecturers[k].submitPetition();
				                    control = 100;
				                    lecturers[k].work("solution");
				                        done = 1;
			                        GebzeTechnicalUniversity.setContribution(-2);
		                        	lecturers[k].setMoney(-2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
				                    break;
				                }
				            }
				        }
				    }
	                for (int j = 0; j < counter.size(); ++j)
	                {
	                    if(counter[j] == randomNumber)
	                    {
				            for(int k = 0; k < researchAssistants.size() && researchAssistantsSize < 4;k++){
				                if(researchAssistants[k].getPid() == counter[j])
				                {
				                                                                     
				                    researchAssistants[k].submitPetition();
				                    control = 100;
				                    researchAssistants[k].work("solution");
				                        done = 1;
			                        GebzeTechnicalUniversity.setContribution(-2);
		                        	researchAssistants[k].setMoney(-2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
				                    break;
				                }
				            }
				        }
				    }
	                for (int j = 0; j < counter.size(); ++j)
	                {
	                    if(counter[j] == randomNumber)
	                    {
				            for(int k = 0; k < secretaries.size() && secretariesSize < 4;k++){
				                if(secretaries[k].getPid() == counter[j])
				                {
				                                                                     
				                    secretaries[k].submitPetition();
				                    control = 100;
				                    secretaries[k].work("solution");
				                        done = 1;
			                        GebzeTechnicalUniversity.setContribution(-2);
		                        	secretaries[k].setMoney(-2);
		                        cout << ". Contribution of GTU is "<< GebzeTechnicalUniversity.getCont()<<endl;
				                    break;
				                }
				            }
				        }
				    }
	            control++;
	        }
	        break;
	        }
        if(done != 1)
        	i--;
    }   
    cout << "\n_____________________________________________________\n";
    cout << "Total contribution of Gebze Technical University is : " << GebzeTechnicalUniversity.getCont()<<endl;

}