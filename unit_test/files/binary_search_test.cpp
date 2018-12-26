
#include "binary_search.cpp"
using namespace std;

template<typename T>
bool pred(T val){
    return val < 5;
}

void binary_search_test(){

    assert((
        mytl::discrete_binary_search<ll>(pred<ll>, 0, 10) == 4
        &&
        abs(mytl::continous_binary_search<double>(pred<double>,0,10,100) - 5) < 0.0001
    ));


}