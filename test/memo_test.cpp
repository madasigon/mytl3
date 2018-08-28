#include <bits/stdc++.h>
//#include "../cbp/test.h"
#include "../src/memo.cpp"
using namespace std;

int lassu_f(int i){
    if(i < 3) return i;
    return max(lassu_f(i-1), lassu_f(i-2));
}


int um_f(int i);
auto nat_f = mytl::natural_memo(um_f);
int um_f(int i){
    if(i < 3) return i;
    return max(nat_f(i-1), nat_f(i-2));
}

int um_unor_f(int i);
auto unordered_f = mytl::unordered_memo(um_unor_f);
int um_unor_f(int i){
    if(i < 3) return i;
    return max(unordered_f(i-1), unordered_f(i-2));
}



void memo_test(){
    assert(lassu_f(10) == nat_f(10) && unordered_f(1000) == nat_f(100));
}
