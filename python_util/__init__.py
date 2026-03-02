"""mytl-util: Library code injection utility for mytl3.

Collects C++ library source files from src/, resolves their dependencies,
and injects the merged library code into template and test files.
"""

from .library import collect_library
from .inject import check_injection, perform_injection, find_target_files

__all__ = [
    "collect_library",
    "check_injection",
    "perform_injection",
    "find_target_files",
]
