//STARTCOPY
#ifndef _MSC_VER
#include<bits/stdc++.h>
#else
#include <iostream>
#include<algorithm>
#include<vector>
#include <set>
#include <functional>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <queue>
#include <istream>
#include <numeric>
#include <string>
#endif


using namespace std;

using unsigned_int = unsigned int;
using need_int = int;
using counter_type = int;
using MAIN = int;
#define int DontUseIntÉ
using ll = long long;

template<typename T>
using PairOf = pair<T,T>;

using Void = tuple<>;

#ifdef __OPTIMIZE__
#define debug_assert(expression) 
#else
#define debug_assert(expression) assert(expression)
#endif

namespace mytl{

template<typename T, typename R, typename F=function<R(T)> >
vector<R> fmap(F f, const vector<T>& t){
    vector<R> res;
    for(auto elem : t) res.push_back(f(elem));
    return res;
}

template<typename T>
vector<T> forrange(T n, T from){
    vector<T> res(n);
    iota(res.begin(), res.end(), from);
    return res;
}

template<typename F>
void repeat(need_int n, const F& callback){
    for(need_int _ : forrange(n,0)) callback();
}



#define WATCH(x) cout << (#x) << " is " << (x) << endl
}
namespace mytl{

template<typename T, typename Pred>
T discrete_binary_search(T l, T r, Pred f){
	debug_assert(f(l));
    while(l < r){
        T pivot = (l+r+1)/2;
        if(!f(pivot)) r = pivot-1;
		else l = pivot;
    }
    return l;
}

template<typename T, typename Pred>
T continuous_binary_search(T l, T r, need_int iterations, Pred f){
    mytl::repeat(iterations,[&](){
        T pivot = (l+r)/2;
        if(f(pivot)) l = pivot;
        else r = pivot;
    });
    return l;
}
}
namespace mytl{

template<typename T>
struct LazyVector : vector<T> {
	inline typename vector<T>::reference operator[](need_int i) {

		if (i >= vector<T>::size()) vector<T>::resize(i + 1);
		return vector<T>::operator[](i);
	}
};

template<typename T>
struct TwoWayLazyVector {
	LazyVector<T> negative, positive;
	inline typename vector<T>::reference operator[](need_int i) {
		if(i >= 0){
			return positive[i];
		}
		else {
			return negative[-i];
		}
	}
};


template<typename T>
struct optional {
	T *ptr = nullptr;

	inline void set(const T& val) {
		ptr = new T(val);
	}

	inline optional() {}
	inline optional(const T& val) {
		set(val);
	}

	optional& operator=(const T& val){
		set(val);
		return *this;
	}

	~optional() {
		delete ptr;
	}
	inline T value() const {
		return *ptr;
	}
	inline bool has_value() const {
		return ptr != nullptr;
	}

	

	optional& operator=(const optional& other) {
		if (other.has_value()) {
			set(other.value());
		}
		else {
			ptr = nullptr;
		}
		return *this;
	}
	optional(const optional& other) {
		operator=(other);
	}

	optional(optional&& other) {
		ptr = other.ptr;
		other.ptr = nullptr;
	}

	optional& operator=(optional&& other) {
		if (this != &other) {
			delete ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
			return *this;
		}
	}

};

}
namespace mytl{

template<typename T, typename C = map<T, void*>, typename Data = tuple<>>
struct TrieNode {

    TrieNode* parent = nullptr;
    T label;
    C next = C();


    Data data = Data();

    TrieNode() {}
    TrieNode(TrieNode* parent, T label) : parent{ parent }, label{ label } {}


    TrieNode* jump(T c) {
        if (next[c] == nullptr) {
            next[c] = new TrieNode(this, c);
        }
        return (TrieNode*)next[c];
    }

    
    TrieNode* traverse(const vector<T>& s, function<void(Data&)> operation = [](Data &data) {}) {
        TrieNode* curr = this;

        operation(curr->data);
        for (T c : s) {
            curr = curr->jump(c);
            operation(curr->data);
        }
        return curr;
    }

    TrieNode* traverse(const string& s, function<void(Data&)> operation = [](Data& data) {}) {
        return traverse(vector<char>(s.begin(), s.end()), operation);
    }
};

}
namespace mytl{

template<typename T, typename C = map<T, void*>>
struct Corasick {
    struct Data {
        void* next_left = nullptr;
        void* link = nullptr;
        void* exit_link = nullptr;
        C go;
        vector<need_int> hits;
    };

    using State = TrieNode<T, C, Data>;

    State *root = new State;
    


