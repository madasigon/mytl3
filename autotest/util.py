from functools import wraps
import os
def curried(numargs):
    def curried_(fn, args=None):
        args = args or ()
        @wraps(fn)
        def curried_wrapper(*new_args):
            if len(args + new_args) < numargs:
                return curried_(fn, args + new_args)
            else:
                return fn(*(args + new_args))
        return curried_wrapper
    return curried_


@curried(3)
def compose(f, g, x):
    return f(g(x))

@curried(2)
def contains(s, h):
    return h.find(s) != -1

@curried(2)
def first_good(pred, l):
    return next(i for (i, v) in enumerate(l) if pred(v))


def read_file(path):
    with open(path, "r") as file:
        res = file.read()
    return res

@curried(2)
def write_file(path, content):
    if type(content) != bytes:
        content = content.encode("utf-8")
    with open(path, "wb") as file:
        file.write(content)

def transform(f, src, dst):
    write_file(dst)(f(read_file(src)).encode("utf-8"))

def filename_list(directory):
    return  list(next(os.walk(directory))[2])

def abs_list(directory):
    return [os.path.join(os.path.abspath(directory), filename) for filename in filename_list(directory)]

