#ifndef STRUCTEMP_H
#define STRUCTEMP_H

#include <iostream>
#include <string>
using namespace std;
struct Emp
{
	string name,surname;
	int pid;
	Emp *next;
};

bool isExist(const Emp *temp, string name, string surname);
bool isExistPid(const Emp *temp, int pid);
void assign(Emp *&strEmployee,string name,string surname,int pid);
void remove(Emp *&strEmployee,int pid);

#endif