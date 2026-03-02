"""Command-line interface for mytl-util."""

from __future__ import annotations

import sys
from pathlib import Path

from .library import collect_library
from .inject import find_target_files, check_injection, perform_injection

# Target directories relative to project root
TARGET_DIRS = ["codeforces_tests", "templates"]
SRC_DIR = "src"

HELP_TEXT = """\
mytl-util: Manage library code injection for mytl3.

Usage:
  mytl-util <command> [options] [FILE ...]

Commands:
  inject        Inject current library code into target files.
  test-inject   Check that all target files are up to date (read-only).
  help          Show this help message.

Options:
  --root PATH   Project root directory (default: current working directory).

If FILE arguments are given, only those files are processed.
Otherwise all .cpp files in codeforces_tests/ and templates/ are used.
"""


def _resolve_root(root: Path) -> Path:
    """Validate that the project root contains the expected src/ directory."""
    src = root / SRC_DIR
    if not src.is_dir():
        print(f"Error: library source directory not found: {src}", file=sys.stderr)
        sys.exit(1)
    return root


def _collect_targets(root: Path) -> list[Path]:
    """Gather all .cpp target files from the configured directories."""
    dirs = [root / d for d in TARGET_DIRS]
    return find_target_files(*dirs)


def _resolve_targets(root: Path, files: list[str]) -> list[Path]:
    """Return explicit file paths if given, otherwise all default targets."""
    if files:
        targets = [Path(f).resolve() for f in files]
        for t in targets:
            if not t.is_file():
                print(f"Error: file not found: {t}", file=sys.stderr)
                sys.exit(1)
        return targets
    return _collect_targets(root)


def cmd_inject(root: Path, files: list[str]) -> None:
    """Inject library code into target files."""
    root = _resolve_root(root)
    library = collect_library(root / SRC_DIR)
    targets = _resolve_targets(root, files)

    modified = perform_injection(targets, library)

    if modified:
        print(f"Injected into {len(modified)} file(s):")
        for path in modified:
            print(f"  {path.relative_to(root)}")
    else:
        print("All files already up to date.")


def cmd_test_inject(root: Path, files: list[str]) -> None:
    """Check that all target files have current library code (no writes)."""
    root = _resolve_root(root)
    library = collect_library(root / SRC_DIR)
    targets = _resolve_targets(root, files)

    outdated = check_injection(targets, library)

    if outdated:
        print(
            f"Error: {len(outdated)} file(s) have outdated library code:",
            file=sys.stderr,
        )
        for path in outdated:
            print(f"  {path.relative_to(root)}", file=sys.stderr)
        sys.exit(1)
    else:
        print("All files are up to date.")


def _parse_args(argv: list[str]) -> tuple[str, Path, list[str]]:
    """Parse command-line arguments into (command, root, files).

    Returns a tuple of the subcommand name, the project root path,
    and any extra positional arguments (file paths).
    Exits with help text on parse failure.
    """
    root: Path | None = None
    positional: list[str] = []

    it = iter(argv)
    for arg in it:
        if arg == "--root":
            try:
                root = Path(next(it))
            except StopIteration:
                print("Error: --root requires a path argument.\n", file=sys.stderr)
                print(HELP_TEXT, file=sys.stderr)
                sys.exit(1)
        elif arg.startswith("-"):
            print(f"Error: unknown option '{arg}'.\n", file=sys.stderr)
            print(HELP_TEXT, file=sys.stderr)
            sys.exit(1)
        else:
            positional.append(arg)

    if root is None:
        root = Path.cwd()

    if not positional:
        print(HELP_TEXT, file=sys.stderr)
        sys.exit(1)

    return positional[0], root, positional[1:]


COMMANDS = {
    "inject": cmd_inject,
    "test-inject": cmd_test_inject,
}


def main() -> None:
    """Entry point for the mytl-util CLI."""
    command, root, files = _parse_args(sys.argv[1:])

    if command == "help":
        print(HELP_TEXT)
        return

    handler = COMMANDS.get(command)
    if handler is None:
        print(f"Error: unknown command '{command}'.\n", file=sys.stderr)
        print(HELP_TEXT, file=sys.stderr)
        sys.exit(1)

    handler(root, files)
