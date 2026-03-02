"""Inject library code into target files.

Handles reading target .cpp files, replacing the content between
STARTCOPY/ENDCOPY markers with the collected library code, and
writing the result back (or comparing for verification).
"""

from __future__ import annotations

from pathlib import Path

from .library import STARTCOPY, ENDCOPY, _find_marker


def inject_into_content(content: str, library: str) -> str:
    """Replace the block between STARTCOPY and ENDCOPY with the library code."""
    lines = content.splitlines()
    start = _find_marker(lines, STARTCOPY)
    end = _find_marker(lines, ENDCOPY)

    result_lines = lines[: start + 1] + [library] + lines[end:]
    result = "\n".join(result_lines)

    # Preserve the original trailing newline if present.
    if content.endswith("\n") and not result.endswith("\n"):
        result += "\n"

    return result


def find_target_files(*directories: Path) -> list[Path]:
    """Find all .cpp files in the given directories."""
    files: list[Path] = []
    for directory in directories:
        if directory.is_dir():
            files.extend(sorted(directory.glob("*.cpp")))
    return files


def check_injection(targets: list[Path], library: str) -> list[Path]:
    """Check which files need injection updates.

    Returns:
        List of file paths whose current content differs from
        what it would be after injection.
    """
    outdated: list[Path] = []
    for filepath in targets:
        content = filepath.read_text(encoding="utf-8")
        expected = inject_into_content(content, library)
        if content != expected:
            outdated.append(filepath)
    return outdated


def perform_injection(targets: list[Path], library: str) -> list[Path]:
    """Inject library code into all target files in place.

    Returns:
        List of file paths that were actually modified.
    """
    modified: list[Path] = []
    for filepath in targets:
        content = filepath.read_text(encoding="utf-8")
        updated = inject_into_content(content, library)
        if content != updated:
            filepath.write_text(updated, encoding="utf-8")
            modified.append(filepath)
    return modified
