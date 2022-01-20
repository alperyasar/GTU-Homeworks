#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

template<typename T>
class Complex {
private:
    T cont;
public:
    Complex<T>()
        :cont(0){ };
    Complex<T>(T contribution)
    {
    //    cont = contribution.cont;
    };
    Complex<T>(const Complex<T>& c)
        :cont(c.cont){ }; 
    Complex<T> operator +=(const Complex<T>& c);
    Complex<T> operator +(const Complex<T>& c) ;
    Complex<T> operator -(const Complex<T>& c) ;
    Complex<T> operator ++() ;
		template<typename U>
    friend ostream& operator <<(ostream&, const Complex<U>&);

};

#endif