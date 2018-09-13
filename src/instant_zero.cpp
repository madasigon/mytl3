#include "base.cpp"

#ifndef INSTANT_ZERO_CPP
#define INSTANT_ZERO_CPP

//STARTCOPY
namespace mytl {

template<class T>
struct Resetter;

template<class T>
Resetter<T> global_resetter;

template<class T>
struct Resetter {
    using State = pair<ll, T>;

    State state;

    Resetter(){}
    Resetter(T value) : state{0, value} {};

    void reset(T value){
        state = {state.first+1, value};
    }

    struct Variable{

        State state;
        State& parent = global_resetter<T>.state;

        Variable();
        Variable(T value) : state{global_resetter<T>.state.first, value} {}
        Variable(State st) : state{st} {}
        Variable(T value, State& parent) : state{parent.first, value} {};

        bool fresh(){
            return state.first >= parent.first;
        }

        void overwrite(){
            state = parent;
        }

        bool refresh(){
            if(!fresh()) overwrite();
        }

        T get(){
            refresh();
            return state.second;
        }

        void survive(){
            state.first = parent.first;
        }

        void operator=(T new_value){
            state.second = new_value;
            survive();
        }

    };

};
}
//ENDCOPY

#endif
