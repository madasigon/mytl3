#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifndef UNIONFIND_CPP
#define UNIONFIND_CPP

namespace mytl{
    struct UnionFind{
        vector<int> t, mysize;
        UnionFind(int n) : t(n+1, -2), mysize{n+1, 1} {};

        int anc(int x){
            if(t[x] == -2) return x;
            else{
                t[x] = anc(t[x]);
                return t[x];
            }
        }
        bool together(int a, int b){
            return anc(a) == anc(b);
        }
        void unite(int a, int b){
            int anca = anc(a), ancb = anc(b);
            if(anca != ancb){
                if(mysize[anca] > mysize[ancb]){
                    t[ancb] = anca;
                    mysize[anca] += mysize[ancb];
                }
            }
        }
    };
}

#endif
