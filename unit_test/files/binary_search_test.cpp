
#include "binary_search.cpp"
using namespace std;

template<typename T>
bool pred(T val){
    return val < 5;
}

void binary_search_test(){
    debug_assert((
        mytl::discrete_binary_search<ll>(0, 10, pred<ll>) == 4
        &&
        abs(mytl::continuous_binary_search<double>(0,10,100, pred<double>) - 5) < 0.0001
    ));


}