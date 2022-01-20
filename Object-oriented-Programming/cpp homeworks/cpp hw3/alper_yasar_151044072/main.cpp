#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <ctime> 

#include "administrator.h"
#include "library.h"
#include "lecturer.h"

using namespace std;

int main()
{
    Administrator admin;
	vector<Lecturer> lecturer;
    vector<Course> courses;
    vector<Classroom> classrooms; 
    string line,firstWord,classID;			/*first check in file if courses or classrooms name*/
    int i=0,size(0),pid,courseID;
    int autoAssign;

    srand(time(NULL));

    ifstream classFile,lecturerFile;
    classFile.open("courses_classrooms.txt");
    lecturerFile.open("lecturers.txt");
    /*read files Course and class*/
    if(!classFile)        cerr << "Open Faiulre" << endl;

	while(getline(classFile, line))
	{
	    if(i == 2)    							classrooms.push_back(file2(line));
	    else if ( i == 1 && line[0] != 'C')    	courses.push_back(file1(line));
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
   /*loop until -o write information about Lecturer lessons*/
	do
	{
    	/*get information student*/
    	getline(cin,line);
    	istringstream some_stream(line);
		some_stream >> firstWord;
    	if(firstWord.compare("-propose")==0)
    	{							
    		some_stream >> pid;
    		pid = isexist(lecturer,pid);
    		courses.push_back(file1(line,courses.size()));
    		if(pid != -1)
    			lecturer[pid].proposeCourse(line,courses[courses.size()-1]);
    	}
    	else if (firstWord.compare("-assign") == 0)
    	{
    		some_stream >> pid >> courseID;
    		if(line.compare("-assign") == 0)
    		{
	    		assignCourse(courses,lecturer);
	    		autoAssign = assignedAllCourse(lecturer,courses);
    		}
	    	else
	    	{
	    		courseID = isexist(lecturer,courseID);
	    		pid = isexist(lecturer,pid);
		    	if(courseID != -1 && pid != -1)
		    		lecturer[pid].assignCourse(courses[courseID]); 	
	    	}
    	}
    	else if(firstWord.compare("-timetable")==0)
    	{
    		some_stream  >> courseID;
    		if(line.compare("-timetable") == 0)
	    		admin.arrangeTimeTable(courses);
	    	else
	    	{
		    	admin.arrangeTimeTable(courses,courseID);
	    	}    		
    	}
       	else if(firstWord.compare("-arrangeC")==0)
       	{
       	   	some_stream >> courseID >> classID;
       	   	if(line.compare("-arrangeC") == 0)
	    		admin.arrangeClassroom(classrooms,courses);
	    	else
	    	{
	    		courseID = isexist(lecturer,courseID);
	    		if(courseID != -1)
			    	admin.arrangeClassroom(classrooms,courses,courseID,classID);
	    	}  
    	}
    	else if(firstWord.compare("exit")==0){
		   autoAssign = assignedAllCourse(lecturer,courses);
    	}
    	i=0;
    }while(firstWord.compare("exit")!=0 || autoAssign != 0);
    return 0;
}