#include "base.cpp"
#include "convenience.cpp"

#ifndef MEMO_CPP
#define MEMO_CPP

//STARTCOPY
namespace mytl{

template <template<typename, typename...> typename Q, typename R, typename... Args>
function<R (Args...)> memoize(R (*fn)(Args...)) {
    Q<R, Args...> table = Q<R, Args...>();
    return [fn, table](Args... args) mutable -> R {
        auto res_ = table.get(args...);
        if(res_.has_value()){
            return res_.value();
        }
        else{
            auto res = fn(args...);
            table.set(args..., res);
            return res;
        }
    };
}
namespace memo{
template<typename R, typename Arg>
struct UnorderedMap : unordered_map<Arg, R>{
    optional<R> get(Arg arg){
        auto found = this->find(arg);
        if(found == this->end()){
            return {};
        }
        else{
            return (*this)[arg];
        }
    }

    void set(Arg arg, R r){
        (*this)[arg] = r;
    }
};

template<typename R, typename Arg>
struct Vector : mytl::LazyVector<optional<R> >{
    optional<R> get(Arg arg){
        return (*this)[arg];
    }
    void set(Arg arg, R res){
        (*this)[arg] = res;
    }
};

template<typename R, typename... Args>
struct Map : map<tuple<Args...>, R> {
    optional<R> get(Args... args){
        auto argt = make_tuple(args...);
        auto found = this->find(argt);
        if(found == this->end()){
            return {};
        }
        else{
            return {found->second};
        }
    }

    void set(Args... args, R r){
        (*this)[make_tuple(args...)] = r;
    }
};
}

}
//ENDCOPY

#endif
