#include <bits/stdc++.h>
using namespace std;


//STARTCOPY
namespace mytl{
template<typename T, typename P>
T power(T base, P exponential, T unit){
    T res = unit;
    while(exponential > 0){
        if(exponential%2 == P(1)) res = res * base;
        base = base * base;
        exponential = exponential / 2;
    }
    return res;
}
}
//ENDCOPY
