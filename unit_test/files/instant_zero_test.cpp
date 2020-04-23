
#include "instant_zero.cpp"
using namespace std;


map<ll, mytl::Resetter<string>::Variable> m;
void instant_zero_test(){
    auto r = *mytl::global_resetter<string>;
    mytl::Resetter<ll>::Variable x = 5;

    x = 7;
    debug_assert(x.get() == 7);

    mytl::global_resetter<ll>->reset(0);

    debug_assert(x.get() == 0);

    m[5] = "apple";
    debug_assert(m[5].get() == "apple");
    r.activate();
    r.reset("resetted to this");
    debug_assert(m[5].get() == "resetted to this");
    debug_assert(m[6].get() == "resetted to this");



}
