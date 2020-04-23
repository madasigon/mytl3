
#include "base.cpp"
#include "convenience.cpp"

#ifndef BINARY_SEARCH_CPP
#define BINARY_SEARCH_CPP

//STARTCOPY
namespace mytl{

template<typename T, typename Pred>
T discrete_binary_search(T l, T r, Pred f){
	debug_assert(f(l));
    while(l < r){
        T pivot = (l+r+1)/2;
        if(!f(pivot)) r = pivot-1;
		else l = pivot;
    }
    return l;
}

template<typename T, typename Pred>
T continuous_binary_search(T l, T r, need_int iterations, Pred f){
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