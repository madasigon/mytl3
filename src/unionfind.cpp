#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifndef UNIONFIND_CPP
#define UNIONFIND_CPP

namespace mytl{
    struct UnionFind{
        UnionFind *father = nullptr;
        int mysize = 1;
        UnionFind(){};

        UnionFind* anc(){
            if(father == nullptr) return this;
            else{
                father = father->anc();
                return father;
            }
        }
        static bool together(UnionFind *a, UnionFind *b){
            return a->anc() == b->anc();
        }
        static void unite(UnionFind *a, UnionFind *b){
            UnionFind *anca = a->anc(), *ancb = b->anc();
            if(anca != ancb){
                if(anca->mysize > ancb->mysize){
                    ancb->father = anca;
                    anca->mysize += ancb->mysize;
                }
                else{
                    anca->father = ancb;
                    ancb->mysize += anca->mysize;
                }
            }
        }
    };
}

#endif
