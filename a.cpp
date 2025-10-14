#include <bits/stdc++.h>
using namespace std;

using ll = long long;


template<typename ElementType, typename OperationType>
struct Ops{
	


	
  virtual ElementType identity() = 0;
  virtual ElementType zero() = 0; 

  virtual ElementType initialise(pair<ll, ll> range) = 0;

  virtual ElementType reduce(ElementType a, ElementType b) = 0;
  virtual ElementType apply(pair<ll, ll> range, ElementType value, OperationType change) = 0;
  virtual OperationType push(OperationType a, OperationType b) = 0;

};




template<typename ElementType, typename OperationType>
struct Segtree{
  using Policy = Ops<ElementType, OperationType>;
  using ElementType = typename Policy::ElementType;
  using OperationType = typename Policy::OperationType;
  Ops<ElementType, OperationType> policy;

  void main(){
    int x = policy.push(OperationType(), OperationType());
    
  }
};

int main(){
    
    return 0;
}