using ll = long long;

ll tabnums = 0;

//STARTCOPY
#include<bits/stdc++.h>
using namespace std;

using counter_type = int;
using MAIN = int;
#define int DontUseIntÉ
using ll = long long;

template<typename T>
using PairOf = pair<T,T>;

namespace mytl{
template<typename T, typename P>
T power(T base, P exponential, T unit){
    T res = unit;
    while(exponential > 0){
        if(exponential%2 == P(1)) res = res * base;
        base = base * base;
        exponential = exponential / 2;
    }
    return res;
}
}
namespace mytl{
    template<ll MOD>
    struct TSModulo{
    private:
        ll val;

    public:
        static TSModulo unit(){
            return 1;
        }
        static TSModulo inverse(TSModulo x){// asserting MOD is prime
            return power(x, MOD-2, unit());
        };
        TSModulo(ll initVal){
            initVal %= MOD;
            if(val < 0) initVal += MOD;
            val = initVal;
        };
        TSModulo& operator=(const TSModulo&) = default;

        ll get() const{ // no type cast operator to prevent accidentally turning into ordinary number
            return val;
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
        TSModulo operator/(const ll& operand) const{ //asserting MOD is prime
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
        TSModulo operator/(const TSModulo& operand) const{ //asserting MOD is prime
            return TSModulo(val * inverse(operand));
        };
    };

    using Mod107 = TSModulo<1000000007LL>;

    template<ll MOD>
    ostream& operator<<(ostream& os, TSModulo<MOD> x){
        return os<<"("<<x.get()<<"%"<<MOD<<")";
    }


}
namespace mytl{
    template<class Q>
    struct Maybe{
        using T = typename Q::T;
        T *val=nullptr;
        void update(T operand){
            if(val == nullptr){
                val = new T;
                *val = operand;
            }
            else{
                *val = Q::reduce(*val, operand);
            }
        }
        T get(){
            return *val;
        }
        static Maybe<Q> nothing(){
            return Maybe<Q>();
        }
        static Maybe<Q> just(T value){
            Maybe<Q> res;
            res.val = new T(value);
            return res;
        }
    };
}
namespace mytl{
    template <typename R, typename... Args>
    function<R (Args...)> memo(R (*fn)(Args...)) {
        map<tuple<Args...>, R> table;
        return [fn, table](Args... args) mutable -> R {
            auto argt = make_tuple(args...);
            auto memoized = table.find(argt);
            if(memoized == table.end()) {
                auto result = fn(args...);
                table[argt] = result;
                return result;
            } else {
                return memoized->second;
            }
        };
    }

    template <typename R, typename Arg>
    function<R (Arg)> unordered_memo(R (*fn)(Arg)) {
        unordered_map<Arg, R> table;
        return [fn, table](Arg arg) mutable -> R {
            auto memoized = table.find(arg);
            if(memoized == table.end()) {
                auto result = fn(arg);
                table[arg] = result;
                return result;
            } else {
                return memoized->second;
            }
        };
    }

    template <typename R, typename Arg>
    function<R (Arg)> natural_memo(R (*fn)(Arg)) {
        vector<pair<bool, R> > table;
        return [fn, table](Arg arg) mutable -> R {
            if(table.size() <= arg) table.resize(arg+1, {false, R()});
            if(!table[arg].first) {
                table[arg] = {true, fn(arg)};
            }
            return table[arg].second;
        };
    }
}
namespace mytl{

}
namespace mytl{
    struct Modulo{
    private:
        ll val;
    public:
        const ll MOD;
        Modulo(ll initMOD, ll initVal) : MOD{initMOD}, val{initVal} {
            val %= MOD;
            if(val < 0) val += MOD;
        };

        static Modulo inverse(Modulo x){// asserting MOD is prime
            return power(x, x.MOD-2, x.unit());
        };
        Modulo unit() const{
            return Modulo(MOD, 1);
        }
        Modulo& operator=(const Modulo& operand){
            val = operand.val;
            return *this;
        };

