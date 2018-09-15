#include <bits/stdc++.h>
//#include "../cbp/test.h"
#include "../src/modulo.cpp"
#include "../src/segtree.cpp"
using namespace std;
using namespace mytl;

ll MOD=8;

struct Custom_Op{
    using Range = Range1D;
    using T = Modulo;
    using Change = Modulo;

    static Change identity(){
        return Modulo(MOD,0);
    }
    static T zero(){
        return Modulo(MOD, 0);
    }

    static T initial(Range r){
        return Modulo(MOD, 0);
    }

    static T reduce(T a, T b){
        return a+b;
    }

    static T apply(Range r, T a, Change c){
        return a + (c*r.span());
    }

    static Change push(Change a, Change b){
        return a+b;
    }

};


Modulo mke(ll x){
    return Modulo(MOD, x);
}

ll n;

vector<Modulo> kum;

void segtree_test(){
    Node<Custom_Op> node({1, 5});


}
