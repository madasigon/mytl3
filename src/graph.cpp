#include "base.cpp"
#include "io.cpp"
#include "named_pair.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

//STARTCOPY
namespace mytl{



template<typename N, typename E, template<typename, typename, typename...> typename C>
struct Container_Graph{
    template<typename A, typename B>
    using Container = C<A,B>;
    using Edge = E;
    using Node = N;
    struct Arm{
        Edge edge;
        Node node;
    };

    Container<Node,  vector<Arm> > container;

    optional<ll> n;
    Container_Graph(ll n={}) : n{n}, container() {}

    void newEdge(Node u, Node v, Edge edge=Void()){
        container[u].push_back({edge, v});
    }
    vector<Node> getNodes(){
        vector<Node> res;
        if(n.has_value()){
            for(ll i=1; i<=n.value(); i++) res.push_back(i);
        }
        else{
            for(auto& p : container){
                res.push_back(p.first);
            }
        }
        return res;

    }
    vector<Arm >& getEdges(Node node){
        return container[node];
    }
    vector<Node > getNeighbours(Node node){
        vector<Node> res;
        for(auto& arm : getEdges(node)){
            res.push_back(arm.node);
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
void readEdgeList(G& g, ll m, bool bidirectional=true){
    using Node = typename G::Node;
    using Edge = typename G::Edge;
    for(auto elem : readValues<tuple<Node, Node, Edge>, Node, Node, Edge >(m)){
        Node u, v;
        Edge edge;
        tie(u, v, edge) = elem;
        g.newEdge(u,v,edge);
        if(bidirectional) g.newEdge(v, u, edge);
    }
}

template<
    typename G,
    template<typename> typename QP,
    template<typename> typename P,
    typename F=void(*)(pair<typename P<G>::Info, typename G::Node>)
>
typename G::template Container<typename G::Node, typename P<G>::Info> queue_graph_algorithm(
    G& g,
    vector<pair<typename P<G>::Info, typename G::Node> > sources,
    F new_node_callback=[](pair<typename P<G>::Info, typename G::Node>){})
{
    
    using Path = P<G>;
    using Edge = typename G::Edge;
    using Node = typename G::Node;
    using Info = typename Path::Info;
    using Option = pair<Info, Node>;
    using QueuePolicy = QP<Option>;
    using Queue = typename QueuePolicy::Queue;

    Queue q;
    for(auto source : sources) QueuePolicy::push(q, source);
    typename G::template Container<Node, Info> d;
    while(!q.empty()){
        auto akt = QueuePolicy::consume(q);
        Node who = akt.second;
        Info info = akt.first;

        if(has_key(d, who)) continue;

        d[who] = info;
        
        new_node_callback(pair<Info, Node>(info, who));
        for(auto arm : g.getEdges(who)) if(!has_key(d, arm.node)){
            QueuePolicy::push(q, {Path::append({info, who}, arm.edge, arm.node), arm.node});
        }
    }
    return d;
}

/*template<template<typename> typename QP, template<typename> typename P>
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
*/

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
        return res;
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
struct SimpleJustLength{
    using Info = ll;
    static Info append(pair<Info, typename G::Node> from, typename G::Edge e, typename G::Node n){
        return from.first + 1;
    }
};


template<typename G>
struct LengthAndLastNode{
    using Info = pair<ll, typename G::Node>;
    static Info append(pair<Info, typename G::Node> from, typename G::Edge e, typename G::Node n){
        return {from.first + e, from.second};
    }
};

template<typename G>
struct SimpleLengthAndLastNode{
    using Info = pair<typename G::Edge, typename G::Node>;
    static Info append(pair<Info, typename G::Node> from, typename G::Edge e, typename G::Node n){
        return {from.first + 1, from.second};
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
