from .populate import *
from .submit import *
from .util import *
import os

def sync(library_path, src_path, dst_path):
    library = collect_dir(library_path)
    for filename in filename_list(src_path):
        transform(populate(library), os.path.join(src_path, filename), os.path.join(dst_path, filename))


def ask(text, type_):
    print(text)
    return type_(input())

def run_test(cf, library_path, src_path, dst_path):
    sync(library_path, src_path, dst_path)
    
    return cf.test_directory(dst_path)

    




