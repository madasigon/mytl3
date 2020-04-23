#include "base.cpp"
#include "pow.cpp"


#ifndef MODULO_CPP
#define MODULO_CPP

//STARTCOPY
namespace mytl{

struct Modulo {

	static ll CURRENT_MOD;

private:
	ll val;

public:
	static Modulo inverse(Modulo x) {// assuming MOD is prime and x != 0
		return power(x, CURRENT_MOD - 2);
	};
	Modulo(ll initVal) {
		debug_assert(CURRENT_MOD != 0);
		if (-CURRENT_MOD < initVal && initVal < CURRENT_MOD) {
			val = initVal;
		}
		else {
			val = initVal % CURRENT_MOD;
		}
	}
	Modulo() : Modulo(0) {}
	Modulo& operator=(const Modulo&) = default;

	ll get() const { // no type cast operator to prevent accidentally turning into ordinary number
		if (val >= 0) return val;
		else return val + CURRENT_MOD;
	}

	//Unary operators
	Modulo operator-() const {
		return Modulo(-val);
	};
	Modulo operator+() const {
		return Modulo(+val);
	};

	//Binary operators on ordinary numbers
	Modulo operator-(const ll& operand) const {
		return Modulo(val - operand);
	};
	Modulo operator+(const ll& operand) const {
		return Modulo(val + operand);
	};
	Modulo operator*(const ll& operand) const {
		return Modulo(val*operand);
	};
	Modulo operator/(const ll& operand) const { //debug_asserting MOD is prime
		return Modulo(inverse(operand) * val);
	};

	//Binary operators on Modulo
	Modulo operator-(const Modulo& operand) const {
		return Modulo(val - operand.get());
	};
	Modulo operator+(const Modulo& operand) const {
		return Modulo(val + operand.get());
	};
	Modulo operator*(const Modulo& operand) const {
		return Modulo(val*operand.get());
	};
	Modulo operator/(const Modulo& operand) const { //debug_asserting MOD is prime
		return Modulo(inverse(operand) * val);
	};
};

ll Modulo::CURRENT_MOD = 0;

}
//ENDCOPY

#endif
