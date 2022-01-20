#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

#include "lecturer.h"
#include "library.h"

class Administrator{
public:
    Administrator() : pid(1), password(1) {};
	
	void arrangeTimeTable(vector<Course>& course,int cid);
	void arrangeTimeTable(vector<Course>& course);
	void arrangeClassroom(vector<Classroom>& classrooms,vector<Course>& course);
	void arrangeClassroom(vector<Classroom>& classrooms,vector<Course>& course,int courseID,string classID);

private:				//Name, surname, personal_id, title, proffesions, courses
	int pid, password;
};
#endif