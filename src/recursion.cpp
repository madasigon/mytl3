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
		optional<R>& res = table[arg];
		if (!res.has_value()) {
			res.set(fn(arg));
		}
		return res.value();
	};
}

template<template<typename, typename, typename...> typename C, typename Arg, typename R>
function<R(Arg)> memoize(R(*fn)(Arg)) {
	return __memoize<C<Arg, optional<R> >, Arg, R>(fn);
}

template<typename R>
function<R (ll) > quick_memoize(R(*fn)(ll)) {
	return __memoize<LazyVector<optional<R> >, ll, R>(fn);
}

template<typename R>
function<R(ll, ll)> quick_memoize(R(*fn)(ll, ll)) {
	LazyVector< LazyVector<optional<R> > > table;
	return [fn, table](ll p1, ll p2) mutable -> R {
		optional<R>& res = table[p1][p2];
		if (!res.has_value()) {
			res.set(fn(p1, p2));
		}
		return res.value();
	};
}


}
//ENDCOPY

#endif
