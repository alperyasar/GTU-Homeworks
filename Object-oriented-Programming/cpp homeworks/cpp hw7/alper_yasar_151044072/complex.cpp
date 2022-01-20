#include "complex.h"

template<typename T>
Complex<T> Complex<T>::operator +=(const Complex<T>& c) {
    cont += c.cont;
    return *this;
}

template<typename T>
Complex<T> Complex<T>::operator +(const Complex<T>& c)  {
    cont += c.cont;
    return *this;
}

template<typename T>
Complex<T> Complex<T>::operator -(const Complex<T>& c)  {
    cont -= c.cont;
    return *this;
}
template<typename T>
Complex<T> Complex<T>::operator ++()  {
    ++cont; 
    return *this;
}
template<typename T>
ostream& operator <<(ostream& os, const Complex<T>& c) {
    os << c.cont;
    return os;
}


