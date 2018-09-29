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

template<typename T, typename Container>
vector<PairOf<T&> > adjecent_pairs(Container& c){
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


}
//ENDCOPY

#endif
