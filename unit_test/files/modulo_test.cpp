
//#include "../cbp/test.h"
#include "modulo.cpp"
using namespace std;



void modulo_test(){
    cout<<mytl::Modulo(10, 5) * 2<<endl;
    assert((mytl::Modulo(7, 3) / 2).get() == 5);
}
