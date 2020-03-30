#ifndef DIMENSION_CPP
#define DIMENSION_CPP

#include <iostream>
#include <vector>
#include <cassert>

//STARTCOPY
namespace mytl{
template <typename T, int... Args>
class Unit {
    int value;
    using U = Unit<T,Args...>;
public:
    // if explicit is written out, than you cannot say e.g. t+=1; or ...=a+1;
    // but would be safer. (It was better without explicit in the end.)
    /*explicit*/ Unit(int value=0) : value(value) {}
    inline U operator+(const U& a) const {
        return U(value+a.value);
    }
    inline U& operator+=(const U& a) {
        value += a.value;
        return *this;
    }
    inline U operator-(const U& a) const {
        return U(value-a.value);
    }
    inline U operator-() const {
        return U(-value);
    }
    inline U& operator-=(const U& a) {
        value -= a.value;
        return *this;
    }
    
    inline bool operator<(const U& a) const { return value < a.value; }
    inline bool operator>(const U& a) const { return value > a.value; }
    inline bool operator<=(const U& a) const { return value <= a.value; }
    inline bool operator>=(const U& a) const { return value >= a.value; }
    inline bool operator==(const U& a) const { return value == a.value; }
    inline bool operator!=(const U& a) const { return value != a.value; }

    inline U& operator++()
    {
        value++;
        return *this;
    }

    inline U& operator--()
    {
        value--;
        return *this;
    }

    int get() const { return value; }

    // TODO Not *really* part of the module, but my test needs it.
    // Maybe some magic with SFINAE would solve this
    U getSumRange() const { return *this; }
};

template <typename T, int... Args>
Unit<T,Args...> operator*(int mult, Unit<T,Args...>& unit) {
    return Unit<T,Args...>(mult*unit.get());
}

template <typename T, int... Args>
std::ostream& operator<<(std::ostream& os, const Unit<T,Args...>& u) {
    return os << u.get();
}

template <typename T, int... Args>
std::istream& operator>>(std::istream& is, Unit<T,Args...>& u) {
    int i=0;
    is >> i;
    u = Unit<T,Args...>(i);
    return is;
}

}
//ENDCOPY

#endif
