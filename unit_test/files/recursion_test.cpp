
//#include "../cbp/test.h"
#include "recursion.cpp"
#include "container.cpp"
using namespace std;



ll natural_(ll x);
auto natural = mytl::quick_memoize(natural_);
ll natural_(ll x){
    if(x < 3) return 1;
    else return natural(x-1) + natural(x-2);
}

ll grid_(ll a, ll b);
auto grid = mytl::quick_memoize(grid_);
ll grid_(ll a, ll b) {
	if (min(a, b) == 0) return 0;
	else return 1 + grid(a - 1, b - 1);
}

ll unordered_(ll x);
auto unordered = mytl::memoize<map, ll, ll>(unordered_);
ll unordered_(ll x){
    if(x < 3) return 1;
    else return unordered(x-1) + unordered(x-2);
}

ll ordered_(ll x);
auto ordered = mytl::memoize<unordered_map, ll, ll>(ordered_);
ll ordered_(ll x){
    if(x < 3) return 1;
    else return ordered(x-1) + ordered(x-2);
}


ll slow(ll i){
    if(i < 3) return 1;
    return slow(i-1) + slow(i-2);
}



void recursion_test(){
    assert(slow(30) == natural(30));
    assert(slow(30) == ordered(30));
    assert(slow(30) == unordered(30));
	assert(15 == grid(15, 16));
}
