#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "lecturer.h"

using namespace std;

struct Date{
	string day;
	int beginLesson;
	int endLesson;
	string classroom;
};
struct Classroom{
	int id;
	string c_no;
	int capacity,student_inroom;
};
struct Course{
	int id,code,isAssign,isTimeArrange;
	string name,field;
	int credit,total_hours,isMandatory;
	vector<Date> dates;
};

Course file1(string line);
Classroom file2(string line);
Course file1(string line,int id);
int isexist(const vector<Course> courses,const int lesson);		/*if course   id does not exit return false else return number*/
int isexist(const vector<Course> courses,const string field,const int which);
int isexist(vector<Classroom> classrooms,string classID);
void assignCourse(vector<Course>& courses, vector<class Lecturer>& lecturers);
int assignedAllCourse(vector<class Lecturer>& lecturer,vector<Course>& course);

Date day(int hour);
int isexist(vector<Lecturer> lecturer,int id);		/*if lecturer id does not exit return false else return number*/
int isexist(vector<Lecturer> lecturer,string proffesions,int which);

#endif