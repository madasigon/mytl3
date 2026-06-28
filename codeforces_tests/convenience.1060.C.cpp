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

// A streambuf that wraps every line it forwards in ANSI color codes, so that
// text sent through it shows up in a distinct color in the terminal.
struct ColorStreambuf : streambuf {
	streambuf* dest;
	string pre, post, buf;
	ColorStreambuf(streambuf* dest, string pre, string post) : dest(dest), pre(pre), post(post) {}
	void emit(){
		if(buf.empty()) return;
		dest->sputn(pre.data(), pre.size());
		dest->sputn(buf.data(), buf.size());
		dest->sputn(post.data(), post.size());
		buf.clear();
	}
	need_int overflow(need_int c) override {
		if(c == EOF) return c;
		if(c == '\n'){ emit(); dest->sputc('\n'); }
		else buf.push_back(char(c));
		return c;
	}
	need_int sync() override { emit(); return dest->pubsync(); }
};

// Make cerr (your debug output) appear in a different color from cout (the real
// answer), so the two are easy to tell apart while debugging in the terminal.
// Only activates on an interactive terminal: when stderr is redirected to a file
// or read by an online judge, nothing is changed and no color codes are emitted.
inline void enable_color_debug(){
#ifndef _MSC_VER
	if(isatty(2)){
		static ColorStreambuf b(cerr.rdbuf(), "\033[33m", "\033[0m"); // yellow
		cerr.rdbuf(&b);
	}
#endif
}

// Auto-enable at startup so cerr is colored without any extra call.
static need_int _color_debug_init = (enable_color_debug(), 0);

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
struct DynamicSegtree {
	using T = typename Op::T;
	using Change = typename Op::Change;
	using Range = pair<ll, ll>;

	DynamicSegtree<Op> *left_child = NULL, *right_child = NULL;

	T partial;
	Change pending = Op::identity();
	Range my_range;
	
	DynamicSegtree(Range range) : my_range{range}, partial{ Op::initial(range) } {};

	
	
	

	DynamicSegtree(Range range, function<T(ll)> getter) {
		my_range = range;
		if(range.first == range.second){
			partial = getter(range.first);
		}
		else{
			pair<ll,ll> range_left_half = {my_range.first, my_range.first + (my_range.second - my_range.first)/2};
			pair<ll,ll> range_right_half = {range_left_half.second + 1, my_range.second};

			if (left_child == NULL) left_child = (new DynamicSegtree(range_left_half,getter));
			if (right_child == NULL) right_child = (new DynamicSegtree(range_right_half,getter));
			partial = Op::reduce(left_child->partial, right_child->partial);
		}

	}


	void add(Change change) {
		pending = Op::push(pending, change);
	}

	void flush() {
		if (my_range.first < my_range.second) {
			pair<ll,ll> range_left_half = {my_range.first, my_range.first + (my_range.second - my_range.first)/2};
			pair<ll,ll> range_right_half = {range_left_half.second + 1, my_range.second};

			if (left_child == NULL) left_child = (new DynamicSegtree(range_left_half));
			if (right_child == NULL) right_child = (new DynamicSegtree(range_right_half));
			left_child->add(pending);
			right_child->add(pending);
		}
		partial = Op::apply(my_range.second - my_range.first+1, partial, pending);
		pending = Op::identity();
	}

	T _update(Range range, Change change) {
		if (range.first <= my_range.first && my_range.second <= range.second) {
			add(change);
			flush();
			return partial;
		}
		flush();
		if (range.first > my_range.second || range.second < my_range.first)  return partial;
		
		auto from_left = left_child->_update(range, change);
		auto from_right = right_child->_update(range, change);
		partial = Op::reduce(from_left, from_right);
		return partial;
	}
	void update(Range range, Change change) {
		_update(range, change);
	}

	T query(Range range) {
		if(range.second < my_range.first || my_range.second < range.first) return Op::zero();
		flush();
		if(range.first <= my_range.first && my_range.second <= range.second) return partial;
		return Op::reduce(left_child->query(range), right_child->query(range));
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

}
namespace mytl{

template<typename Op_>
struct Trie {
	struct Node;
	using Op = Op_;
	using T = typename Op::T;
	using Info = typename Op::template Info<Node>;
	using Next_Container = typename Op::template Next<Node*>;

	struct Node : Info {
		Node *parent;
		T last;
		Next_Container next;
		need_int leaf = 0;
		Node *jump(T c) {
			if (next.contains(c)) {
				return next[c];
			}
			else return nullptr;
		}

		Node(Node *parent, T last) : parent{ parent }, last{ last } {}
	};

	Node *root = new Node(nullptr, T());