        ll get() const{ // no type cast operator to prevent accidentally turning into ordinary number
            return val;
        }

        //Unary operators
        Modulo operator-() const{
            return Modulo(MOD, -val);
        };
        Modulo operator+() const{
            return Modulo(MOD, +val);
        };

        //Binary operators on ordinary numbers
        Modulo operator-(const ll& operand) const{
            return Modulo(MOD, val-operand);
        };
        Modulo operator+(const ll& operand) const{
            return Modulo(MOD, val+operand);
        };
        Modulo operator*(const ll& operand) const{
            return Modulo(MOD, val*operand);
        };
        Modulo operator/(const ll& operand) const{ //asserting MOD is prime
            return Modulo(MOD, val * inverse(Modulo(MOD, operand)).get());
        };

        //Binary operators on Modulo
        Modulo operator-(const Modulo& operand) const{
            return Modulo(MOD, val-operand.get());
        };
        Modulo operator+(const Modulo& operand) const{
            return Modulo(MOD, val+operand.get());
        };
        Modulo operator*(const Modulo& operand) const{
            return Modulo(MOD, val*operand.get());
        };
        Modulo operator/(const Modulo& operand) const{ //asserting MOD is prime
            return Modulo(MOD, val * inverse(operand).get());
        };

    };

    Modulo mod107(ll x){
        return Modulo(1000000007LL, x);
    }
    ostream& operator<<(ostream& os, Modulo x){
        return os<<"("<<x.get()<<"%"<<x.MOD<<")";
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

        bool refresh(){
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
template<class Q>
    struct Offline{
        using Query = typename Q::Query;
        using T = typename Q::T;
        typedef pair<Query, function<void(T)> > Tie;
        vector<Tie> queries;
        Offline(){};

        void query(Query question, function<void(T)> callback){
            queries.push_back({question, callback});
        }

        void process(){
            sort(begin(queries), end(queries), [](Tie a, Tie b){return Q::comp(a.first, b.first);});
            for(Tie query : queries){
                query.second(Q::query_function(query.first));
            }
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

typedef vector<Point> Poly;

bool inside(const Poly& poly, const Point& point, bool strict){
    set<ll> dirs;
    for(ll i=0; i<poly.size(); i++){
        ll nexdindex = (i+1)%poly.size();
        ll dir = poly[i].direction(poly[nexdindex], point);
        if(dir == 0){
            if(strict) return false;
        }
        else{
            dirs.insert(dir);
            if(dirs.size() > 1) return false;
        }

    }
    return true;
}

}
namespace mytl{
template<class Op>
struct Node : Op::Range{
    using Range = typename Op::Range;
    using T = typename Op::T;
    using Change = typename Op::Change;
    using Range::singleton;
    using Range::inside;
    using Range::intersect;
    using Range::leftHalf;
    using Range::rightHalf;

    Node *left_child=NULL, *right_child=NULL;

    T partial;
    Change pending = Op::identity();

    Node(Range range) : Range(range), partial{Op::initial(range)} {};

    T query(Range range, Change change){
        return query_(range, change).first;
    }

    void add(Change change){
        pending = Op::push(pending, change);
    }

    void prepare(){
        if(!singleton()){
            if(left_child == NULL) left_child = (new Node(leftHalf()));
            if(right_child == NULL) right_child = (new Node(rightHalf()));
            left_child->add(pending);
            right_child->add(pending);
        }
        partial = Op::apply(*this, partial, pending);
        pending = Op::identity();
    }

    pair<T,T> query_(Range range, Change change){
        //cout<<range<<" "<<*this<<endl;
        prepare();
        if(inside(range)){
            add(change);
            prepare();
            return {partial, Op::zero()};
        }
        if(!intersect(range)){
            //cout<<"n"<<range<<" "<<*this<<endl;
            return {Op::zero(), partial};
        }

        auto from_left = left_child->query_(range, change);
        auto from_right = right_child->query_(range, change);
        //cout<<from_right.first<<endl;
        auto needed = Op::reduce(from_left.first, from_right.first), rest = Op::reduce(from_left.second, from_right.second);
        partial = Op::reduce(needed, rest);
        return {needed, rest};
    }

    T build_from(const function<T(ll)>& getter){
        prepare();
        pending = Op::identity();
        if(singleton()) partial = getter(this->first);
        else partial = Op::reduce(left_child->build_from(getter), right_child->build_from(getter));
        return partial;
    }

};

struct Range1D : pair<ll,ll>{
    using pair<ll,ll>::pair;

    ll span() const {
        return second-first+1;
    }
    bool singleton() const {
        return span() == 1;
    }
    Range1D leftHalf() const {
        return Range1D(first, (first+second)/2);
    }
    Range1D rightHalf() const {
        return Range1D((first + second)/2 + 1, second);
    }
    bool inside(const Range1D& other) const {
        return other.first <= first && second <= other.second;
    }
    bool intersect(const Range1D& other) const {

        return other.inside(*this)
             ||(other.first <= first && first <= other.second)
             ||(other.first <= second && second <= other.second);
    }
};


}

//ENDCOPY
 //HAJAJ
using ll = long long;
using Par = pair<ll, ll>;
using ParPar = pair<Par, Par>;

ll M = 1000000007;

Par operator+(Par a, Par b){
    Par res = {(a.first+b.first), a.second + b.second};
    return {res.first%M, res.second%M};
}
Par operator*(Par a, ParPar b){
    Par res = {b.first.first*a.first + b.first.second*a.second, b.second.first*a.first + b.second.second*a.second};
    return {res.first%M, res.second%M};
}
ParPar operator*(ParPar a_, ParPar b_){
    ll a = a_.first.first,
         b = a_.first.second,
         c = a_.second.first,
         d = a_.second.second,
         e = b_.first.first,
         f = b_.first.second,
         g = b_.second.first,
         h = b_.second.second;
    ParPar res = {{e*a+f*c, e*b+f*d}, {g*a + h*c, g*b + h*d}};
    return {{res.first.first%M, res.first.second%M}, {res.second.first%M, res.second.second%M}};
}

struct Custom_Op{
    using Range = mytl::Range1D;
    using T = Par;
    using Change = ParPar;

    static Change identity(){
        return {{1, 0}, {0,1}};
    }
    static T zero(){
        return {0, 0};
    }

    static T initial(Range r){
        Par res = {r.span()%M, r.span()%M};
        return res;
    }

    static T reduce(T a, T b){
        T res = a + b;
        return res;
    }

    static T apply(Range r, T a, Change c){
        T res = a * c;
        return res;
    }

    static Change push(Change a, Change b){
        Change res = a * b;
        return res;
    }
};


ll n,m;

ParPar hatv(ll kitevo){
    ParPar res = Custom_Op::identity();
    ParPar alap = {{0,1}, {1,1}};
    while(kitevo > 0){
        if(kitevo%2 == 1) res = res*alap;
        alap = alap*alap;
        kitevo /= 2;
    }
    return res;
}

MAIN main() {
    //freopen("be.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    mytl::Node<Custom_Op> node({1,n});
    vector<ll> be(n+1);
    for(ll i=1; i<=n; i++){
        cin>>be[i];
    }
    node.build_from([&be](ll index){return Par{1,1} * hatv(be[index]-1);});
    for(ll i=1; i<=m; i++){
        ll mode;
        cin>>mode;
        if(mode == 1){
            ll l,r,x;
            cin>>l>>r>>x;
            node.query({l,r}, hatv(x));
        }
        else{
            ll l,r;
            cin>>l>>r;
            cout<<node.query({l,r}, Custom_Op::identity()).first<<endl;
        }
    }

}
