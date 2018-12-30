
#include "base.cpp"

#ifndef CONTAINER_CPP
#define CONTAINER_CPP

//STARTCOPY
namespace mytl{

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

}
//ENDCOPY

#endif