#include <bits/stdc++.h>
#include "../src/instant_zero.cpp"
using namespace std;



void instant_zero_test(){
    mytl::Resetter<ll>::Variable x = 5;

    x = 7;
    cout<<x.get()<<endl;

    mytl::global_resetter<ll>.reset(0);

    cout<<x.get()<<endl;

}
