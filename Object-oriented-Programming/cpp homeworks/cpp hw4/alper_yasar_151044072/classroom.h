#ifndef _CLASSROOM_H_
#define _CLASSROOM_H_
#include <iostream>
#include <vector>
#include <string>

#include "lecturer.h"
#include "library.h"

using namespace std;
namespace ClassName
{
	class Classroom{
	public:
		Classroom();
	//	~Classroom();
		Classroom(const Classroom& classrooms);

		friend ostream& operator <<(ostream& outputStream,const Classroom& classrooms);
		Classroom(string line);
		void enterClass(int studentID);
		void quitClass(int studentID);
		int isexist(string classID);
		int studentInroom(int studentID);
		int getID() {return id;};
		string getC_NO() {return c_no;};
		int getCAPACITY() {return capacity;};
		int getSTUDENTINROOM(){return student_inroom;};
		int getSTUNDENTID(int i){return student_id[i];};
	private:
		int id;
		string c_no;
		int capacity,student_inroom;
		int *student_id;
	};
}

#endif