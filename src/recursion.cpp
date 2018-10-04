#include "base.cpp"
#include "convenience.cpp"

#ifndef MEMO_CPP
#define MEMO_CPP

//STARTCOPY
namespace mytl{

template <template<typename, typename> typename Q, typename Arg, typename R>
function<R (Arg)> memoize(R (*fn)(Arg)) {
    Q<Arg, optional<R> > table;
    return [fn, table](Arg arg) mutable -> R {
        optional<R>& res = table[arg];
        if(!res.has_value()){
            res = fn(arg);
        }
        return res.value();
    };
}


}
//ENDCOPY

#endif
