
#include "lecturer.h"
#include "library.h"
#include "classroom.h"

Lecturer :: Lecturer()
{
    personal_id = 0;
    name = "";
    surname = "";
    title = "";
}
/*	//copy constructer
Lecturer :: Lecturer(const Lecturer& templecturer){
	cout << "a"<<endl;
	personal_id = templecturer.personal_id;
    name = templecturer.name;
    surname = templecturer.surname;
    title = templecturer.title;
    int i =0;
}*/
 /*	//destructer
Lecturer :: ~Lecturer()
{
	
}*/
void Lecturer :: setLecturer(string line)
{
	string field;
	int i(0),k(0),size(0);
	istringstream some_stream(line);

	some_stream >> personal_id >> name >> surname >> title >> field;
	while(field[i])
	{
		if(field[i] == ',')
		{
			size++;
			proffesions.resize(size);
			proffesions[size-1].assign(field,k,i-k);
			i++;
			k=i;
		}
		i++;
	}
	size++;
	proffesions.resize(size);
	proffesions[size-1].assign(field,k,i-k);
}
ostream& operator <<(ostream& outputStream,const Lecturer& lecturer){
	outputStream <<  lecturer.personal_id << " " << lecturer.name << " " << lecturer.surname <<" "<< lecturer.title << endl;
	int i = 0;

	while(i < lecturer.lessons.size())
	{
		
		outputStream << lecturer.lessons[i].name << ", "<< lecturer.lessons[i].code<< " ";
		i++;
	}
	outputStream << endl;
	return outputStream;
}

int Lecturer :: assignCourse(struct Course& lesson,int checkAssign)
{
	int i(0),compareResult=0;
	if(lessons.size() < 3 && lesson.isAssign == 0)
	{
		
		lesson.isAssign =1;
	    lessons.push_back(lesson);
    	checkAssign = 1;
    }
    
    return checkAssign; 
}
int Lecturer :: assignCourse(struct Course& lesson,int checkAssign,int loopControl)
{
	int i(0),compareResult=0;
	for(int j=0;j<getProffesionsSize(); j++)
	{
		if(lessons[j].isMandatory == 0)
		{
			lessons.erase(lessons.begin()+j);
			lesson.isAssign =1;
		    lessons.push_back(lesson);
   		 	checkAssign = 1;
   		 	break;
		}
	}
    
    return checkAssign; 
}



