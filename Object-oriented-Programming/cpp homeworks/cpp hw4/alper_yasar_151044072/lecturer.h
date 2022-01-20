#ifndef _LECTURER_H_
#define _LECTURER_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "library.h"
using namespace std;

class Lecturer{
public:
    Lecturer();
//    ~Lecturer();
//    Lecturer(const Lecturer& lecturer);
    void setLecturer(string line);
	int assignCourse(struct Course &lesson,int checkAssign);
	int assignCourse(struct Course& lesson,int checkAssign,int loopControl);
	friend ostream& operator <<(ostream& outputStream,const Lecturer& lecturer);

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