#include "../src/base.cpp"
#include "../src/reduce.cpp"



struct Q{
    using T = ll;
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
