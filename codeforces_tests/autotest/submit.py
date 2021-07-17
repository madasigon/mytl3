
from functools import wraps
from .util import *
import getpass


import subprocess
import multiprocessing

def submit(path):
    prob = "".join(path.split('.')[-3:-1])
    command = f'./cf submit {path} -prob={prob}'
    output = subprocess.run(command.split(), capture_output=True)
    if output.returncode != 0:
        raise RuntimeError((output.returncode, output.stderr))
    
    verdict = ''.join([c for c in output.stdout.decode('utf-8') if c.isupper()])

    if 'ACCEPTED' in verdict:
        verdict = 'ACCEPTED'
    
    return verdict

def test_directory(dst_path):
    paths = abs_list(dst_path)

    res = []
    for path in paths:
        verdict = submit(path)
        print(f'{path} -> {repr(verdict)}')
        res.append((path, verdict))

    return res
