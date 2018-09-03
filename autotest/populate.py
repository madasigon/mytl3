from .util import *
from instance.config import STARTCOPY, ENDCOPY, MAGICWORD

is_start = contains(STARTCOPY)
is_end = contains(ENDCOPY)

def extract(content):
    lines = content.split("\n")
    return "\n".join(lines[first_good(is_start, lines)+1:first_good(is_end, lines)])

@curried(2)
def populate(library, content):
    assert(content.count(MAGICWORD) == 1)
    return content.replace(MAGICWORD, library)

@curried(3)
def emplace(library, src, dest):
    transform(populate(library), src, dest)


def collect_dir(directory):
    return "\n".join(map(compose(extract, read_file), abs_list(directory)))


