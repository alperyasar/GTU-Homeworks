#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <ctime> 

#include "classroom.h"
#include "lecturer.h"   
#include "library.h"

using namespace std;

int main()
	{
    using ClassName :: Classroom;
	vector<Lecturer> lecturer;
    vector<Course> courses;
    vector<Classroom> classrooms; 
    string line,firstWord,classNO;			/*first check in file if courses or classrooms name*/
    int i=0,size(0),studentID,hourOfWeek,classID;
   

    srand(time(NULL));

    ifstream classFile,lecturerFile;
    classFile.open("courses_classrooms.txt");
    lecturerFile.open("lecturers.txt");
    /*read files Course and class*/
    if(!classFile)        cerr << "Open Faiulre" << endl;

	while(getline(classFile, line))
	{
	    if(i == 2)    							classrooms.push_back(Classroom(line) );
	    else if ( i == 1 && line[0] != 'C')    	courses.push_back(file(line));
	    else if(line[0] >= 'C') 				i++;
	}
	i = 0;												
        /*read lecturer information input from user */ 

    if(!lecturerFile)       
        cerr << "Open Faiulre" << endl;
    while(getline(lecturerFile,line))
    {
        ++size;
        lecturer.resize(size);
        lecturer[size-1].setLecturer(line);
    }
    int j=0;

    assignCourse(courses,lecturer);
    arrangeTimeTable(courses);
    arrangeClassroom(classrooms,courses);

    cerr << "--------------------LECTURER--------------------" << endl ;
    for (int i = 0; i < lecturer.size(); ++i)
    {  
        cout << lecturer[i] << endl;
    }
    
    cerr << "--------------------LECTURER--------------------" << endl ;
   /*loop until -o write information about Lecturer lessons*/
	do
	{

    	/*get information student*/
    	getline(cin,line);
    	istringstream some_stream(line);
		some_stream >> firstWord;
        if(firstWord.compare("-enter")==0)
        {                           
            some_stream >> studentID >> classNO >> hourOfWeek;
            for (int i = 0; i < classrooms.size(); ++i)
            {
                classID = classrooms[i].isexist(classNO);
                if(classID != -1)
                    break;
            }
            if(classID == -1)
                cerr << "ERROR: no class" << endl;
            else             
                
            if(controlStudent(courses,studentID,classrooms,hourOfWeek-1)){
                classrooms[classID].enterClass(studentID);
            }

        }
        else if (firstWord.compare("-quit") == 0)
        {
            some_stream >> studentID;
            if(controlStudent(studentID,classrooms)){

            }

        }
        else if(firstWord.compare("-attendance")==0)
        {
            int *newStudent,studentSize=0,*classNumber;
            for (int i = 0; i < classrooms.size(); ++i)
            {
                for (int j = 0; j < classrooms[i].getSTUDENTINROOM(); ++j)
                {
                    int control = 0;

                    for (int k = 0; k < studentSize; ++k)
                    {
                        if(classrooms[i].getSTUNDENTID(j) == newStudent[k]){
                            classNumber[k]++;
                            control = 1;
                        }
                    }
                    if(control == 0 && studentSize != 0){
                        int *temp,*tempclassNumber;
                        studentSize++;
                        temp = newStudent;
                        tempclassNumber = classNumber;
                        classNumber = new int[studentSize];
                        newStudent = new int[studentSize];
                        classNumber = tempclassNumber;
                        classNumber[studentSize-1] = 1;
                        newStudent = temp;
                        newStudent[studentSize-1] =classrooms[i].getSTUNDENTID(j); 
                    }
                    else{
                        studentSize++;
                        classNumber = new int[studentSize];
                        newStudent = new int[studentSize];
                        classNumber[studentSize-1] = 1;
                        newStudent[studentSize-1] =classrooms[i].getSTUNDENTID(j); 
                    }
                }
            }
            for (int i = 0; i < studentSize; ++i)
            {
                cout << "Student Number : " << newStudent[i] << " : " << classNumber[i] << " ";
            }
            cout << endl;
        }
    	
    	i=0;
    }while(firstWord.compare("exit")!=0);
    return 0;
}