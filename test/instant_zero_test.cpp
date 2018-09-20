#include <bits/stdc++.h>
#include "../src/instant_zero.cpp"
using namespace std;


map<ll, mytl::Resetter<string>::Variable> m;
void instant_zero_test(){
    auto r = *mytl::global_resetter<string>;
    mytl::Resetter<ll>::Variable x = 5;

    x = 7;
    assert(x.get() == 7);

    mytl::global_resetter<ll>->reset(0);

    assert(x.get() == 0);

    m[5] = "apple";
    assert(m[5].get() == "apple");
    r.activate();
    r.reset("resetted to this");
    assert(m[5].get() == "resetted to this");
    assert(m[6].get() == "resetted to this");



}