    State* link(State *curr) {
        void*& kulcs = curr->data.link;
        if (kulcs == nullptr) {
            if (curr == root || curr->parent == root) {
                kulcs = root;
            }
            else {
                kulcs = go(link(curr->parent), curr->label);
            }
        }
        return (State*)kulcs;
    }
    State* go(State* curr, T c) {
        void*& kulcs = curr->data.go[c];
        if (kulcs == nullptr) {
            if (curr->next[c] != nullptr) {
                kulcs = curr->next[c];
            }
            else {
                if (curr->parent == nullptr) {
                    kulcs = root;
                }
                else {
                    kulcs = go(link(curr), c);
                }
            }
        }
        return (State*)kulcs;
    }

    State* exit_link(State* curr) {
        State*& kulcs = (State*&)curr->data.exit_link;

        if (kulcs == nullptr) {
            if (curr == root) {
                kulcs = nullptr;
            }
            else {
                if (!link(curr)->data.hits.empty()) kulcs = link(curr);
                else kulcs = exit_link(link(curr));
            }
        }
        return kulcs;
    }


public:

    template<typename Word>
    Corasick(const vector<Word>& words) {
        for (need_int i = 0; i < words.size(); i++) {
            root->traverse(words[i])->data.hits.push_back(i);
        }
    }

    State* step(State* currstate, T c) {
        return go(currstate, c);
    }

    State* initial_state() {
        return root;
    }

    vector<need_int> hits(State* currstate) {
        State* curr = currstate;

        vector<need_int> res;

        while (curr != nullptr) {
            res.insert(res.end(), curr->data.hits.begin(), curr->data.hits.end());
            curr = exit_link(curr);
        }

        return res;
    }

    need_int num_hits(State* currstate) {
        State* curr = currstate;

        need_int ans = 0;

        while (curr != nullptr) {
            ans += curr->data.hits.size();
            curr = exit_link(curr);
        }
        return ans;
    }

};


}
namespace mytl{

struct Point{
    ll x, y;

    Point(ll x, ll y) : x{x}, y{y} {};
    Point(pair<ll,ll> initPair) : x{initPair.first}, y{initPair.second} {};

    pair<ll,ll> getPair(){//not introducing type cast operator for safety
        return {x,y};
    }

    //Unary operators
    Point operator-() const{
        return {-x, -y};
    }
    Point operator+() const{
        return {x,y};
    }

    static ll sgn(ll x){
        return (x > 0) - (x < 0);
    }

    //Binary operators on ordinary numbers
    Point operator*(const ll& operand) const{
        return {x*operand, y*operand};
    }

    //Binary operators on Point itself
    Point operator+(const Point& operand) const{
        return {x+operand.x, y+operand.y};
    }
    Point operator-(const Point& operand) const{
        return {x-operand.x, y-operand.y};
    }

    ll operator*(const Point& operand){ //vectorial product
        return x*operand.y - y*operand.x;
    }

