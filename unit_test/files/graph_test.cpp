#include "graph.cpp"
using namespace std;


using G = mytl::Container_Graph<ll, double, map>;
void graph_test(){

    G g(4);
    g.newEdge(4,3,0.5);
    g.newEdge(3,4,0.5);
    g.newEdge(3,1,2);
    g.newEdge(1,3,2);
    g.newEdge(1,2,1);
    g.newEdge(2,1,1);
    g.newEdge(2,4,2);
    g.newEdge(4,2,2);


    //using Dijkstra = mytl::AlgoComposer<mytl::Priority, mytl::JustLength>;
    //using BFS = mytl::AlgoComposer<mytl::FIFO, mytl::SimpleJustLength>;

    auto x = mytl::queue_graph_algorithm<G, mytl::Priority, mytl::JustLength>(g, {{0,1}});
    auto x_ = mytl::queue_graph_algorithm_from_single_source<G, mytl::Priority, mytl::JustLength>(g, 0, 1);

    assert((x == x_));

    auto y = mytl::queue_graph_algorithm<G,mytl::FIFO, mytl::SimpleJustLength>(g, {{0,1}});
    auto y_ = mytl::queue_graph_algorithm_from_single_source<G, mytl::FIFO, mytl::SimpleJustLength>(g, 0, 1);

    assert((y == y_));

    vector<pair<double,ll> > res;
    for(ll i=1; i<=g.n.value(); i++){
        res.push_back(pair<double,ll>(x[i],y[i]));
    }

    cout<<res<<endl;

    assert((res == vector<pair<double, ll> >{
            {0, 0},
            {
                1, 1//1
            },
            {
                2, 1//1
            },{
                2.5, 2//2
            }
            }));

}
