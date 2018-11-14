#include "convenience.cpp"


void convenience_test(){

    ll x = 1;
    auto y = LAZY(++x, ll);
    assert(x == 1);
    assert(y.value() == 2);
    assert(x == 2);


    mytl::Tracker<ll, mytl::min> t;

    t.update(2);
    t.update(3);
    t.update(1);
    assert(t.value() == 1);

    vector<ll> l{1,2,3,4};
    vector<ll> res;
    for(auto& par : mytl::adjecent_pairs(l)){
        res.push_back(par.first);
        res.push_back(par.second);
    }
    assert((res == vector<ll>{1, 2, 2, 3, 3, 4}));

    assert((mytl::fmap<ll,ll>([](ll x){return x*2;}, mytl::forrange<ll>(3,1)) == vector<ll>{2,4,6}));
}


