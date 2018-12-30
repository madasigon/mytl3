
#include "lazy.cpp"
using namespace std;


void lazy_test(){
    ll x = 1;
    auto y = LAZY(++x, ll);
    assert(x == 1);
    assert(y.value() == 2);
    assert(x == 2);

}