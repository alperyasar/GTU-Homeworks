#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <iostream>
using namespace std;

class University
{
public:
	University();
	University(const University &temp);
	University(const int cont);
	void setCont(int cont);
	int getCont();
private:
	int contribution;
};



#endif