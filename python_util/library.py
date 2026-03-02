"""Collect and merge library source files with dependency resolution.

Reads all .cpp files from the library source directory, resolves their
#include dependencies via topological sort, extracts the code blocks
between STARTCOPY/ENDCOPY markers, and concatenates them into a single
library string suitable for injection.
"""

from __future__ import annotations

from pathlib import Path

STARTCOPY = "STARTCOPY"
ENDCOPY = "ENDCOPY"


def _find_marker(lines: list[str], marker: str) -> int:
    """Return the index of the first line containing the marker."""
    for i, line in enumerate(lines):
        if marker in line:
            return i
    raise ValueError(f"Marker '{marker}' not found")


def find_includes(filepath: Path) -> list[Path]:
    """Find local #include dependencies in a source file."""
    includes = []
    for line in filepath.read_text(encoding="utf-8").splitlines():
        if "#include" in line and '"' in line:
            included_name = line.split('"')[1]
            includes.append((filepath.parent / included_name).resolve())
    return includes


def extract_library_block(content: str) -> str:
    """Extract the code between STARTCOPY and ENDCOPY markers."""
    lines = content.splitlines()
    start = _find_marker(lines, STARTCOPY)
    end = _find_marker(lines, ENDCOPY)
    return "\n".join(lines[start + 1 : end])


def _topological_sort(deps: dict[Path, list[Path]]) -> list[Path]:
    """Sort files so that dependencies come before dependents.

    Uses a simple iterative algorithm: repeatedly find a file whose
    dependencies have all been resolved, append it to the order, and
    remove it from the remaining set.
    """
    remaining = {path: list(path_deps) for path, path_deps in deps.items()}
    resolved: set[Path] = set()
    order: list[Path] = []

    while remaining:
        # Find a file whose deps are all resolved (or external)
        ready = None
        for path, path_deps in remaining.items():
            if all(d in resolved or d not in remaining for d in path_deps):
                ready = path
                break

        if ready is None:
            # Circular dependency fallback: pick the first remaining file.
            ready = next(iter(remaining))

        order.append(ready)
        resolved.add(ready)
        del remaining[ready]

    return order


def collect_library(src_dir: Path) -> str:
    """Collect all library files in dependency order and merge their code.

    Args:
        src_dir: Path to the directory containing library .cpp files.

    Returns:
        A single string with all library code blocks concatenated.
    """
    cpp_files = sorted(src_dir.glob("*.cpp"))

    deps = {
        filepath.resolve(): find_includes(filepath)
        for filepath in cpp_files
    }

    order = _topological_sort(deps)

    blocks = [
        extract_library_block(filepath.read_text(encoding="utf-8"))
        for filepath in order
    ]

    return "\n".join(blocks)
