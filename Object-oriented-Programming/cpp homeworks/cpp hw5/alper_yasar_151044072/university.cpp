#include "university.h"

University :: University() : contribution(0) {}
University :: University(const int cont) : contribution(cont) {}
University :: University(const University &temp){
	contribution = temp.contribution;
}

void University ::  setCont(int cont){
	contribution += cont;
}
int University ::  getCont(){
	return contribution;
}


