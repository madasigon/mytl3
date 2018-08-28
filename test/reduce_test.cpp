#include <bits/stdc++.h>
#include "../src/reduce.cpp"
using namespace std;


struct Q{
    using T = int;
    static T reduce(T a, T b){
        return min(a,b);
    }
};
void reduce_test(){
    mytl::Maybe<Q> c;
    c.update(6);
    c.update(4);
    c.update(5);
    cout<<endl<<"=77"<<c.get()<<endl;
}
