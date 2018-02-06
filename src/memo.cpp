#include <bits/stdc++.h>
using namespace std;
#ifndef MEMO_CPP
#define MEMO_CPP

//STARTCOPY
namespace mytl{
    template <typename R, typename... Args>
    function<R (Args...)> memo(R (*fn)(Args...)) {
        map<tuple<Args...>, R> table;
        return [fn, table](Args... args) mutable -> R {
            auto argt = make_tuple(args...);
            auto memoized = table.find(argt);
            if(memoized == table.end()) {
                auto result = fn(args...);
                table[argt] = result;
                return result;
            } else {
                return memoized->second;
            }
        };
    }

    template <typename R, typename Arg>
    function<R (Arg)> unordered_memo(R (*fn)(Arg)) {
        unordered_map<Arg, R> table;
        return [fn, table](Arg arg) mutable -> R {
            auto memoized = table.find(arg);
            if(memoized == table.end()) {
                auto result = fn(arg);
                table[arg] = result;
                return result;
            } else {
                return memoized->second;
            }
        };
    }

    template <typename R, typename Arg>
    function<R (Arg)> natural_memo(R (*fn)(Arg)) {
        vector<pair<bool, R> > table;
        return [fn, table](Arg arg) mutable -> R {
            if(table.size() <= arg) table.resize(arg+1, {false, R()});
            if(!table[arg].first) {
                table[arg] = {true, fn(arg)};
            }
            return table[arg].second;
        };
    }
}
//ENDCOPY

#endif