    ll direction(const Point& a, const Point& b) const{
        return sgn((a - *this) * (b - *this));
    };
};

ll distance_squared(const Point& a, const Point& b){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

double distance(const Point& a, const Point& b){
    return sqrt(distance_squared(a, b));
}

ll cartesian_distance(const Point& a, const Point& b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

typedef vector<Point> Poly;

bool inside(const Poly& poly, const Point& point, bool strict){ //assuming Poly is weakly convex
    ll prevdir = -2;
    for(ll i=0; i<poly.size(); i++){
        ll nexdindex = (i+1)%poly.size();
        ll dir = poly[i].direction(poly[nexdindex], point);
        if(dir == 0){
            if(strict) return false;
        }
        else{
            if(dir != prevdir && prevdir != -2) return false;
            prevdir = dir;
        }

    }
    return true;
}

}
namespace mytl {

template<class T>
struct Resetter;

template<class T>
Resetter<T>* global_resetter = new Resetter<T>;

template<class T>
struct Resetter {

    using State = pair<counter_type, T>;

    State* state = new State{0, T()};

    Resetter(){}
    Resetter(T value){
        state = new State{0, value};
    }

    void activate(){
        global_resetter<T> = this;
    }

    void reset(T value){
        *state = State{state->first+1, value};
    }

    struct Variable{

        State state;
        State& parent = *global_resetter<T>->state;

        Variable() : state{*global_resetter<T>->state} {}
        Variable(T value) : state{global_resetter<T>->state->first, value} {}
        Variable(State st) : state{st} {}
        Variable(T value, State& parent) : state{parent->first, value} {};

        bool fresh(){
            return state.first >= parent.first;
        }

        void overwrite(){
            state = parent;
        }

        void refresh(){
            if(!fresh()) overwrite();
        }

        T get(){
            refresh();
            return state.second;
        }

        void survive(){
            state.first = parent.first;
        }

        void operator=(T new_value){
            state.second = new_value;
            survive();
        }

    };

};
}

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
namespace mytl{
template<typename T>
T power(T base, ll exponential, T unit=1){
    T res = unit;
    while(exponential > 0){
        if(exponential%2 == 1) res = res * base;
        base = base * base;
        exponential = exponential / 2;
    }
    return res;
}

template<typename T>
struct Pows2 : vector<T>{
    Pows2(){
        this->resize(300);
        this->operator[](0) = 1;
        for(ll i=1; i < this->size(); i++){
            this->operator[](i) = this->operator[](i) * 2;
        }
    }
};

template<typename T>
Pows2<T> powers2;

}
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
namespace mytl {

template <typename C, typename Arg, typename R>
function<R(Arg)> __memoize(R(*fn)(Arg)) {
	C table;
	return [fn, table](Arg arg) mutable -> R {
		if (!table[arg].has_value()) {
			table[arg].set(fn(arg));
		}
		return table[arg].value();
	};
}

template<template<typename, typename, typename...> typename C, typename Arg, typename R>
function<R(Arg)> memoize(R(*fn)(Arg)) {
	return __memoize<C<Arg, optional<R> >, Arg, R>(fn);
}

template<typename R>
function<R (ll) > quick_memoize(R(*fn)(ll)) {
	return __memoize<TwoWayLazyVector<optional<R> >, ll, R>(fn);
}

template<typename R>
function<R(ll, ll)> quick_memoize(R(*fn)(ll, ll)) {
	TwoWayLazyVector< TwoWayLazyVector<optional<R> > > table;
	return [fn, table](ll p1, ll p2) mutable -> R {
		if(!table[p1][p2].has_value()){
			table[p1][p2].set(fn(p1, p2));
		}
		return table[p1][p2].value();
	};
}


}
namespace mytl{
template<class Op>
struct IntervalTree : Op::Range {
	using Range = typename Op::Range;
	using T = typename Op::T;
	using Change = typename Op::Change;
	using Range::singleton;
	using Range::inside;
	using Range::intersect;
	using Range::leftHalf;
	using Range::rightHalf;

	IntervalTree *left_child = NULL, *right_child = NULL;

	T partial;
	Change pending = Op::identity();

	IntervalTree(Range range) : Range(range), partial{ Op::initial(range) } {};

	T query(Range range, Change change) {
		return query_(range, change).first;
	}

	void add(Change change) {
		pending = Op::push(pending, change);
	}

	void prepare() {
		if (!singleton()) {
			if (left_child == NULL) left_child = (new IntervalTree(leftHalf()));
			if (right_child == NULL) right_child = (new IntervalTree(rightHalf()));
			left_child->add(pending);
			right_child->add(pending);
		}
		partial = Op::apply(*this, partial, pending);
		pending = Op::identity();
	}

	pair<T, T> query_(Range range, Change change) {
		//cout<<range<<" "<<*this<<endl;
		prepare();
		if (inside(range)) {
			add(change);
			prepare();
			return { partial, Op::zero() };
		}
		if (!intersect(range)) {
			//cout<<"n"<<range<<" "<<*this<<endl;
			return { Op::zero(), partial };
		}

		auto from_left = left_child->query_(range, change);
		auto from_right = right_child->query_(range, change);
		//cout<<from_right.first<<endl;
		auto needed = Op::reduce(from_left.first, from_right.first), rest = Op::reduce(from_left.second, from_right.second);
		partial = Op::reduce(needed, rest);
		return { needed, rest };
	}

	T build_from(const function<T(ll)>& getter) {
		prepare();
		pending = Op::identity();
		if (singleton()) partial = getter(this->l);
		else partial = Op::reduce(left_child->build_from(getter), right_child->build_from(getter));
		return partial;
	}

};


template<typename Op>
class SegmentTree {
public:
	const pair<ll, ll> range;
private:
	vector<typename Op::T> t;
	vector<typename Op::Change> d;
	ll n;
	ll h;

	void __calc(ll p, ll k) {
		t[p] = Op::apply(k, Op::reduce(t[p * 2], t[p * 2 + 1]), d[p]);
	}

	void __apply(ll p, typename Op::Change value, ll k) {
		t[p] = Op::apply(k, t[p], value);
		if (p < n) d[p] = Op::push(d[p], value);
	}

	void __build(ll l, ll r) {
		ll k = 2;
		l += n;
		r += n - 1;
		for (; l > 1; k *= 2) {
			l /= 2;
			r /= 2;
			for (ll i = r; i >= l; i--) __calc(i, k);
		}
	}

	void __push(ll l, ll r) {
		ll s = h;
		ll k = 1 << (h - 1);

		l += n;
		r += n - 1;
		for (; s > 0; s--, k /= 2) {
			for (ll i = l >> s; i <= r >> s; i++) {
				__apply(i * 2, d[i], k);
				__apply(i * 2 + 1, d[i], k);
				d[i] = Op::identity();
			}
		}
	}

	void __modify(ll l, ll r, typename Op::Change value) {
		__push(l, l + 1);
		__push(r - 1, r);
		ll l0 = l, r0 = r, k = 1;

		l += n;
		r += n;
		for (; l < r; l /= 2, r /= 2, k *= 2) {
			if (l & 1) __apply(l++, value, l);
			if (r & 1) __apply(--r, value, k);
		}
		__build(l0, l0 + 1);
		__build(r0 - 1, r0);
	}

	typename Op::T __query(ll l, ll r) {
		__push(l, l + 1);
		__push(r - 1, r);
		typename Op::T resl = Op::zero(), resr = Op::zero();

		l += n;
		r += n;

		for (; l < r; l /= 2, r /= 2) {
			if (l & 1)  resl = Op::reduce(resl, t[l++]);
			if (r & 1) resr = Op::reduce(t[--r], resr);
		}
		return Op::reduce(resl, resr);

	}

public:

	SegmentTree(pair<ll, ll> range, const function<typename Op::T(ll)>& getter) : range{ range } {
		n = range.second - range.first + 1;
		t.resize(n * 2);
		d.resize(n, Op::identity());
		for (ll i = 0; i < n; i++) {
			t[i + n] = getter(i+range.first);
		}
		for (ll i = n - 1; i > 0; i--) t[i] = t[i * 2] + t[i * 2 + 1];
		h = 0;
		ll new_n = n;
		while (new_n > 0) {
			h++;
			new_n /= 2;
		}

	}

	typename Op::T query(pair<ll, ll> query_range) {
		debug_assert(range.first <= query_range.first && query_range.second <= range.second);
		return __query(query_range.first - range.first, query_range.second - range.first + 1);
	}
	
	typename Op::T query_single(ll query_point) {
		return query({ query_point, query_point });
	}

	void modify(pair<ll, ll> modify_range, typename Op::Change value) {
		debug_assert(range.first <= modify_range.first && modify_range.second <= range.second);
		__modify(modify_range.first - range.first, modify_range.second - range.first + 1, value);
	}

	void modify_single(ll modify_point, typename Op::Change value) {
		return modify({ modify_point, modify_point }, value);
	}

};


template<typename T_, typename Range_>
struct Add_Sum {
	using Range = Range_;
	using T = T_;
	using Change = T_;

	static Change identity() {
		return 0;
	}

	static T zero() {
		return 0;
	}

	static T initial(Range r) {
		return zero();
	}

	static T reduce(T a, T b) {
		return a + b;
	}

	static T apply(Range r, T a, Change c) {
		return a + r.span()*c;
	}

	static Change push(Change a, Change b) {
		return a + b;
	}
};

template<typename T_, typename Range_>
struct Multiply_Sum {
	using Range = Range_;
	using T = T_;
	using Change = T_;

	static Change identity() {
		return 1;
	}

	static T zero() {
		return 0;
	}

	static T initial(Range r) {
		return r.span() * 1;
	}

	static T reduce(T a, T b) {
		return a + b;
	}

	static T apply(Range r, T a, Change c) {
		return a * c;
	}

	static Change push(Change a, Change b) {
		return a * b;
	}
};


/*
struct Custom_Op{
using Range = _;
using T = _;
using Change = _;

static Change identity(){
return _;
}

static T zero(){
return _;
}

static T initial(Range r){
return _;
}

static T reduce(T a, T b){
return _;
}

static T apply(Range r, T a, Change c){
return _;
}

static Change push(Change a, Change b){
return _;
}

};
*/
}
namespace mytl{

template<typename T, T(*f)(T,T)>
struct Tracker : optional<T>{

	void update(const T& x){
		if (optional<T>::has_value()) {
			optional<T>::set(f(optional<T>::value(), x));
		}
		else {
			optional<T>::set(x);
		}
    }
};

template<typename T>
T min(T a, T b){return std::min(a,b);}
template<typename T>
T max(T a, T b){return std::max(a,b);}
template<typename T>
T __gcd(T a, T b){return std::__gcd(a,b);}

}
//ENDCOPY


MAIN main() {
	ios_base::sync_with_stdio(false);
#ifdef _MSC_VER
#if 1
	freopen("be.txt", "r", stdin);
#endif
#endif // _MSC_VER

}