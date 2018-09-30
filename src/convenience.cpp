#include "base.cpp"

#ifndef CONVENIENCE_CPP
#define CONVENIENCE_CPP

//STARTCOPY
namespace mytl{
template<typename T>
struct Tracker : optional<T>{
    using optional<T>::operator=;
    function<T(T,T)> f;

    Tracker(function<T(T,T)> f) : f{f} {};

    void update(T val){
        if(this->has_value()){
            *this = f(this->value(), val);
        }
        else{
            *this = val;
        }
    }
};

template<typename T, template<typename> typename Container>
vector<PairOf<T&> > adjecent_pairs(Container<T>& c){
    vector<PairOf<T&> > res;
    optional<T*> prev_elem;
    for(auto& elem : c){
        if(prev_elem.has_value()){
            res.push_back({*prev_elem.value(), elem});
        }
        prev_elem = &elem;
    }
    return res;
}

template<typename T>
struct LazyVector : vector<T>{
    T& operator[](counter_type i){
        if(i >= this->size()) this->resize(i+1);
        return vector<T>::operator[](i);
    }
};

template<typename K, typename T>
using AssocVector = LazyVector<T>;

template<typename T>
istream& operator>>(istream& os, optional<T>& x){
    if(x.has_value()) return os;
    else{
        T val;
        os>>val;
        x = val;
        return os;
    }
}

istream& operator>>(istream& os, Void x){
    return os;
}

template<typename T>
struct Lazy : optional<T>{

    function<T()> f;

    Lazy(function<T()> f) : f{f}, optional<T>() {};

    T value(){
        if(!this->has_value()){
            optional<T>::operator=(f());
        }
        return optional<T>::value();
    }

};

#define LAZY(val, tipe) Lazy<tipe>([&](){return (val);})

}
//ENDCOPY

#endif
