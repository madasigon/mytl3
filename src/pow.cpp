#include "base.cpp"


#ifndef POW_CPP
#define POW_CPP

//STARTCOPY
namespace mytl{
template<typename T>
T power(T base, ll exponential, T unit=1){
    T res = unit;
    while(exponential > 0){
        if(exponential%2 == 1) res = res * base;
        base = base * base;
        exponential = exponential / 2;
    }
    return res;
}

template<typename T>
struct Pows2 : vector<T>{
    Pows2(){
        this->resize(300);
        this->operator[](0) = 1;
        for(ll i=1; i < this->size(); i++){
            this->operator[](i) = this->operator[](i) * 2;
        }
    }
};

template<typename T>
Pows2<T> powers2;

}
//ENDCOPY

#endif
