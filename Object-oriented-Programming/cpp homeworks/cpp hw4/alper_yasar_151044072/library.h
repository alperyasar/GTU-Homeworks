#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "classroom.h"
#include "lecturer.h"

using namespace std;

struct Date{
	string day;
	int beginLesson;
	int endLesson;
	string classroom;
};
struct Course{
	int id,code,isAssign,isTimeArrange;
	string name,field;
	int credit,total_hours,isMandatory;
	vector<Date> dates;
};
/*read*/
Course file(string line);
Course file(string line,int id);
/*assign day*/
Date day(int hour);
void assignCourse(vector<Course>& courses, vector<class Lecturer>& lecturers);
void arrangeTimeTable(vector<Course>& course);
void arrangeClassroom(vector<class Classroom>& classrooms,vector<Course>& course);
/*print*/
void printLesson(const vector<Course> courses);
int controlStudent(vector<Course>& course,int studentID,vector<class Classroom>& classrooms,int hourOfWeek);
int controlStudent(int studentID,vector<class Classroom>& classrooms);
string compareDate(Course course,string day,int hourOfWeek);
string date(int hour);
int isexist(vector<class Classroom> classrooms,string classID);
int isexist(vector<Lecturer> lecturer,string proffesions,int which);
int isexist(vector<Course> courses,string field,int which);

#endif