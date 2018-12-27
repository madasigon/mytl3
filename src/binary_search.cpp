
#include "base.cpp"
#include "convenience.cpp"

#ifndef BINARY_SEARCH_CPP
#define BINARY_SEARCH_CPP

//STARTCOPY
namespace mytl{

template<typename T>
T discrete_binary_search(function<bool(T)> f, T l, T r){
    if(!f(l)) return l;
    while(l < r){
        T pivot = (l+r)/2;
        if(!f(pivot)) r = pivot-1;
        else if(!f(pivot+1)) l = r = pivot;
        else l = pivot+1;
    }
    return l;
}

template<typename T>
T continuous_binary_search(function<bool(T)> f, T l, T r, need_int iterations){
    mytl::repeat(iterations,[&](){
        T pivot = (l+r)/2;
        if(f(pivot)) l = pivot;
        else r = pivot;
    });
    return l;
}
}
//ENDCOPY

#endif