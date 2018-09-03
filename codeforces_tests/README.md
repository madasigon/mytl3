# Directory for codeforces tests

The files should end with `<task_number>.<task_letter>.cpp`. For example if the given file is a solution to Codeforces challenge 1000A then it should end with `1000.A.cpp`.
The autotest will insert the newest version of the library between the `//STARTCOPY` and `//ENDCOPY` lines. The generated result will go with the same name to the `codeforces_temp` directory, then uploaded and tested for correctnes at Codeforces.