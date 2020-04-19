#include "base.cpp"
#include "convenience.cpp"

#ifndef io_CPP
#define io_CPP

//STARTCOPY

namespace mytl{

template<typename T>
T read(istream& is=cin){
    T a;
    is>>a;
    return a;
}

template<typename T, typename Container=vector<T>>
vector<T> readValues(ll n, istream& is=cin){
    vector<T> res;
    repeat(n, [&res](){
        res.push_back(read<T>());
    });
    return Container(res.begin(), res.end());
}


template<typename T>
void print(const T& x, ostream& os=cout){
    os<<x;
}

template<typename Container>
void printContainer(const Container& cont, ostream& os=cout){
    os<<"{";
    bool first = true;
    for(const auto& elem : cont){
        if(!first){
            os<<", ";
        }
        else{
            first = false;
        }
        print(elem, os);
    }
    os<<"}";
}


}
//ENDCOPY

#endif
