#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "base.cpp"

#include "convenience_test.cpp"
#include "geom_test.cpp"
#include "instant_zero_test.cpp"
#include "modulo_test.cpp"
#include "modulo_typesafe_test.cpp"
#include "pow_test.cpp"
#include "recursion_test.cpp"
#include "segtree_test.cpp"
#include "io_test.cpp"
#include "binary_search_test.cpp"
#include "tracker_test.cpp"
#include "container_test.cpp"
#include "trie_test.cpp"
#include "corasick_test.cpp"

TEST_CASE("Dummy", "[dummy]"){
    REQUIRE(1 == 1);
}
