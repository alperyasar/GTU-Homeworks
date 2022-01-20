#include "lecturer.h"
#include "library.h"
#include "administrator.h"
#include <cstdlib> 
#include <ctime> 
using namespace std;


/*arrange time given specific course*/
void Administrator :: arrangeTimeTable(vector<Course>& course,int cid)
{
	int courseFound=0,numberOfDays;
	for (int i = 0; i < course.size(); ++i)
	{
		if(cid == course[i].id)
			courseFound = 1;
	}
	if(courseFound == 0)
		cerr << "Error: no course!"<<endl;
	else if(course[cid].dates.size() > 0)
	{
		cout << "Assigned" << endl <<"Before: ("<< course[cid].id <<")" << course[cid].name <<" ";
		int i;
		for (i = 0; i < course[cid].dates.size()-1; ++i)
		{
			cout << course[cid].dates[i].day << "_" << course[cid].dates[i].beginLesson <<"-" << course[cid].dates[i].endLesson << ",";
		}
			cout << course[cid].dates[i].day << "_" << course[cid].dates[i].beginLesson <<"-" << course[cid].dates[i].endLesson << endl;
	}

	else
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
		cout << "DONE: ("<< course[cid].id <<")" << course[cid].name <<" ";
		int j;
		for (j = 0; j < course[cid].dates.size()-1; ++j)
		{
			cout << course[cid].dates[j].day << "_" << course[cid].dates[j].beginLesson <<"-" << course[cid].dates[j].endLesson << ",";
		}
			cout << course[cid].dates[j].day << "_" << course[cid].dates[j].beginLesson <<"-" << course[cid].dates[j].endLesson << endl;
	}
}
/*arrange time all course*/
void Administrator :: arrangeTimeTable(vector<Course>& course)
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
		cout << "("<< course[cid].id <<")" << course[cid].name <<" ";
		int j;
		for (j = 0; j < course[cid].dates.size()-1; ++j)
		{
			cout << course[cid].dates[j].day << "_" << course[cid].dates[j].beginLesson <<"-" << course[cid].dates[j].endLesson << ",";
		}
			cout << course[cid].dates[j].day << "_" << course[cid].dates[j].beginLesson <<"-" << course[cid].dates[j].endLesson << endl;
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
void Administrator :: arrangeClassroom(vector<Classroom>& classrooms,vector<Course>& course)
{
	for (int i = 0; i < course.size(); ++i)
	{	
		if(course[i].dates[0].classroom.compare("") == 0)
		{
			for(int l = 0; l < course[i].dates.size(); ++l)
			{
				int randomNumber = rand() % classrooms.size();
				course[i].dates[l].classroom.assign(classrooms[randomNumber].c_no);
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
				cout << ",";
		}
		cout << endl;
	}
}
/*assign given specific course to classes*/
void Administrator ::  arrangeClassroom(vector<Classroom>& classrooms,vector<Course>& course,int courseID,string classID)
{
	int i=0,j=0,k=0;
	int notClass = 0,emptyClass=0;
	std::vector<string> classes;
	while(classID[i] != '\0')
	{
		if(classID[i] == ',')
		{
			j++;
			classes.resize(j);
			classes[j-1].assign(classID,k,i-k);
			notClass = isexist(classrooms,classes[j-1]);
			if(notClass == -1)
				break;
			i++;
			k=i;			
		}
		i++;
	}
	if(notClass != -1)
	{		
		j++;
		classes.resize(j);
		classes[j-1].assign(classID,k,i-k);
		notClass = isexist(classrooms,classes[j-1]);
		if(notClass != -1)
		{
			if(course[courseID].dates.size() < 1)
				cerr << "Timetable not arranged yet" << endl;
			for (i = 0; i < classes.size(); ++i)
			{
				for ( j = 0; j < course.size(); ++j)
				{
					for (k = 0; k < course[j].dates.size(); ++k)
					{

						if(course[j].dates[k].classroom.compare(classes[i]) == 0)
						{
							if(course[j].dates[k].day.compare(course[courseID].dates[i].day) == 0 && 
							  (course[j].dates[k].beginLesson == course[courseID].dates[i].beginLesson || course[j].dates[k].endLesson == course[courseID].dates[i].endLesson)){
								cerr << " Block: class is not available, there is another class assigned" << endl;
								emptyClass++;
							}
						}
					}
				}
			}
			if(emptyClass == 0)
			{
				cout << "DONE: ("<< course[courseID].id <<")" << course[courseID].name <<" ";
				for (i = 0; i < classes.size()-1; ++i)
				{
					course[courseID].dates[i].classroom.assign(classes[i]); 
					cout << "in " << course[courseID].dates[i].classroom << " at ";
					cout << course[courseID].dates[i].day << "_" << course[courseID].dates[i].beginLesson <<"-" << course[courseID].dates[i].endLesson << ",";
				}
				for (j = i; j < course[courseID].dates.size(); ++j)
				{
					course[courseID].dates[j].classroom.assign(classes[i]); 
					cout << "in " << course[courseID].dates[j].classroom << " at ";
					cout << course[courseID].dates[j].day << "_" << course[courseID].dates[j].beginLesson <<"-" << course[courseID].dates[j].endLesson;
					if(j!= course[courseID].dates.size()-1)
						cout << ",";
				}
				cout << endl;
				 
			}
		}
	}
}
