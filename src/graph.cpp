#include "base.cpp"
#include "io.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

//STARTCOPY
namespace mytl{

template<typename N, typename E, template<typename, typename> typename C>
struct Container_Graph : C<N, vector<pair<E, N> > >{
    template<typename A, typename B>
    using Container = C<A,B>;
    using Edge = E;
    using Node = N;
    optional<ll> n;
    Container_Graph(ll n={}) : n{n}, Container<Node, vector<pair<Edge, Node> > >() {}

    void newEdge(Node u, Node v, Edge edge=Void()){
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

using NormalSimpleGraph = Container_Graph<ll, Void, AssocVector>;

template<typename G>
void readNeighbourList(G& g, ll indexing=1){
    for(ll i : forrange(g.n.size(), indexing)){
        for(ll neig : readValues<ll>(read<ll>())){
            g.new_edge(i, neig);
        }
    }
}

template<typename G>
void readEdgeList(G& g, optional<ll> m, bool bidirectional=true){
    using Node = typename G::Node;
    using Edge = typename G::Edge;
    cin>>m;
    for(auto [u, v, edge] : readValues<tuple<Node, Node, Edge> >(m.value())){
        g.newEdge(u,v,edge);
        if(bidirectional) g.newEdge(v, u, edge);
    }
}

template<typename Container>
struct Util{
};
template<
    typename G,
    template<typename> typename A,
    typename F=void(*)(typename A<G>::Option)
>
auto queue_graph_algorithm(
    G& g,
    vector<typename A<G>::Option > sources,
    optional<F> new_node_callback={})
{
    using Algo = A<G>;
    typename Algo::Queue q;
    
    for(auto source : sources) q.push(source);
    typename G::template Container<typename G::Node, typename Algo::Info> d;
    while(!q.empty()){
        auto akt = Algo::consume(q);
        typename Algo::Node who = akt.second;
        typename Algo::Info info = akt.first;

        if(Util<decltype(d)>::has_key(d, who)) continue;

        d[who] = info;
        
        if(new_node_callback.has_value()){
            new_node_callback.value()({info, who});
        }
        for(auto par : g.getEdges(who)) if(!Util<decltype(d)>::has_key(d, par.second)){
            q.push({Algo::append({info, who}, par.first, par.second), par.second});
        }
    }
    return d;
}

template<template<typename> typename QP, template<typename> typename P>
struct AlgoComposer{
    template<typename G>
    struct A{
        using Path = P<G>;
        using Edge = typename G::Edge;
        using Node = typename G::Node;
        using Info = typename Path::Info;
        using Option = pair<Info, Node>;
        using QueuePolicy = QP<Option>;
        using Queue = typename QueuePolicy::Queue;

        static Option consume(Queue& q){
            return QueuePolicy::consume(q);
        }
        static void push(Queue& q, Option new_option){
            return QueuePolicy::push(q, new_option);
        }
        static Info append(pair<Info, Node> from , Edge e, Node to){
            return Path::append(from, e, to);
        }
    };
};


template<typename T>
struct Priority{
    using Queue = priority_queue<T, vector<T>, greater<T> >;
    static T consume(Queue& q){
        auto res = q.top();
        q.pop();
        return res;
    }
    static void push(Queue& q, T new_option){
        q.push(new_option);
    }
};


template<typename T>
struct FIFO{
    using Queue = queue<T>;
    static T consume(Queue& q){
        auto res = q.front();
        q.pop();
        return res;
    }
    static void push(Queue& q, T new_option){
        q.push(new_option);
    }
};

template<typename T>
struct FILO{
    using Queue = stack<T>;
    static T consume(Queue& q){
        auto res = q.top();
        q.pop();
    }
    static void push(Queue& q, T new_option){
        q.pop();
    }
};

template<typename G>
struct JustLength{
    using Info = typename G::Edge;
    static Info append(pair<Info, typename G::Node> from, typename G::Edge e, typename G::Node n){
        return from.first + e;
    }
};

template<typename G>
struct LengthAndLastNode{
    using Info = pair<typename G::Edge, typename G::Node>;
    static Info append(pair<Info, typename G::Node> from, typename G::Edge e, typename G::Node n){
        return {from.first + e, from.second};
    }
};


/*
template<typename G>
struct Custom{
    using Edge = typename G::Edge;
    using Node = typename G::Node;

    using Info = _;
    using Option = pair<Info, Edge>;
    using Queue = _;

    static Option consume(Queue &q){
        _
        return _;
    }

    static void push(Queue &q, Option new_option){
        _
    }



    static Info append(Option from, Edge e, Node to){
        return _
    }

};
*/
}
//ENDCOPY

#endif
