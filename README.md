[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/madasigon/mytl3) 

# Mytl3
A "library/framework" for online competitive programming in C++.
# Motivation
The goal of this project is to spare people's time from repeatedly typing frequently used algorithms, while also making it hard to make bugs or engage in bad habits. Focusing on the safety and speed of writing solutions in expense of runtime efficiency, some of its implementations may not be usable in case of strict time/memory limits. Nevertheless, some contest platforms, such as Codeforces, set relatively big time and memory limits for their tasks, making it usable most of the time.
# Features
- Macros to prevent risky usages of `int` instead of `long long`
- Some convenience functions for input/output.
- Some convenience functions to simplify often occuring patterns such as memoizing a recursive function or making calculations modulo 10^9+7.
- Some algorithms including graphs (Dijkstra's, DFS etc...), computational geometry (Graham Scan: *TODO*) and data structures (Segment Tree)
- All algorithms try to be as generic as possible, using C++ templates. This means you'll be able to do many kinds of things without having to modify the implementations. You'll only need to define what's specific to your case of usage, and pass these as template parameters.

# Examples
### Modulo 1000000007:
```C++
mytl::Mod107 x = 43; //The value of x will always be calculated modulo 10^9+7. Mod107 is a synonym for TSModulo<100000007>
x = x / 2; //now you can do whatever you want: add, subtract, multiply or divide
cout<<x.get(); //x.get() returns the numeric value of x
mytl::TSModulo<47> y = 3;
x = x + y; //Compile error: the type of x and y don't match. You can only operate between numbers of the same modulus.
```
### Segment Tree (updating operation: addition, querying operation: sum):
```C++
mytl::Node<mytl::Add_Sum<long long> > tree({1,1e+10}); //create a segment tree with 10^10 elements
tree.query({1, 10}, 2); //add 2 to every element in the range that's written in the curly brackets
cout<<tree.query({5,14}, 0); //print the sum of the elements in the given range
```
### Toughtless use of `int` instead of `long long`:
```C++
int value_that_could_be_very_big = 0; // compile error: you can't write 'int' in your program
need_int not_big_value = 0; //OK! you can use 'need_int' if you really need int's
```
*Further examples are in the codeforces_tests folder: these are correct solutions of Codeforces problems, that use the library.*
# Installation
Simply copy the contents of `extracted.cpp` to the top of your solution and leave out the standard includes like ```#include<bits/stdc++.h```. The library's functions are in the `mytl::` namespace. *You'll have to write* `MAIN main()` *instead of* `int main()`*, because writing `int something` is prohibited as a safety feature.*
# Contribute
- *There is a very easy way to contribute*: write a solution to a [Codeforces](http://codeforces.com/) problem, that uses this library. If you add this file to the codeforces_tests folder, it can always be automatically uploaded to Codeforces and tested, so that if a bug is introduced to the library, the solution may give **wrong answer** or some other error, indicating that something may be wrong with the current version of the library.
- *Also, any change propositions to the library itself are very welcome.*
