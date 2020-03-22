#include "base.cpp"
#include "convenience.cpp"

#ifndef MEMO_CPP
#define MEMO_CPP

//STARTCOPY
namespace mytl{

template <template<typename, typename, typename...> typename C, typename Arg, typename R>
function<R (Arg)> memoize(R (*fn)(Arg)) {
    C<Arg, R* > table;
    return [fn, table](Arg arg) mutable -> R {
        R*& res = table[arg];
        if(res == nullptr){
			res = new R;
			*res = fn(arg);
        }
		return *res;
    };
}


}
//ENDCOPY

#endif
