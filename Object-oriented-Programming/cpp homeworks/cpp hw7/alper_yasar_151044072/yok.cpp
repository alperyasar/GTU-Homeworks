#include "yok.h"


YOK::YOK(){
  research=new University<int>(0,"IYTE");
  linguistic=new University<double>(0,"BOGAZICI");
  technical=new University<complex<int>>("GTU");

}

template<class T>
void YOK::giveJob(T& employee,string name,string surname){
	employee.setNameSurname(name,surname);
	cout << employee.getName() << employee.getSurname() << " ";	
}
template<class U>
bool YOK::foundUni(University<U> uni,string uniName){
	return(uniName.compare(uni.getName()));
}