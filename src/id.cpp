
#include "base.cpp"

#ifndef ID_CPP
#define ID_CPP

//STARTCOPY
namespace mytl{

template<typename T=ll>
struct Id{
private:
    ll val;
public:
    Id();
    Id(T val) : val{val} {}
    Id& operator=(const Id&) = default;

    T get() const {
        return val;
    }
    operator size_t() const {
        return get();
    }

    bool operator==(const Id& other) const {
        return val == other.val;
    }
    bool operator!=(const Id& other) const {
        return !operator==(other);
    }

    bool operator<(const Id& other) const {
        return val < other.val;
    }
    bool operator>(const Id& other) const {
        return val > other.val;
    }

};

template<typename T>
ostream& operator<<(ostream& os, const Id<T>& x){
    return os<<x.get();
}

template<typename T>
istream& operator>>(istream& is, Id<T>& x){
    T to_read;
    is>>to_read;
    x = to_read;
    return is;
}

}
//ENDCOPY

#endif