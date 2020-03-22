
#include "base.cpp"

#ifndef TRACKER_CPP
#define TRACKER_CPP

//STARTCOPY
namespace mytl{

template<typename T, T(*f)(T,T)>
struct Tracker {

	T* val = nullptr;

    void update(T x){
        if(val != nullptr){
            *val = f(*val, x);
        }
        else{
			val = new T;
			*val = x;
        }
    }

	T value() {
		return *val;
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