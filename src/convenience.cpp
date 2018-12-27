#include "base.cpp"

#ifndef CONVENIENCE_CPP
#define CONVENIENCE_CPP

//STARTCOPY
namespace mytl{

template<typename T, typename R, typename F=function<R(T)> >
vector<R> fmap(F f, const vector<T>& t){
    vector<R> res;
    for(auto elem : t) res.push_back(f(elem));
    return res;
}

template<typename T>
vector<T> forrange(T n, T from){
    vector<T> res(n);
    iota(res.begin(), res.end(), from);
    return res;
}

template<typename F>
void repeat(need_int n, const F& callback){
    for(need_int _ : forrange(n,0)) callback();
}


template<typename T, template<typename, typename...> typename Container>
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
    typename vector<T>::reference operator[](counter_type i){
        if(i >= this->size()) this->resize(i+1);
        return vector<T>::operator[](i);
    }
};

template<typename K, typename T>
struct AssocVector : LazyVector<T>{
    LazyVector<bool> exists;
    typename vector<T>::reference operator[](counter_type i){
        exists[i] = true;
        return LazyVector<T>::operator[](i);
    }
    typename vector<T>::iterator find(counter_type i){
        if(!exists[i]) return this->end();
        else return this->begin() + i;
    }
};

template<template<typename, typename, typename...> typename Container, typename Key, typename Value>
bool has_key(Container<Key, Value>& container, Key key){
    return container.find(key) != container.end();
}

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
