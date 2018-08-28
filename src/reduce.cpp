#include <bits/stdc++.h>
using namespace std;

#ifndef REDUCE_CPP
#define REDUCE_CPP

//STARTCOPY
namespace mytl{
    template<class Q>
    struct Maybe{
        using T = typename Q::T;
        T *val=nullptr;
        void update(T operand){
            if(val == nullptr){
                val = new T;
                *val = operand;
            }
            else{
                *val = Q::reduce(*val, operand);
            }
        }
        T get(){
            return *val;
        }
        static Maybe<Q> nothing(){
            return Maybe<Q>();
        }
        static Maybe<Q> just(T value){
            Maybe<Q> res;
            res.val = new T(value);
            return res;
        }
    };
}
//ENDCOPY


#endif
