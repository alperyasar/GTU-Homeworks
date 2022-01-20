#ifndef _LECTURER_H_
#define _LECTURER_H_
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "library.h"

using namespace std;

class Lecturer{
public:
    Lecturer();
    void setLecturer(string line);
    void proposeCourse(string line,struct Course& lesson);	//Lecturer proposes new courses. If courses given by the lecturer is less than
	void assignCourse(struct Course &lesson);						//proposed course(s) is added to overall courses list.
	int assignCourse(struct Course &lesson,int checkAssign);
	int assignCourse(struct Course& lesson,int checkAssign,int loopControl);
									//assignCourse(): Course is assigned to lecturer. If Lecturer gives 3 courses, assignment is not
										//allowed. If lecturer gives less than 3 courses and s/he has not proposed any elective courses,
										//program asks her/him to propose an elective course.
	int getProffesionsSize(){return proffesions.size();};
	string getProffesions(int i){return proffesions[i];};
    int getID(){return personal_id;};
    int getLessonSize(){return lessons.size();};
private:				//Name, surname, personal_id, title, proffesions, courses
	int personal_id;
	string name,surname;
	string title;
	vector<string> proffesions;
	vector<Course> lessons;
};

#endif