
#include "lecturer.h"
#include "library.h"
#include <cstdlib> 
#include <ctime> 
/*read each line to Course's vector*/
Course file1(string line)
{
	Course newcourse;
	string dates;

	istringstream some_stream(line);
	  
	some_stream >> newcourse.id >> newcourse.name >> newcourse.code 
	     	    >> newcourse.credit >> newcourse.total_hours >> newcourse.field;
	newcourse.isAssign = 0;
	newcourse.isTimeArrange = 0;
	newcourse.isMandatory = 1;
	return newcourse;
}
/*read each line to Classroom's vector*/
Classroom file2(string line)
{
	Classroom newclass;
	
	istringstream some_stream(line);
	some_stream >> newclass.id >> newclass.c_no >> newclass.capacity;

	return newclass;
}
/*assign to struct course new propose courses*/
Course file1(string line,int id)
{
	Course newcourse;
	string dates,temp;

	istringstream some_stream(line);
	  
	some_stream >> temp >> temp >> newcourse.name >> newcourse.code 
	     	    >> newcourse.credit >> newcourse.total_hours >> newcourse.field;
	newcourse.isAssign = 0;
	newcourse.isTimeArrange = 0;
	newcourse.id = ++id;
	newcourse.isMandatory = 0;


	return newcourse;
}
/*check the courses*/
int isexist(vector<Course> courses,int lesson)
{
	int i(0);
	while (courses.size() > i++){
		if(courses[i].id == lesson )
			return i;
	}
		cout << "There is no COURSE which has this ID" << endl;
	return -1;
}
/*assign automatic*/
void assignCourse(vector<Course>& courses,vector<Lecturer>& lecturers)
{
	int mandatorySize = 0,controlFound=0;
	vector<string> fields,proffesions;
	string stringTemp;
	std::vector<int> fieldsSize,proffesionsSize;
	int intTemp;

	for (int i = 0; i < courses.size(); ++i)
	{
		if(courses[i].isMandatory == 1){
			for (int j = 0; j < fields.size(); ++j)
			{
				if(fields[j].compare(courses[i].field) == 0){
					fieldsSize[j]++;
					controlFound=1;
				}
			}
			if(controlFound == 0){
				fields.push_back(courses[i].field);
				fieldsSize.push_back(1);					
			}
			controlFound = 0;
		}
	}
	for(int i=0; i < lecturers.size();i++)
	{
		for(int j=0;j < lecturers[i].getProffesionsSize();++j)
		{
			for (int k = 0; k < proffesions.size(); ++k)
			{
				if(proffesions[k].compare(lecturers[i].getProffesions(j)) == 0)
				{
					proffesionsSize[k]++;
					controlFound=1;  

				}
			}
			if(controlFound == 0){

				proffesions.push_back(lecturers[i].getProffesions(j));
				proffesionsSize.push_back(1);					
			}
			controlFound = 0;
		}
	}
	for (int i = 1; i < proffesions.size(); ++i)
	{
		for (int j = 0; j < proffesions.size()-i; ++j)	
		{
			if(proffesionsSize[j] > proffesionsSize[j+1])
			{
				stringTemp.assign(proffesions[j]);
				proffesions[j].assign(proffesions[j+1]);
				proffesions[j+1].assign(stringTemp);
				intTemp=proffesionsSize[j];
				proffesionsSize[j]=proffesionsSize[j+1];
				proffesionsSize[j+1]=intTemp;			
			}
		}
	}
	for (int i = 0; i < proffesions.size(); ++i)
	{
		for (int j = 0; j < fields.size(); ++j)
		{
			if(proffesions[i].compare(fields[j]) == 0)
			{
				for (int k = 0; k < fieldsSize[j]; ++k)
				{
					int checkAssign=0,loopControl=0;
					int personalError = k;
					int cid;
					do{
						loopControl++;
						personalError = personalError % proffesionsSize[i];
						int pid = isexist(lecturers,proffesions[i],personalError);
						cid = isexist(courses,fields[j],k);
						checkAssign = lecturers[pid].assignCourse(courses[cid],checkAssign);
						personalError++;
					}while(checkAssign == 0 && courses[cid].isAssign == 0 && loopControl < fieldsSize[j]);	
					if(courses[cid].isAssign != 1){
						checkAssign=0;
						loopControl=0;
						personalError = k;
						do{
							loopControl++;
							personalError = personalError % proffesionsSize[i];
							int pid = isexist(lecturers,proffesions[i],personalError);
							checkAssign = lecturers[pid].assignCourse(courses[cid],checkAssign,loopControl);
							personalError++;
						}while(checkAssign == 0 && courses[cid].isAssign == 0 && loopControl < fieldsSize[j]);					
					}
				}
			}
		}
	}
	for (int i = 0; i < courses.size(); ++i)
	{
		if(courses[i].isAssign != 1)
			cerr << i <<" There is error somethings" << courses[i].isAssign << endl ;
	}
}
/*check and find courses index*/
int isexist(vector<Course> courses,string field,int which)
{
	int i(0),k=0;
	while(i++ < courses.size())
	{
		if(courses[i-1].field.compare(field) == 0)
		{
			if(k == which)
				return i-1;
			else k++;
		}
	}
	return -1;
}
/*check and find Classroom index*/
int isexist(vector<Classroom> classrooms,string classID)
{
		int i(0);
	while (classrooms.size() > i)
	{
		if(classrooms[i].c_no.compare(classID) == 0)
			return i;
		i++;
	}
		cout << "There is no CLASSROOM which has this ID" << endl;
	return -1;
}
/*check is all courses assigned?*/
int assignedAllCourse(vector<class Lecturer>& lecturer,vector<Course>& course)
{
	int i=0,mustAssign=0,j=0;
	while(i<lecturer.size())
	{
		if(lecturer[i].getLessonSize() < 3)
		{
			for (int j = 0; j < course.size(); ++j)
			{
				if(course[j].isMandatory == 0)
					lecturer[i].assignCourse(course[j],1);		
			}
		}
		i++;
	}
	return mustAssign;
}