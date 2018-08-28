#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifndef INSTANT_ZERO_CPP
#define INSTANT_ZERO_CPP

//STARTCOPY
namespace mytl{

template<class Q>
struct Zeroable{
    using T = typename Q::T;
    T _value;
    const ll& latest;
    ll freshness;

    void freshen(){
        freshness = latest;
    }

    T get(){
        if(freshness < latest){
            _value = Q::zero(); //TODO
            freshen();
        }
        return _value;
    }
    void set(T to_what){
        _value = to_what;
        freshen();
    }
    void set(Zeroable<T> to_what){
        set(to_what.get());
    }
    void operator=(T to_what){
        set(to_what);
    }
    void operator=(Zeroable<T> to_what){
        set(to_what);
    }

    Zeroable(const ll& latest) : latest(latest), freshness{latest}, _value{T::zero()} {}
    Zeroable(const ll& latest, T init) : latest(latest), freshness{latest}, _value{init} {}
};

template<class Q>
struct ZFactory{
    using Zeroable = Zeroable<Q>;
    using T = typename Q::T;
    ll latest = 0;

    Zeroable create(){
        return Zeroable(latest);
    }
    Zeroable create(T init){
        return Zeroable(latest, init);
    }
    void reset(){
        latest++;
    }
};

}
//ENDCOPY

#endif
