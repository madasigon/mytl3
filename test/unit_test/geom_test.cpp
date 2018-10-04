#include <bits/stdc++.h>
//#include "../cbp/test.h"
#include "../../src/geom.cpp"
using namespace std;

template <typename R, typename Arg>
function<R (Arg)> natural_memo(R (*fn)(Arg)) {
    vector<pair<bool, R> > table;
    return [fn, table](Arg arg) mutable -> R {
        if(table.size() <= arg) table.resize(arg+1, {false, R()});
        if(!table[arg].first) {
            table[arg] = {true, fn(arg)};
        }
        return table[arg].second;
    };
}




void geom_test(){
    assert((mytl::Point{0,0}.direction({1,1}, {2,1}) == -1
         && mytl::Point{0,0}.direction({2,2}, {1,1}) == 0
         && mytl::Point{0,0}.direction({-1,1}, {1, -1}) == 0)
         && mytl::inside({{0,0},{3,0},{0,3}}, {1,1}, true)
         && mytl::inside({{0,0},{3,0},{0,3}}, {2,1}, false));

}
