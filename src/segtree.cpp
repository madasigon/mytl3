#include "base.cpp"

#ifndef SEGTREE_CPP
#define SEGTREE_CPP

//STARTCOPY
namespace mytl{
template<class Op>
struct DynamicSegtree {
	using T = typename Op::T;
	using Change = typename Op::Change;
	using Range = pair<ll, ll>;

	DynamicSegtree<Op> *left_child = NULL, *right_child = NULL;

	T partial;
	Change pending = Op::identity();
	Range my_range;
	
	DynamicSegtree(Range range) : my_range{range}, partial{ Op::initial(range) } {};

	
	
	

	DynamicSegtree(Range range, function<T(ll)> getter) {
		my_range = range;
		if(range.first == range.second){
			partial = getter(range.first);
		}
		else{
			pair<ll,ll> range_left_half = {my_range.first, my_range.first + (my_range.second - my_range.first)/2};
			pair<ll,ll> range_right_half = {range_left_half.second + 1, my_range.second};

			if (left_child == NULL) left_child = (new DynamicSegtree(range_left_half,getter));
			if (right_child == NULL) right_child = (new DynamicSegtree(range_right_half,getter));
			partial = Op::reduce(left_child->partial, right_child->partial);
		}

	}


	void add(Change change) {
		pending = Op::push(pending, change);
	}

	void flush() {
		if (my_range.first < my_range.second) {
			pair<ll,ll> range_left_half = {my_range.first, my_range.first + (my_range.second - my_range.first)/2};
			pair<ll,ll> range_right_half = {range_left_half.second + 1, my_range.second};

			if (left_child == NULL) left_child = (new DynamicSegtree(range_left_half));
			if (right_child == NULL) right_child = (new DynamicSegtree(range_right_half));
			left_child->add(pending);
			right_child->add(pending);
		}
		partial = Op::apply(my_range.second - my_range.first+1, partial, pending);
		pending = Op::identity();
	}

	T _update(Range range, Change change) {
		if (range.first <= my_range.first && my_range.second <= range.second) {
			add(change);
			flush();
			return partial;
		}
		flush();
		if (range.first > my_range.second || range.second < my_range.first)  return partial;
		
		auto from_left = left_child->_update(range, change);
		auto from_right = right_child->_update(range, change);
		partial = Op::reduce(from_left, from_right);
		return partial;
	}
	void update(Range range, Change change) {
		_update(range, change);
	}

	T query(Range range) {
		if(range.second < my_range.first || my_range.second < range.first) return Op::zero();
		flush();
		if(range.first <= my_range.first && my_range.second <= range.second) return partial;
		return Op::reduce(left_child->query(range), right_child->query(range));
	}
};



template<typename T_, typename Range_>
struct Add_Sum {
	using Range = Range_;
	using T = T_;
	using Change = T_;

	static Change identity() {
		return 0;
	}

	static T zero() {
		return 0;
	}

	static T initial(Range r) {
		return zero();
	}

	static T reduce(T a, T b) {
		return a + b;
	}

	static T apply(Range r, T a, Change c) {
		return a + r.span()*c;
	}

	static Change push(Change a, Change b) {
		return a + b;
	}
};

template<typename T_, typename Range_>
struct Multiply_Sum {
	using Range = Range_;
	using T = T_;
	using Change = T_;

	static Change identity() {
		return 1;
	}

	static T zero() {
		return 0;
	}

	static T initial(Range r) {
		return r.span() * 1;
	}

	static T reduce(T a, T b) {
		return a + b;
	}

	static T apply(Range r, T a, Change c) {
		return a * c;
	}

	static Change push(Change a, Change b) {
		return a * b;
	}
};


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
//ENDCOPY

#endif
