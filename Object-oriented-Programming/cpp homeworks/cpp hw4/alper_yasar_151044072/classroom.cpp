#include "classroom.h"
#include <iostream>
#include <string>
#include <sstream>
#include "library.h"

using namespace std;
namespace ClassName
{
	Classroom :: Classroom()
	{
		id = 0;
		c_no = "";
		capacity = 0;
		student_inroom = 0;
	}
	/*copy constructer*/
	Classroom :: Classroom(const Classroom& classrooms){
		id = classrooms.id;
		c_no = classrooms.c_no;
		capacity = classrooms.capacity;
		student_inroom = classrooms.student_inroom;
	}
	/*Classroom :: ~Classroom(){
		delete [] student_id;
	} */
	Classroom :: Classroom(string line){
		istringstream some_stream(line);
		some_stream >> id >> c_no >> capacity;

		student_inroom = 0;
	}

	ostream& operator <<(ostream& outputStream,const Classroom& classrooms)
	{

		outputStream << classrooms.id << " " << classrooms.c_no << " "<< classrooms.capacity<< " " << endl;

		return outputStream;
	}
	
	int Classroom :: isexist(string classID){
		if(c_no.compare(classID) == 0)
			return id-1;
		return -1;
	}

	void Classroom :: enterClass(int studentID){
		int *temp;
		if(student_inroom != 0){
			student_inroom++;
			temp = student_id;
			student_id = new int[student_inroom];
			student_id = temp;
			student_id[student_inroom-1] = studentID;
		}	
		else{
			student_inroom++;
			student_id = new int[student_inroom];
			student_id[student_inroom-1] = studentID;
		}
		cout << "DONE!"<<endl;
	}
	void Classroom :: quitClass(int studentID){
		int control = 0;
		for (int i = 0; i < student_inroom; ++i)
		{
			if(student_id[i] == studentID) control = 1;
			if(control == 1 && i < student_inroom-1){
				student_id[i] = student_id[i+1];
			}
		}
		if(control == 1){
			student_inroom--;
		}
	
	}
	int Classroom :: studentInroom(int studentID){
		for (int i = 0; i < student_inroom; ++i)
		{
			if(*student_id == studentID)
				return 1;
		}
		return 0;
	}	
}
