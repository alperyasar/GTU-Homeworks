
#include "lecturer.h"
#include "library.h"

Lecturer :: Lecturer()
{
    personal_id = 0;
    name = "";
    surname = "";
    title = "";
}
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

void Lecturer :: proposeCourse(string line,Course&lesson)
{
    if(lessons.size()<3){
    	lesson.isAssign = 1;
    	lessons.push_back(lesson);
    	cout << "DONE!"<<endl;
    }
    else
    	cerr << "Lecturer has too much lesson!!" << endl;
    			
}
int isexist(vector<Lecturer> lecturer,int id)		/*if lecturer id does not exit return false else return number*/
{
	int i(0);
	while(i++ < lecturer.size())
	{
		if(lecturer[i-1].getID() == id )
			return i-1;
	}
	cout << "There is no LECTURER who has this ID" << endl;
	return -1;
}
void Lecturer :: assignCourse(Course &lesson)
{
	int i(0),compareResult=0;
	if(lessons.size()<3 && lesson.isAssign == 0)
	{
		while(proffesions.size() > i++)
		{
			if(proffesions[i-1].compare(lesson.field) == 0)
				compareResult = 1;
		}
		if(compareResult == 1){
			lesson.isAssign =1;
	    	lessons.push_back(lesson);
    		cout << "DONE!"<<endl;
		}
    }
    else
    	cerr << "Lecturer has too much lesson or lesson has assigned!!" << endl;
}
int Lecturer :: assignCourse(struct Course& lesson,int checkAssign)
{
	int i(0),compareResult=0;
	if(lessons.size()<3&& lesson.isAssign == 0)
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
int isexist(vector<Lecturer> lecturer,string proffesions,int which)		/*if lecturer id does not exit return false else return number*/
{
	int i(0),k=0;
	while(i++ < lecturer.size())
	{
		for(int j=0;j<lecturer[i-1].getProffesionsSize(); j++)
		{
			if(lecturer[i-1].getProffesions(j).compare(proffesions) == 0)
			{
				if(k == which)
					return i-1;
				else k++;
			}
		}
	}
	return -1;
}