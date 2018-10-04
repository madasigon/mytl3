#include "base.cpp"
#include "convenience.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

//STARTCOPY
namespace mytl{

template<typename N, typename E, template<typename, typename> typename Container>
struct Container_Graph : Container<N, vector<pair<E, N> > >{
    using Edge = E;
    using Node = N;
    optional<ll> n;
    Container_Graph(ll n={}) : n{n}, Container<Node, vector<pair<Edge, Node> > >() {}

    void newEdge(ll u, ll v, Edge edge=Void()){
        (*this)[u].push_back(make_pair(edge, v));
    }
    vector<Node> getNodes(){
        vector<Node> res;
        if(n.has_value()){
            for(ll i=1; i<=n.value(); i++) res.push_back(i);
        }
        else{
            for(auto& p : *this){
                res.push_back(p.first);
            }
        }
        return res;

    }
    vector<pair<Edge, Node> >& getEdges(Node node){
        return (*this)[node];
    }
    vector<Node > getNeighbours(Node node){
        vector<Node> res;
        for(auto& par : getEdges(node)){
            res.push_back(par.second);
        }
        return res;
    }

};


template<typename T>
void readNeighbourList(T& g){
    for(ll i=1; i<=g.n.value(); i++){
        ll mi;
        cin>>mi;
        for(ll j=1; j<=mi; j++){
            ll neig;
            cin>>neig;
            g.newEdge(i, neig);
        }
    }
}

template<typename T>
void readEdgeList(T& g, optional<ll> m, bool bidirectional=true){
    cin>>m;
    for(ll i=1; i<=m.value(); i++){
        ll u,v;
        typename T::E edge;
        cin>>u>>v>>edge;
        g.newEdge(u,v,edge);
        if(bidirectional){
            g.newEdge(v, u, edge);
        }
    }
}


template<typename Algo, typename Container>
void graph_algorithm(typename Algo::Graph& g, vector<pair<typename Algo::Info, typename Algo::Node> > sources, Container& tav){
    typename Algo::Queue qu;
    for(auto source : sources) qu.push(source);

    while(!qu.empty()){
        auto akt = qu.top();
        qu.pop();
        typename Algo::Node who = akt.second;
        typename Algo::Info info = akt.first;

        if(tav[who].has_value()) continue;

        tav[who] = info;

        for(auto par : g.getEdges(who)) if(!tav[par.second].has_value()){
            qu.push(make_pair(Algo::append({info, who}, par.first, par.second), par.second));
        }
    }
}

template<typename G>
struct BFS{
    using Edge = typename G::Edge;
    using Node = typename G::Node;
    using Graph = G;

    using Info = ll;
    struct Queue : queue<pair<Info, Node> >{
        pair<Info, Node> top(){
            return this->front();
        }
    };
    static Info append(pair<Info,Node> from, Edge e, Node to){
        return from.first + 1;
    }
};

template<typename G>
struct Dijkstra{
    using Edge = typename G::Edge;
    using Node = typename G::Node;
    using Graph = G;

    using Info = Edge;
    using Queue = priority_queue<pair<Info, Node>, vector<pair<Info, Node> >, greater<pair<Info, Node> > >;

    static Info append(pair<Info,Node> from, Edge e, Node to){
        return from.first + e;
    }

};
}
//ENDCOPY

#endif
