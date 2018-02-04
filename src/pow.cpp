#include <bits/stdc++.h>
using namespace std;


//STARTCOPY
namespace mytl{
template<typename T, typename P>
T pow(T base, P pow, T unit){
    T res = unit;
    while(pow > 0){
        if(pow%2 == P(1)) res = res * base;
        base = base * base;
        pow = pow / 2;
    }
    return res;
}
};
//ENDCOPY
