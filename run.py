import sys

sys.path.insert(0, "./codeforces_tests/")
from autotest import Codeforces, run_test, collect_dir
import autotest.config as config
import autotest.config.secret as secret
import os
from autotest.util import write_file


def test(*args):
    cf = Codeforces(*secret.credentials)
    all_accepted = True
    for file, result in list(run_test(cf, config.LIBRARY_PATH, config.SRC_PATH, config.DST_PATH)):
        print(file.split("/")[-1], "->", result)
        all_accepted = all_accepted and result == "Accepted"
    
    if all_accepted:
        print("Great! All accepted.")
    else:
        print("Not great! Not all accepted.")

def extract_to_file(*args):
    content = """//{}\n{}\n//{}""".format(config.STARTCOPY, collect_dir(config.LIBRARY_PATH), config.ENDCOPY)
    write_file("extracted.cpp", content)

def before_commit(*args):
    extract_to_file()
    test()

def add_module(name):
    write_file(f"src/{name}.cpp",f"""
#include "base.cpp"

#ifndef {name.upper()}_CPP
#define {name.upper()}_CPP

//STARTCOPY
namespace mytl{{



}}
//ENDCOPY

#endif""")
    write_file(f"unit_test/files/{name}_test.cpp",f"""
#include "{name}.cpp"
using namespace std;


void {name}_test(){{
    

}}""")

available_operations = {
    "test": test,
    "extract": extract_to_file,
    "precommit": before_commit,
    "add_module": add_module
}



def main():
    import sys
    available_operations[sys.argv[1]](*sys.argv[2:])

main()
