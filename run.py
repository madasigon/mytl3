import sys

from git import Repo


sys.path.insert(0, "./codeforces_tests/")
from autotest import run_test, collect_dir, sync
import autotest.config as config
import os
from autotest.util import write_file


def test(*args):
    results = run_test(config.LIBRARY_PATH, config.SRC_PATH, config.DST_PATH)
    if set([b for a, b in results]) == {'ACCEPTED'}:
        print("Great! All accepted.")
    else:
        print("Not great! Not all accepted.")
        import sys
        sys.exit(1)

def extract_to_templates(*args):
    sync(config.LIBRARY_PATH, config.TEMPLATE_PATH, config.TEMPLATE_PATH)

def before_commit(*args):
    extract_to_templates()
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

def check_extracted(*args):
    extract_to_templates()
    
    r = Repo('./')

    if r.is_dirty():
        print('Looks like templates haven\'nt been extracted, exiting with fail.')
        sys.exit(1)
    else:
        print("All extracted.")
    



available_operations = {
    "test": test,
    "extract": extract_to_templates,
    "precommit": before_commit,
    "add_module": add_module,
    "check-extracted": check_extracted
}



def main():
    import sys
    available_operations[sys.argv[1]](*sys.argv[2:])

main()
