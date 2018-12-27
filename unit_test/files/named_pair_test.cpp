
#include "named_pair.cpp"
using namespace std;


NAMED_PAIR(TestPair,thisone,thatone)


void named_pair_test(){

    TestPair<ll,ll> csoki{3,4}, szaloncukor{3,3};
    assert((
        (csoki.thisone >= szaloncukor.thatone)
        &&
        (szaloncukor < csoki)
    ));

}