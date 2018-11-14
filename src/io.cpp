#include "base.cpp"
#include "convenience.cpp"

#ifndef io_CPP
#define io_CPP

//STARTCOPY

namespace std{

template<typename T>
istream& operator>>(istream& is, mytl::optional<T>& x){
    if(!x.has_value()){
        T x_;
        is>>x_;
        x = x_;
    }
    return is;
}

istream& operator>>(istream& is, Void& x){
    return is;
}

template<typename P, typename Q>
istream& operator>>(istream& is, pair<P,Q> x){
    return is>>x.first>>x.second;
}


template<typename P, typename Q>
ostream& operator<<(ostream& os, const pair<P,Q>& x){
    os<<"("<<x.first<<", "<<x.second<<")";
    return os;
}

template<typename T, template<typename, typename...> typename Container>
ostream& operator<<(ostream& os, const Container<T>& x){
    os<<"{";
    bool first = true;
    for(const auto& elem : x){
        if(!first) os<<", ";
        os<<elem;
        first = false;
    }
    os<<"}";
    return os;
}

}

namespace mytl{

template<typename T, typename P=T>
T read(istream& is=cin){
    P a;
    is>>a;
    return T(a);
}

template<typename T, typename P, typename Q>
T read(istream& is=cin){
    P a;
    Q b;
    is>>a>>b;
    return T(a,b);
}

template<typename T, typename P, typename Q, typename R>
T read(istream& is=cin){
    P a;
    Q b;
    R c;
    is>>a>>b>>c;
    return T(a,b,c);
}


template<typename T, typename... Q, typename Container=vector<T>>
vector<T> readValues(ll n, istream& is=cin){
    vector<T> res;
    repeat(n, [&res](){
        res.push_back(read<T,Q...>());
    });
    return Container(res.begin(), res.end());
}

}


namespace mytl{


template<typename T>
void print(const T& x, ostream& os=cout){
    os<<x;
}

}
//ENDCOPY

#endif
