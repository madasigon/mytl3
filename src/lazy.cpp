
#include "base.cpp"

#ifndef LAZY_CPP
#define LAZY_CPP

//STARTCOPY
namespace mytl{


template<typename T>
struct Lazy : optional<T>{

    function<T()> f;

    Lazy(function<T()> f) : f{f}, optional<T>() {};

    T& value(){
        if(!this->has_value()){
            optional<T>::operator=(f());
        }
        return optional<T>::value();
    }

};

#define LAZY(val, tipe) mytl::Lazy<tipe>([&](){return (val);})
#define WATCH(x) cout << (#x) << " is " << (x) << endl

}
//ENDCOPY

#endif