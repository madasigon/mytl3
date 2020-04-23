#include "base.cpp"
#include "pow.cpp"
#include "container.cpp"

#ifndef MODULO_TYPESAFE_CPP
#define MODULO_TYPESAFE_CPP

//STARTCOPY
namespace mytl{
    template<ll MOD>
    struct TSModulo{
		friend class optional<TSModulo<MOD> >;
    private:
        ll val;

    public:
        static TSModulo inverse(TSModulo x){// assuming MOD is prime and x != 0
            return power(x, MOD-2);
        };
		TSModulo(ll initVal) {
			if (-MOD < initVal && initVal < MOD) {
				val = initVal;
			}
			else {
				val = initVal % MOD;
			}
		}
        TSModulo() : TSModulo(0) {}
        TSModulo& operator=(const TSModulo&) = default;

        ll get() const{ // no type cast operator to prevent accidentally turning into ordinary number
			if (val >= 0) return val;
			else return val + MOD;
        }

        //Unary operators
        TSModulo operator-() const{
            return TSModulo(-val);
        };
        TSModulo operator+() const{
            return TSModulo(+val);
        };

        //Binary operators on ordinary numbers
        TSModulo operator-(const ll& operand) const{
            return TSModulo(val-operand);
        };
        TSModulo operator+(const ll& operand) const{
            return TSModulo(val+operand);
        };
        TSModulo operator*(const ll& operand) const{
            return TSModulo(val*operand);
        };
        TSModulo operator/(const ll& operand) const{ //debug_asserting MOD is prime
            return TSModulo(inverse(operand) * val);
        };

        //Binary operators on Modulo
        TSModulo operator-(const TSModulo& operand) const{
            return TSModulo(val-operand.get());
        };
        TSModulo operator+(const TSModulo& operand) const{
            return TSModulo(val+operand.get());
        };
        TSModulo operator*(const TSModulo& operand) const{
            return TSModulo(val*operand.get());
        };
        TSModulo operator/(const TSModulo& operand) const{ //debug_asserting MOD is prime
            return TSModulo(val * inverse(operand));
        };
    };

	template<ll MOD>
	struct optional<TSModulo<MOD> >{
		ll val = off_value;
		static const ll off_value = -MOD - 1;

		bool has_value() const {
			return val != off_value;
		}

		void set(const TSModulo<MOD>& other) {
			val = other.val;
		}

		TSModulo<MOD> value() const {
			debug_assert((has_value()));
			if (!has_value()) {
                TSModulo<MOD>* dummy = nullptr;
				return *dummy;
			}
			return TSModulo<MOD>(val);
		}

		optional() {
		}

		optional<TSModulo<MOD> >& operator=(const TSModulo<MOD>& other) {
			set(other);
			return *this;
		}
		optional(const TSModulo<MOD>& other) {
			set(other);
		}

	};

    using Mod107 = TSModulo<1000000007LL>;

}
//ENDCOPY

#endif
