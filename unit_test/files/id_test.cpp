
#include "id.cpp"
using namespace std;


void id_test(){
    mytl::Id x = 3, y = 4;
    string alma="abcde";
    alma[x] = 'e';
    assert((alma == "abcee"));
    assert((
        x < y && y > x && x != y && !(x == y)
    ));

}