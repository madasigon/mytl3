
#include "base.cpp"
#include "container.cpp"

#ifndef TRACKER_CPP
#define TRACKER_CPP

//STARTCOPY
namespace mytl{

template<typename T, T(*f)(T,T)>
struct Tracker : optional<T>{

	void update(const T& x){
		if (optional<T>::has_value()) {
			optional<T>::set(f(optional<T>::value(), x));
		}
		else {
			optional<T>::set(x);
		}
    }
};

template<typename T>
T min(T a, T b){return std::min(a,b);}
template<typename T>
T max(T a, T b){return std::max(a,b);}

}
//ENDCOPY

#endif