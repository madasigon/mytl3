#include "convenience.cpp"
#include "segtree.cpp"
using namespace std;



struct My_Add_Sum {
	using Range = pair<ll, ll>;
	using T = ll;
    using Change = ll;

	static Change identity() {
		return 0;
	}

	static T zero() {
		return 0;
	}

	static T initial(Range r) {
		return zero();
	}

	static T reduce(T a, T b) {
		return a + b;
	}

	static T apply(ll k, T a, Change c) {
		return a + k*c;
	}

	static Change push(Change a, Change b) {
		return a + b;
	}
};


void test_segtree_1_10(mytl::DynamicSegtree<My_Add_Sum> &segtree){
    segtree.update({1, 10}, 1);
    segtree.update({2,4}, 2);
    debug_assert(segtree.query({1, 3}) == 7);
    debug_assert(segtree.query({4, 10}) == 9);
    debug_assert(segtree.query({1, 10}) == 16);
}

void segtree_test(){
    mytl::DynamicSegtree<My_Add_Sum> segtree({0, 10});
    test_segtree_1_10(segtree);
    mytl::DynamicSegtree<My_Add_Sum> segtree2({0, 10}, [](ll i){return 0;});
    test_segtree_1_10(segtree2);
}