	template<typename C>
	Node *insert_word(C word, need_int leaf_flag = 1) {
		Node *curr = root;
		for (T c : word) {
			if (!curr->next.contains(c)) {
				curr->next[c] = new Node(curr, c);
			}
			curr = curr->next[c];
		}
		curr->leaf = leaf_flag;
		return curr;
	}

	template<typename C>
	Node* jump_path(Node* node, C path) {
		for (T c : path) {
			if (node == nullptr) return node;
			node = node->jump(c);
		}
		return node;
	}

	template<typename C>
	bool contains_word(C word) {
		Node *res = jump_path(root, word);
		return res && res->leaf;
	}


};


template<need_int ALPHABETSIZE>
struct Basic_Char_Trie_Op {
	using T = char;

	template<typename Node>
	struct Info {
	};

	template<typename N>
	struct Next {
		N next[ALPHABETSIZE] = {};

		N& operator[](char i) {
			return next[i - 'a'];
		}

		bool contains(char i) {
			return operator[](i) != nullptr;
		}

	};

};


template<need_int ALPHABET_SIZE>
using CharTrie = Trie<Basic_Char_Trie_Op<ALPHABET_SIZE> >;


}
namespace mytl{

template<typename BaseTrie>
struct Corasick {

	struct Corasick_Op : BaseTrie::Op {
		using T = typename BaseTrie::Op::T;

		template<typename N>
		struct Info {
			N* next_leaf_d = nullptr;
			N* link_d = nullptr;
			typename BaseTrie::Op::template Next<N*> go_d;
		};
	};

	using MyTrie = Trie<Corasick_Op>;
	using Node = typename MyTrie::Node;
	using T = typename Corasick_Op::T;

	MyTrie trie;

	static Node* go(Node *node, T c) {
		if (!node->go_d.contains(c)) {
			if (node->next.contains(c)) {
				node->go_d[c] = node->next[c];
			}
			else if (node->parent == nullptr) {
				node->go_d[c] = node;
			}
			else {
				node->go_d[c] = go(link(node), c);
			}
		}
		return node->go_d[c];
	};

	static Node* link(Node *node) {
		if (node->link_d == nullptr) {
			if (node->parent == nullptr) {
				node->link_d = node;
			}
			else if (node->parent->parent == nullptr) {
				node->link_d = node->parent;
			}
			else {
				node->link_d = go(link(node->parent), node->last);
			}
		}
		return node->link_d;
	}

	static Node* next_leaf(Node *node) {
		if (node->next_leaf_d == nullptr) {
			if (node->parent == nullptr) {
				node->next_leaf_d = node;
			}
			else {
				if (link(node)->leaf) {
					node->next_leaf_d = link(node);
				}
				else {
					node->next_leaf_d = next_leaf(link(node));
					if (!node->next_leaf_d->leaf) {
						node->next_leaf_d = node;
					}
				}
			}
		}
		return node->next_leaf_d;
	}

	static vector<need_int> current_matches(Node* node) {
		vector<need_int> res;
		if (node->leaf) res.push_back(node->leaf);
		while (next_leaf(node) != node) {
			node = next_leaf(node);
			res.push_back(node->leaf);
		}
		return res;
	}

	Node *root = trie.root;


	template<typename C>
	Corasick(C dictionary) {
		need_int i = 0;
		for (auto word : dictionary) {
			trie.insert_word(word, ++i);
		}
	}

};


}
//ENDCOPY




ll n,m, x;



ll a[20001], b[20001], kum_a[20001], kum_b[20001];

using T = mytl::Tracker<ll, mytl::min>;
vector<T> best_a(20001), best_b(20001);

MAIN main(){
    ios_base::sync_with_stdio(false);
    cin>>n>>m;

    for(ll i=1; i<=n; i++){
        cin>>a[i];
        kum_a[i] = kum_a[i-1] + a[i];
    }

    for(ll i=1; i<=m; i++){
        cin>>b[i];
        kum_b[i] = kum_b[i-1] + b[i];
    }
    cin>>x;


    for(ll i=0; i<n; i++){
        for(ll hossz=1; i+hossz<=n; hossz++){
            best_a[hossz].update(kum_a[i+hossz] - kum_a[i]);
        }
    }
    for(ll i=0; i<m; i++){
        for(ll hossz=1; i+hossz<=m; hossz++){
            best_b[hossz].update(kum_b[i+hossz] - kum_b[i]);
        }
    }

    mytl::Tracker<ll, mytl::max> ans;
    ans.update(0);
    for(ll i=1; i<=n; i++){
        for(ll j=1; j<=m; j++){
            if(best_a[i].value()*best_b[j].value() <= x) ans.update(i*j);
        }
    }


    cout<<ans.value()<<endl;

}