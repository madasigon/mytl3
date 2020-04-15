#include "base.cpp"
#include "convenience.cpp"
#include "container.cpp"
#ifndef MEMO_CPP
#define MEMO_CPP

//STARTCOPY
namespace mytl {

template <typename C, typename Arg, typename R>
function<R(Arg)> __memoize(R(*fn)(Arg)) {
	C table;
	return [fn, table](Arg arg) mutable -> R {
		if (!table[arg].has_value()) {
			table[arg].set(fn(arg));
		}
		return table[arg].value();
	};
}

template<template<typename, typename, typename...> typename C, typename Arg, typename R>
function<R(Arg)> memoize(R(*fn)(Arg)) {
	return __memoize<C<Arg, optional<R> >, Arg, R>(fn);
}

template<typename R>
function<R (ll) > quick_memoize(R(*fn)(ll)) {
	return __memoize<TwoWayLazyVector<optional<R> >, ll, R>(fn);
}

template<typename R>
function<R(ll, ll)> quick_memoize(R(*fn)(ll, ll)) {
	TwoWayLazyVector< TwoWayLazyVector<optional<R> > > table;
	return [fn, table](ll p1, ll p2) mutable -> R {
		if(!table[p1][p2].has_value()){
			table[p1][p2].set(fn(p1, p2));
		}
		return table[p1][p2].value();
	};
}


}
//ENDCOPY

#endif
