#include "../src/graph.cpp"
using namespace std;


using G = mytl::Container_Graph<ll, double, mytl::AssocVector>;
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


    using V = mytl::LazyVector<optional<typename mytl::Dijkstra<G>::Info> >;

    V x;
    mytl::LazyVector<optional<ll> > bfs;

    mytl::graph_algorithm<G, mytl::Dijkstra, V >(g, {{0,1}}, x);
    mytl::graph_algorithm<G, mytl::BFS, mytl::LazyVector<optional<ll> > >(g, {{0,1}}, bfs);

    vector<pair<double, ll> > res;

    for(ll i=1; i<=g.n.value(); i++){
        res.push_back({x[i].value(),bfs[i].value()});
    }

    assert((res == vector<pair<double, ll> >{
            {0, 0},
            {
                1, 1
            },
            {
                2, 1
            },{
                2.5, 2
            }
            }));

}
