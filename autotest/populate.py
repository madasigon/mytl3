from .util import *
from instance.config import STARTCOPY, ENDCOPY, MAGICWORD
import os

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

def dependencies(filepath):
    filepath = os.path.abspath(filepath)
    def include(line):
        if "#include" not in line or "\"" not in line:
            return None
        return os.path.join(os.path.dirname(filepath), line.split("\"")[1])
    return list(filter(lambda x: x is not None, map(include, read_file(filepath).split("\n"))))      

def collect_dir(directory):
    graph = dict((filepath, dependencies(filepath)) for filepath in abs_list(directory))
    order = []
    while graph:
        removable = list(graph.keys())[0]
        while graph[removable]:
            removable = graph[removable][0]
        
        for _, val in graph.items():
            if removable in val: val.remove(removable)
        del graph[removable]
        
        order.append(removable)
    
        
    print(order)    
    return "\n".join(map(compose(extract, read_file), order))    


