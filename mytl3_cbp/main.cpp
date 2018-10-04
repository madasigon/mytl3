#include "../src/base.cpp"

#include "../test/convenience_test.cpp"
#include "../test/geom_test.cpp"
#include "../test/graph_test.cpp"
#include "../test/instant_zero_test.cpp"
#include "../test/modulo_test.cpp"
#include "../test/modulo_typesafe_test.cpp"
#include "../test/pow_test.cpp"
#include "../test/recursion_test.cpp"
#include "../test/segtree_test.cpp"

MAIN main(){
    convenience_test();
    geom_test();
    graph_test();
    instant_zero_test();
    modulo_test();
    modulo_typesafe_test();
    pow_test();
    recursion_test();
    segtree_test();
}
