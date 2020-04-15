
//#include "../cbp/test.h"
#include "modulo_typesafe.cpp"
using namespace std;



void modulo_typesafe_test(){
	mytl::optional<mytl::TSModulo<6> > lala;
	lala.set(3);
	auto x = lala.value();
}
