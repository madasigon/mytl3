#include "base.cpp"

#ifndef CONVENIENCE_CPP
#define CONVENIENCE_CPP

//STARTCOPY
namespace mytl{
template<typename T, T(*f)(T,T)>
struct Tracker : optional<T>{
    using optional<T>::operator=;

    Tracker() : optional<T>() {};

    void update(T val){
        if(this->has_value()){
            *this = f(this->value(), val);
        }
        else{
            *this = val;
        }
    }
};

template<typename T>
T min(T a, T b){return std::min(a,b);}
template<typename T>
T max(T a, T b){return std::max(a,b);}
template<typename T>
T __gcd(T a, T b){return std::__gcd(a,b);}

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

template<typename P, typename Q>
istream& operator>>(istream& is, pair<P,Q>& x){
    return is>>x.first>>x.second;
}

template<typename P, typename Q>
ostream& operator<<(ostream& os, const pair<P,Q>& x){
    return os<<"("<<x.first<<", "<<x.second<<")";
}

template<typename T>
ostream& print_elements(const T& t, string open="", string separator=" ", string close="", ostream& os=cout){
    os<<open;
    bool first = true;
    for(const auto& elem : t){
        if(!first) os<<separator;
        os<<elem;
        first = false;
    }
    os<<close;
    return os;
}


template<typename T>
ostream& operator<<(ostream& os, const vector<T>& t){
    return print_elements(t, "[", ", ", "]", os);
}
template<typename T>
ostream& operator<<(ostream& os, const set<T>& t){
    return print_elements(t, "{", ", ", "}", os);
}
template<typename T>
ostream& operator<<(ostream& os, const unordered_set<T>& t){
    return print_elements(t, "{", ", ", "}", os);
}
template<typename P, typename Q>
ostream& operator<<(ostream& os, const map<P, Q>& t){
    return print_elements(t, "{", ", ", "}", os);
}
template<typename P, typename Q>
ostream& operator<<(ostream& os, const unordered_map<P, Q>& t){
    return print_elements(t, "{", ", ", "}", os);
}


template<typename T>
struct Lazy : optional<T>{

    function<T()> f;

    Lazy(function<T()> f) : f{f}, optional<T>() {};

    inline T& value(){
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
