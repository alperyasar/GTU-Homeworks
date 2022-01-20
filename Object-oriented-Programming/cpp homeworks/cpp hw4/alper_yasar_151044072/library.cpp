
#include "lecturer.h"
#include "library.h"
#include "classroom.h"

#include <cstdlib> 
#include <ctime> 
/*read each line to Course's vector*/
Course file(string line)
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
/*read each line to Classroom's vector*
/*assign to struct course new propose courses*/
Course file(string line,int id)
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
void printLesson(vector<Course> courses)
{
	for (int i = 0; i < courses.size(); ++i){
		cout << courses[i].id << " " << courses[i].name << " "<< courses[i].code<< " " << courses[i].credit<< " " << courses[i].total_hours;
		cout << " " << " "<< courses[i].field << endl;
	}
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
int isexist(vector<Lecturer> lecturer,string proffesions,int which)		/*if lecturer id does not exit return false else return number*/
{
	int i(0),k=0;

	while(i++ < lecturer.size())
	{
		for(int j=0;j<lecturer[i-1].getProffesionsSize(); j++)
		{
			if(lecturer[i-1].getProffesions(j).compare(proffesions) == 0)
			{
				if(k == which){
					return i-1;
				}
				else k++;
			}
		}
	}
	return -1;
}
/*check and find Classroom index*/

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
void arrangeTimeTable(vector<Course>& course)
{
	int cid=0,numberOfDays;

	while(cid<course.size())
	{
		if(!(course[cid].dates.size() > 0))
		{
			if(course[cid].total_hours % 2 == 0)
				numberOfDays = course[cid].total_hours/2;
			else numberOfDays = (course[cid].total_hours+1) /2;

			for (int i = 0; i < numberOfDays; ++i)
			{
				if(i == (numberOfDays-1) && (numberOfDays%2) == 1)
					course[cid].dates.push_back(day(1));
				else
					course[cid].dates.push_back(day(2));

				for (int j = 0; j < course[cid].dates.size()-1; ++j)
				{
					if(course[cid].dates[i].day.compare(course[cid].dates[j].day) == 0){
						course[cid].dates.erase(course[cid].dates.begin()+i);
						i--;
					}
				}
			}
		}
		/*cout << "("<< course[cid].id <<")" << course[cid].name <<" ";
		int j;
		for (j = 0; j < course[cid].dates.size()-1; ++j)
		{
			cout << course[cid].dates[j].day << "_" << course[cid].dates[j].beginLesson <<"-" << course[cid].dates[j].endLesson << ",";
		}
			cout << course[cid].dates[j].day << "_" << course[cid].dates[j].beginLesson <<"-" << course[cid].dates[j].endLesson << endl;*/
		cid++;
	}
}
/*choose random day and hours for courses*/
Date day(int hour)
{
	string days[5] = {"MON","TUE","WED","THU","FRI"};
	int i;
	Date day;
	i = rand()%5;
	day.day.assign(days[i]);
	day.beginLesson = (rand()%6) + 9;
	day.endLesson = day.beginLesson + hour;

	return day;
}
/*assign all course to classes*/
void arrangeClassroom(vector<Classroom>& classrooms,vector<Course>& course)
{
	cerr << "--------------------COURSES--------------------" << endl ;
	for (int i = 0; i < course.size(); ++i)
	{	
		if(course[i].dates[0].classroom.compare("") == 0)
		{
			for(int l = 0; l < course[i].dates.size(); ++l)
			{
				int randomNumber = rand() % classrooms.size();
				course[i].dates[l].classroom.assign(classrooms[randomNumber].getC_NO());
				for(int j = 0; j < course.size(); ++j)
				{
					for (int k = 0; k < course[j].dates.size(); ++k)
					{
						if(course[j].dates[k].classroom.compare(course[i].dates[l].classroom) == 0 && i != j)
						{
							if(course[j].dates[k].day.compare(course[i].dates[l].day) == 0 && 
							  (course[j].dates[k].beginLesson == course[i].dates[l].beginLesson || course[j].dates[k].endLesson == course[i].dates[l].endLesson)){
								j = course.size();
								k = course[j].dates.size();
								l--;
							}
						}
					}
				}
			}
		}
	}
	
	for (int i = 0; i < course.size(); ++i)
	{	
		cout << "("<< course[i].id <<")" << course[i].name <<" ";
		for(int l = 0; l < course[i].dates.size(); ++l)
		{
			cout << "in " << course[i].dates[l].classroom << " at ";
			cout << course[i].dates[l].day << "_" << course[i].dates[l].beginLesson <<"-" << course[i].dates[l].endLesson;
			if(l!= course[i].dates.size()-1)
				cout << ", ";
		}
		cout << endl;
	}
	cerr << "--------------------COURSES--------------------" << endl ;
}
int controlStudent(int studentID,vector<class Classroom>& classrooms){
	for (int i = 0; i < classrooms.size(); ++i)
	{
		classrooms[i].quitClass(studentID);
	}
}

int controlStudent(vector<Course>& course,int studentID,vector<class Classroom>& classrooms,int hourOfWeek){
	string day,className;
	day = date(hourOfWeek);

	
	hourOfWeek = (hourOfWeek%8) + 9;

	int stundentInLesson=0;
	for (int i = 0; i < course.size(); ++i)
	{	

		className.assign(compareDate(course[i],day,hourOfWeek));
		if(className.compare("-1")!= 0)
		{
			for (int j = 0; j < classrooms.size(); ++j)
			{
				if(classrooms[j].getC_NO().compare(className) == 0)
				{
					stundentInLesson = classrooms[j].studentInroom(studentID);
					if(stundentInLesson){
						cerr << "BLOCK: s/he is at another classroom" << endl;
						return 0;
					}
				}
			}
		}
	}
	return 1;
}
string compareDate(Course course,string day,int hourOfWeek){
	
	for (int k = 0; k < course.dates.size(); ++k)
	{	
		if(course.dates[k].day.compare(day) == 0 && (course.dates[k].beginLesson <= hourOfWeek && course.dates[k].endLesson >= hourOfWeek ))
		{
			return course.dates[k].classroom;
		}
	}

	return "-1";
}
string date(int hour)
{
	string days[5] = {"MON","TUE","WED","THU","FRI"};
	int i;
	i = hour/8;

	return days[i];
}/*
controlStudent(int studentID,int hourOfWeek){
	
}*/
int isexist(vector<class Classroom> classrooms,string classID)		/*if lecturer id does not exit return false else return number*/
{
	int i(0);
	while (classrooms.size() > i)
	{
		if(classrooms[i].getC_NO().compare(classID) == 0)
			return i;
		i++;
	}
		cout << "There is no CLASSROOM which has this ID" << endl;
	return -1;
}