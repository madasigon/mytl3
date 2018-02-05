#include <bits/stdc++.h>
#include "pow.cpp"
using namespace std;
using ll = long long;

//STARTCOPY
namespace mytl{
    template<ll MOD>
    struct Modulo{
        using Self = Modulo<MOD>;
    private:
        ll val;

    public:
        static constexpr Modulo unit = 1;
        static Modulo inverse(Modulo x){// asserting MOD is prime
            return power(x, MOD-2, Modulo::unit);
        };
        Modulo(ll initVal){
            initVal %= MOD;
            if(val < 0) initVal += MOD;
            val = initVal;
        };
        Modulo& operator=(const Modulo&) = default;

        ll get() const{ // no type cast operator to prevent accidentally turning into ordinary number
            return val;
        }

        //Unary operators
        Modulo operator-() const{
            return Modulo(-val);
        };
        Modulo operator+() const{
            return Modulo(+val);
        };

        //Binary operators on ordinary numbers
        Modulo operator-(const ll& operand) const{
            return Modulo(val-operand);
        };
        Modulo operator+(const ll& operand) const{
            return Modulo(val+operand);
        };
        Modulo operator*(const ll& operand) const{
            return Modulo(val*operand);
        };
        Modulo operator/(const ll& operand) const{ //asserting MOD is prime
            return Modulo(val * inverse(operand));
        };

        //Binary operators on Modulo
        Modulo operator-(const Modulo& operand) const{
            return Modulo(val-operand.get());
        };
        Modulo operator+(const Modulo& operand) const{
            return Modulo(val+operand.get());
        };
        Modulo operator*(const Modulo& operand) const{
            return Modulo(val*operand.get());
        };
        Modulo operator/(const Modulo& operand) const{ //asserting MOD is prime
            return Modulo(val * inverse(operand));
        };
    };

    using Mod107 = Modulo<1000000007LL>;

    template<ll MOD>
    ostream& operator<<(ostream& os, Modulo<MOD> x){
        return os<<"("<<x.get()<<"%"<<MOD<<")";
    }


}
//ENDCOPY
