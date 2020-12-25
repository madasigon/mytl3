from .populate import *
from .submit import *
from .util import *
import os
import time

def sync(library_path, src_path, dst_path):
    library = collect_dir(library_path)
    if not os.path.exists(dst_path):
        os.makedirs(dst_path)
    for filename in filename_list(src_path):
        transform(populate(library), os.path.join(src_path, filename), os.path.join(dst_path, filename))


def ask(text, type_):
    print(text)
    return type_(input())

def run_test(cf, library_path, src_path, dst_path):
    sync(library_path, src_path, dst_path)
    
    paths = abs_list(dst_path)

    def stampise(content):
        if content.split("\n")[0].startswith("//") and content.split("\n")[0].find("20") != -1:
            return "/n".join(["//" + time.ctime()] + content.split("\n")[1:])
        else:
            return "//" + time.ctime() + "\n" + content

    for path in paths:
        
        transform(stampise, path, path)

    return cf.check_n_solutions(paths)

    




