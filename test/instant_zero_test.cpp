#include <bits/stdc++.h>
#include "../src/instant_zero.cpp"
using namespace std;


map<ll, mytl::Resetter<string>::Variable> m;
void instant_zero_test(){
    auto r = *mytl::global_resetter<string>;
    mytl::Resetter<ll>::Variable x = 5;

    x = 7;
    cout<<x.get()<<endl;

    mytl::global_resetter<ll>->reset(0);

    cout<<x.get()<<endl;

    m[5] = "apple";
    cout<<m[5].get()<<endl;
    r.activate();
    r.reset("resetted to this");
    cout<<m[5].get()<<endl;
    cout<<m[6].get()<<endl;



}
