# Directory for codeforces tests

The files should end with `<tested_file_1_name>.[<tested_file_2_name....]<task_number>.<task_letter>.cpp`.

For example if the given file is a solution to Codeforces challenge 1000A and it makes use of the segtree.cpp and the modulo.cpp file, it's name should be `segtree.modulo.1000.A.cpp`

The autotest will insert the newest version of the library between the `//STARTCOPY` and `//ENDCOPY` lines. The generated result will go with the same name to the `codeforces_temp` directory, then uploaded and tested for correctnes at Codeforces.

Currently they are being tested with the `c++14` option at Codeforces.