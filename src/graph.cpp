#include "base.cpp"
#include "convenience.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

//STARTCOPY
namespace mytl{
namespace graph{
struct Natural{
    using Node = ll;
    ll n;
    vector<vector<ll> > g;
    Natural(ll n) : n{n}, g(n+1){};

    Node newNode(){
        n++;
        g.push_back({});
        return n;
    }
    void newEdge(ll u, ll v){
        g[u].push_back(v);
    }
    vector<Node> getNodes(){
        vector<Node> res;
        for(ll i=1; i<=n; i++) res.push_back(i);
        return res;
    }
    vector<Node>& getNeighbours(Node x){
        return g[x];
    }

};
}

template<typename T>
T fromNeighbourList(optional<ll> n={}){
    cin>>n;
    T g(n.value());
    for(ll i=1; i<=n; i++){
        ll mi;
        cin>>mi;
        for(ll j=1; j<=mi; j++){
            ll neig;
            cin>>neig;
            g.newEdge(i, neig);
        }
    }
    return g;
}

template<typename T>
T fromEdgeList(optional<ll> n={}, bool bidirectional=true){
    cin>>n;
    ll m;
    cin>>m;
    T g(n.value());
    for(ll i=1; i<=m; i++){
        ll u,v;
        cin>>u>>v;
        g.newEdge(u,v);
        if(bidirectional){
            g.newEdge(v, u);
        }
    }
    return g;
}


template<typename T, typename Algo>
T dijkstra(T g, typename T::Node source){
    typename Algo::queue x;


}
}
//ENDCOPY

#endif
