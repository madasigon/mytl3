#include "base.cpp"

#ifndef SEGTREE_CPP
#define SEGTREE_CPP

//STARTCOPY
namespace mytl{
template<class Op>
struct Node : Op::Range{
    using Range = typename Op::Range;
    using T = typename Op::T;
    using Change = typename Op::Change;
    using Range::singleton;
    using Range::inside;
    using Range::intersect;
    using Range::leftHalf;
    using Range::rightHalf;

    Node *left_child=NULL, *right_child=NULL;

    T partial;
    Change pending = Op::identity();

    Node(Range range) : Range(range), partial{Op::initial(range)} {};

    T query(Range range, Change change){
        return query_(range, change).first;
    }

    void add(Change change){
        pending = Op::push(pending, change);
    }

    void prepare(){
        if(!singleton()){
            if(left_child == NULL) left_child = (new Node(leftHalf()));
            if(right_child == NULL) right_child = (new Node(rightHalf()));
            left_child->add(pending);
            right_child->add(pending);
        }
        partial = Op::apply(*this, partial, pending);
        pending = Op::identity();
    }

    pair<T,T> query_(Range range, Change change){
        //cout<<range<<" "<<*this<<endl;
        prepare();
        if(inside(range)){
            add(change);
            prepare();
            return {partial, Op::zero()};
        }
        if(!intersect(range)){
            //cout<<"n"<<range<<" "<<*this<<endl;
            return {Op::zero(), partial};
        }

        auto from_left = left_child->query_(range, change);
        auto from_right = right_child->query_(range, change);
        //cout<<from_right.first<<endl;
        auto needed = Op::reduce(from_left.first, from_right.first), rest = Op::reduce(from_left.second, from_right.second);
        partial = Op::reduce(needed, rest);
        return {needed, rest};
    }

    T build_from(const function<T(ll)>& getter){
        prepare();
        pending = Op::identity();
        if(singleton()) partial = getter(this->first);
        else partial = Op::reduce(left_child->build_from(getter), right_child->build_from(getter));
        return partial;
    }

};

struct Range1D : pair<ll,ll>{
    using pair<ll,ll>::pair;

    ll span() const {
        return second-first+1;
    }
    bool singleton() const {
        return span() == 1;
    }
    Range1D leftHalf() const {
        return Range1D(first, (first+second)/2);
    }
    Range1D rightHalf() const {
        return Range1D((first + second)/2 + 1, second);
    }
    bool inside(const Range1D& other) const {
        return other.first <= first && second <= other.second;
    }
    bool intersect(const Range1D& other) const {

        return other.inside(*this)
             ||(other.first <= first && first <= other.second)
             ||(other.first <= second && second <= other.second);
    }
};


}
//ENDCOPY


//STARTCOPY: predef opsets
namespace mytl{
/*
struct Custom_Op{
    using Range = _;
    using T = _;
    using Change = _;

    static Change identity(){
        return _;
    }

    static T zero(){
        return _;
    }

    static T initial(Range r){
        return _;
    }

    static T reduce(T a, T b){
        return _;
    }

    static T apply(Range r, T a, Change c){
        return _;
    }

    static Change push(Change a, Change b){
        return _;
    }

};
*/

}


#endif
