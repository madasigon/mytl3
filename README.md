[![Codeforces Upload Tests](https://github.com/madasigon/mytl3/actions/workflows/cf-upload.yml/badge.svg)](https://github.com/madasigon/mytl3/actions/workflows/CI.yml)
[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/madasigon/mytl3) 


# Mytl3
A **C++** competitive programming library.

# Features

- *10-second setup!* (all functions in one file)
- Doesn't let you to use `int`, to prevent Integer Overflow Errors (unless you really want to, then use `need_int`). Use `ll` (short for `long long`) instead.
- Shortcuts for commonly used functionality (eg. `Mod107` for a Modulo 10^9+7 type,  `vector_memo` for memoization using `vector`s, etc...)
- Some convenience functions to simplify often occurring patterns such as memoizing a recursive function or making calculations modulo 10^9+7.
- Segment tree, Modulo Integer Class, Trie, Memoization using any underlying Data Structure
- Sample usage code snippet below every functionality
- Generality of Data Structures achieved using **C++ templates**
- Debug assertions in the code to minimise the chance of incorrect usage

# Another CP library?

Many CP libraries exist, but most have algorithms implemented for one specific type (eg. `Segment Tree` can only calculate sum of `int`-s), so they often can't be used without modifying the code.

Type-agnostic implementations eliminate the need to modify implementations for each use case by supplying use-case-specific logic via `C++` templates (eg. underlying Data Structure for Memoization, or the "sum" operation for Segment Tree)

In addition, this library has a focus on safety. For example, `int`-s are rarely a good idea to use in online CP contests, hence the macro preventing the appearance of `int` in the code (if you absolutely need `int`-s, use `need_int` which is a synonym).

# Examples

### Modulo 10^9+7:
```C++
mytl::Mod107 x = 43; //The value of x will always be calculated modulo 10^9+7. Mod107 is a synonym for TSModulo<100000007>
x = x / 2; //Mod107 works with all four elementary numeric operations
cout<<x.get(); //x.get() returns the numeric value of x
```
### Segment Tree (updating operation: addition, querying operation: sum):
```C++
mytl::Node<mytl::Add_Sum<long long> > tree({1,1e+10}); //Create a segment tree with 10^10 elements. As the name Add_Sum suggests, you can add a value to any range and query the sum of any range in O(log n) time.
tree.query({1, 10}, 2); //Add 2 to every element with index in the range {1, ... 10}.
cout<<tree.query({5,14}, 0); //Print the sum of elements with index in range {5, ... 14}.
```
### Unnecessary use of `int`:
```C++
int value_that_could_be_very_big; // compile error: macros prevent you from writing int in your code to prevent Integer Overflow
need_int not_big_value = 0; //OK! you can use 'need_int' if you really need int's
```
Further examples are in the `codeforces_tests` folder: these are correct solutions of Codeforces problems, that use the library.

# Install
Copy `templates/basic.cpp` into your editor and you can start making your solution right away (by modifying the `main` function).

# Contribute
- *Very easy:* if you use the library to solve a Codeforces problem, your solution becomes a test after you copy it under the path `codeforces_tests/{any_name}.{contest_number}.{problem_letter}.cpp`.
- To add/change the functionality itself, fork and make a pull request.
