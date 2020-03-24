#include "base.cpp"

#ifndef SEGTREE_CPP
#define SEGTREE_CPP

//STARTCOPY
namespace mytl{
template<class Op>
struct IntervalTree : Op::Range {
	using Range = typename Op::Range;
	using T = typename Op::T;
	using Change = typename Op::Change;
	using Range::singleton;
	using Range::inside;
	using Range::intersect;
	using Range::leftHalf;
	using Range::rightHalf;

	IntervalTree *left_child = NULL, *right_child = NULL;

	T partial;
	Change pending = Op::identity();

	IntervalTree(Range range) : Range(range), partial{ Op::initial(range) } {};

	T query(Range range, Change change) {
		return query_(range, change).first;
	}

	void add(Change change) {
		pending = Op::push(pending, change);
	}

	void prepare() {
		if (!singleton()) {
			if (left_child == NULL) left_child = (new IntervalTree(leftHalf()));
			if (right_child == NULL) right_child = (new IntervalTree(rightHalf()));
			left_child->add(pending);
			right_child->add(pending);
		}
		partial = Op::apply(*this, partial, pending);
		pending = Op::identity();
	}

	pair<T, T> query_(Range range, Change change) {
		//cout<<range<<" "<<*this<<endl;
		prepare();
		if (inside(range)) {
			add(change);
			prepare();
			return { partial, Op::zero() };
		}
		if (!intersect(range)) {
			//cout<<"n"<<range<<" "<<*this<<endl;
			return { Op::zero(), partial };
		}

		auto from_left = left_child->query_(range, change);
		auto from_right = right_child->query_(range, change);
		//cout<<from_right.first<<endl;
		auto needed = Op::reduce(from_left.first, from_right.first), rest = Op::reduce(from_left.second, from_right.second);
		partial = Op::reduce(needed, rest);
		return { needed, rest };
	}

	T build_from(const function<T(ll)>& getter) {
		prepare();
		pending = Op::identity();
		if (singleton()) partial = getter(this->l);
		else partial = Op::reduce(left_child->build_from(getter), right_child->build_from(getter));
		return partial;
	}

};


template<typename Op>
class SegmentTree {
public:
	const pair<ll, ll> range;
private:
	vector<typename Op::T> t;
	vector<typename Op::Change> d;
	ll n;
	ll h;

	void __calc(ll p, ll k) {
		t[p] = Op::apply(k, Op::reduce(t[p * 2], t[p * 2 + 1]), d[p]);
	}

	void __apply(ll p, typename Op::Change value, ll k) {
		t[p] = Op::apply(k, t[p], value);
		if (p < n) d[p] = Op::push(d[p], value);
	}

	void __build(ll l, ll r) {
		ll k = 2;
		l += n;
		r += n - 1;
		for (; l > 1; k *= 2) {
			l /= 2;
			r /= 2;
			for (ll i = r; i >= l; i--) __calc(i, k);
		}
	}

	void __push(ll l, ll r) {
		ll s = h;
		ll k = 1 << (h - 1);

		l += n;
		r += n - 1;
		for (; s > 0; s--, k /= 2) {
			for (ll i = l >> s; i <= r >> s; i++) {
				__apply(i * 2, d[i], k);
				__apply(i * 2 + 1, d[i], k);
				d[i] = Op::identity();
			}
		}
	}

	void __modify(ll l, ll r, typename Op::Change value) {
		__push(l, l + 1);
		__push(r - 1, r);
		ll l0 = l, r0 = r, k = 1;

		l += n;
		r += n;
		for (; l < r; l /= 2, r /= 2, k *= 2) {
			if (l & 1) __apply(l++, value, l);
			if (r & 1) __apply(--r, value, k);
		}
		__build(l0, l0 + 1);
		__build(r0 - 1, r0);
	}

	typename Op::T __query(ll l, ll r) {
		__push(l, l + 1);
		__push(r - 1, r);
		typename Op::T resl = Op::zero(), resr = Op::zero();

		l += n;
		r += n;

		for (; l < r; l /= 2, r /= 2) {
			if (l & 1)  resl = Op::reduce(resl, t[l++]);
			if (r & 1) resr = Op::reduce(t[--r], resr);
		}
		return Op::reduce(resl, resr);

	}

public:

	SegmentTree(pair<ll, ll> range, const function<typename Op::T(ll)>& getter) : range{ range } {
		n = range.second - range.first + 1;
		t.resize(n * 2);
		d.resize(n, Op::identity());
		for (ll i = 0; i < n; i++) {
			t[i + n] = getter(i);
		}
		for (ll i = n - 1; i > 0; i--) t[i] = t[i * 2] + t[i * 2 + 1];
		h = 0;
		ll new_n = n;
		while (new_n > 0) {
			h++;
			new_n /= 2;
		}

	}

	typename Op::T query(pair<ll, ll> query_range) {
		return __query(query_range.first - range.first, query_range.second - range.first + 1);
	}
	void modify(pair<ll, ll> modify_range, typename Op::Change value) {
		__modify(modify_range.first - range.first, modify_range.second - range.first + 1, value);
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
