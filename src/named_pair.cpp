
#include "base.cpp"

#ifndef NAMED_PAIR_CPP
#define NAMED_PAIR_CPP

//STARTCOPY
namespace mytl{

#define NAMED_PAIR(classname, fst, snd)\
template<typename P, typename Q>\
struct classname : public pair<P,Q>{\
\
private:\
    using pair<P,Q>::first;\
    using pair<P,Q>::second;\
public:\
    P &fst = first;\
    Q &snd = second;\
    using pair<P,Q>::pair;\
};

}
//ENDCOPY

#endif