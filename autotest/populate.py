from .util import *
from instance.config import STARTCOPY, ENDCOPY, MAGICWORD

is_start = contains(STARTCOPY)
is_end = contains(ENDCOPY)

def extract(content):
    lines = content.split("\n")
    return "\n".join(lines[first_good(is_start, lines)+1:first_good(is_end, lines)])

@curried(2)
def populate(library, content):
    lines = content.split("\n")
    where = first_good(is_start, lines)+1
    end = first_good(is_end, lines)-1
    del lines[where:end+1]
    lines.insert(where, library)
    return "\n".join(lines)

@curried(3)
def emplace(library, src, dest):
    transform(populate(library), src, dest)


def collect_dir(directory):
    return "\n".join(map(compose(extract, read_file), abs_list(directory)))


