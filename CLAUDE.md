# mytl3

A C++ competitive programming library with type-safe, template-based data structures.

## Project Structure

- [src/](src/) — Library source files. Each `.cpp` file contains a module (e.g. `segtree.cpp`, `modulo.cpp`). Code to be exported is wrapped between `//STARTCOPY` and `//ENDCOPY` markers.
- [templates/](templates/) — Starter files for CP solutions. The library is injected here.
- [codeforces_tests/](codeforces_tests/) — Correct Codeforces solutions that use the library. Also serve as integration tests. Naming: `{name}.{contest}.{problem}.cpp`.
- [python_util/](python_util/) — Python utility package for managing library injection.
- [unit_test/](unit_test/) — Unit tests for the library.
- [build/](build/) — Build artifacts.

## python_util (mytl-util CLI)

The `python_util` package is a utility for injecting the library into single-file CP submissions. Online judges require a single file, so the library code from `src/` is injected between `STARTCOPY`/`ENDCOPY` markers in target files.

**Install:**
```sh
uv pip install -e .
# or: pip install -e .
```

**Commands:**
```sh
mytl-util inject              # Inject library into all files in codeforces_tests/ and templates/
mytl-util inject FILE ...     # Inject into specific files only
mytl-util test-inject         # Check all target files are up to date (read-only, used in CI)
mytl-util --root PATH inject  # Run from a different project root
```

**How injection works:**
1. All `.cpp` files in `src/` are collected and sorted in dependency order (via `#include` topological sort).
2. The `STARTCOPY`/`ENDCOPY` blocks from each file are concatenated into one library string.
3. The library string replaces the content between `STARTCOPY`/`ENDCOPY` markers in target files.

## Key Library Concepts

- `int` is macro-blocked to prevent integer overflow bugs. Use `ll` (`long long`) instead. Use `need_int` only when `int` is truly needed.
- `debug_assert(expr)` — active in debug builds, stripped in optimized builds.
- Templates are used for type-agnostic data structures (e.g. `Node<Add_Sum<ll>>` for a segment tree).

## Adding a Codeforces Test

Copy your solution to `codeforces_tests/{name}.{contest_number}.{problem_letter}.cpp`, then run `mytl-util inject` to inject the current library.
