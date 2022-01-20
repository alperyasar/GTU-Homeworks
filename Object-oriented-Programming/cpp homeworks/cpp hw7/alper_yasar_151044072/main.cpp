#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <ctime> 

#include "secretary.h"
#include "researchassistant.h"
#include "officer.h"
#include "lecturer.h"
#include "university.h"
#include "university.cpp"
#include "yok.h"
#include "yok.cpp"
#include <complex>
#include "capitalisteducation.h"
#include "communisteducation.h"
#include "liberaleducation.h"

using namespace std;


int main(){
    Communist communist;
    Capitalist capitalist;
    Liberal liberal;
        srand((unsigned)time(nullptr));

    cout<< "Choose one story-types : L (liberal), Com(communist), and Cap(capitalist) : ";
    string choosen;
    cin >> choosen;
    if(choosen.compare("Com")==0 || choosen.compare("com")==0 || choosen.compare("COM")==0)
        communist.process();
    else if(choosen.compare("Cap")==0 || choosen.compare("cap")==0 || choosen.compare("CAP")==0)
        capitalist.process();
    else if(choosen.compare("Lib")==0 || choosen.compare("lib")==0 || choosen.compare("LIB")==0)
        liberal.process();
}