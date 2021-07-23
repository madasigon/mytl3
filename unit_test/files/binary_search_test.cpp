
#include "binary_search.cpp"
using namespace std;


TEST_CASE("Discrete Binary Search", "[binary_search]"){
    function<function<bool(ll)>(ll)> pred = [](ll limit){
        return [limit](ll x){
            return x <= limit;
        };
    };

    SECTION("Limit is in middle of range"){
        ll limit = 123456789;
        REQUIRE(mytl::discrete_binary_search(1LL, limit*2+43242432,pred(limit)) == limit);
    }

    SECTION("Limit is in left end of range"){
        REQUIRE(mytl::discrete_binary_search(1,10,pred(1)) == 1);
    }

    SECTION("Limit is below left end of range"){
        REQUIRE_THROWS_AS(mytl::discrete_binary_search(1,10,pred(0)), DebugAssertionError);
    }

    SECTION("Limit is in right end of range"){
        REQUIRE(mytl::discrete_binary_search(1,10,pred(10)) == 10);
    }

    SECTION("Limit is over range"){
        REQUIRE(mytl::discrete_binary_search(1,10,pred(100)) == 10);
    }

    for(ll i=1; i<=30; i++){
        DYNAMIC_SECTION("Binary Search is correct when answer is: " << i){
            REQUIRE(mytl::discrete_binary_search(1,100,pred(i)) == min(100LL,i));
        }
    }
}

TEST_CASE("Continuous Binary Search", "[binary_search]"){
    function<function<bool(double)>(double)> pred = [](double limit){
        return [limit](double x){
            return x <= limit;
        };
    };

    SECTION("Limit is below range"){
        REQUIRE(mytl::continuous_binary_search(0.0,10.0,100, pred(-10)) == Approx(0));
    }

    SECTION("Limit is above range"){
        REQUIRE(mytl::continuous_binary_search(0.0,10.0,100, pred(20)) == Approx(10));
    }

    SECTION("Limit is inside range"){
        double limit = 4.24234234;
        REQUIRE(mytl::continuous_binary_search(0.0,10.0,100, pred(limit)) == Approx(limit));
    }
}