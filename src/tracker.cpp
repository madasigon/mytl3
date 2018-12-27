
#include "base.cpp"

#ifndef TRACKER_CPP
#define TRACKER_CPP

//STARTCOPY
namespace mytl{

template<typename T, T(*f)(T,T)>
struct Tracker : optional<T>{

    Tracker() : optional<T>() {};

    void update(T val){
        if(this->has_value()){
            optional<T>::operator=(f(this->value(), val));
        }
        else{
            optional<T>::operator=(val);
        }
    }
};

template<typename T>
T min(T a, T b){return std::min(a,b);}
template<typename T>
T max(T a, T b){return std::max(a,b);}
template<typename T>
T __gcd(T a, T b){return std::__gcd(a,b);}

}
//ENDCOPY

#endif