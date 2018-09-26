#include "../src/convenience.cpp"
#include <optional>




void convenience_test(){

    mytl::Tracker<ll> t([](ll a, ll b){return min(a,b);});

    t.update(2);
    t.update(3);
    t.update(1);
    cout<<"smallest: "<<t.value()<<endl;

    vector<ll> l{1,2,3,4};
    for(auto p : mytl::adjecent_pairs<ll,vector<ll> >(l)){
        cout<<p.first<<","<<p.second<<endl;
    }
}
