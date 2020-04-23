
#include "tracker.cpp"
using namespace std;


void tracker_test(){
    mytl::Tracker<ll, mytl::min> t;

    t.update(2);
    t.update(3);
    t.update(1);
    debug_assert(t.value() == 1);

}