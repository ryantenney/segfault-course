---
title: "Lesson 23: Filesystem"
---

## Why This Lesson Exists

C++17 added `<filesystem>` (based on Boost.Filesystem), giving C++ portable,
built-in support for path manipulation, directory traversal, and file metadata
queries. Before this, every project either used platform-specific APIs or
pulled in Boost.

The filesystem library is essential for any program that reads configuration
files, scans directories, manages temporary files, or builds output paths.

## Key Concepts

### Path Construction and Joining

`std::filesystem::path` represents a filesystem path. The `/` operator joins
components with the platform-correct separator:

```cpp
namespace fs = std::filesystem;
fs::path dir = "/usr/local";
fs::path full = dir / "bin" / "app";  // "/usr/local/bin/app"
```

### Path Decomposition

Every path can be broken into its components:

```cpp
fs::path p = "/home/user/docs/report.txt";
p.parent_path()   // "/home/user/docs"
p.filename()      // "report.txt"
p.stem()          // "report"
p.extension()     // ".txt"
```

These methods work purely on the path string -- they do not touch the
filesystem.

### Filesystem Queries

```cpp
fs::exists(path)            // does the path exist?
fs::is_regular_file(path)   // is it a regular file?
fs::is_directory(path)      // is it a directory?
fs::file_size(path)         // size in bytes
fs::last_write_time(path)   // modification timestamp
```

### Directory Iteration

```cpp
// Non-recursive: one level
for (const auto& entry : fs::directory_iterator(dir)) { ... }

// Recursive: walks the entire tree
for (const auto& entry : fs::recursive_directory_iterator(dir)) { ... }
```

### Creating Directories

```cpp
fs::create_directory(path)     // create one directory (parent must exist)
fs::create_directories(path)   // create all missing directories (like mkdir -p)
```

### Error Handling

Most filesystem functions have two overloads: one that throws
`fs::filesystem_error` and one that takes a `std::error_code&`:

```cpp
std::error_code ec;
fs::create_directories(path, ec);
if (ec) { /* handle error without exceptions */ }
```

### RAII for Temporary Directories

A common pattern: wrap a temp directory in a class whose destructor calls
`fs::remove_all()`. This guarantees cleanup even when exceptions are thrown.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-23

# Build and test a single exercise
./run exercise 02-23-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Path Construction

**Files:** `ex01.h` (edit) - `ex01_test.cpp` (read-only)

Use `std::filesystem::path` and its `/` operator to join path components.
The library handles platform-specific separators for you.

### What to do

1. `join_paths()` -- join two path components using the `/` operator.
2. `build_filepath()` -- construct a file path from directory, stem, and
   extension.
3. `append_subdirs()` -- append a list of subdirectory names to a base path.

---

## Exercise 2: Path Decomposition

**Files:** `ex02.h` (edit) - `ex02_test.cpp` (read-only)

Extract the parts of a path using `stem()`, `extension()`, `parent_path()`,
and `filename()`. These work purely on the string representation -- no
filesystem access required.

### What to do

1. `get_extension()` -- return the file extension including the dot.
2. `get_stem()` -- return the filename without its extension.
3. `get_parent()` -- return the parent directory path.
4. `change_extension()` -- return a path with a different extension.

---

## Exercise 3: Existence and Type Checks

**Files:** `ex03.h` (edit) - `ex03_test.cpp` (read-only)

Use `fs::exists()`, `fs::is_regular_file()`, and `fs::is_directory()` to
inspect the filesystem. Learn the error_code overload for exception-free
queries.

### What to do

1. `path_status()` -- return "file", "directory", "not found", or "other".
2. `count_entries()` -- count immediate entries in a directory.
3. `path_exists_safe()` -- check existence using the error_code overload.

---

## Exercise 4: Directory Listing

**Files:** `ex04.h` (edit) - `ex04_test.cpp` (read-only)

Iterate over directory entries using `fs::directory_iterator`. Each entry
provides its path, type, and other metadata.

### What to do

1. `list_files()` -- list all regular file names in a directory, sorted.
2. `list_by_extension()` -- list files with a specific extension, sorted.
3. `count_files_and_dirs()` -- count regular files and subdirectories.

---

## Exercise 5: Recursive Listing

**Files:** `ex05.h` (edit) - `ex05_test.cpp` (read-only)

`fs::recursive_directory_iterator` walks an entire directory tree. You can
filter results and use `lexically_relative()` to get paths relative to a base.

### What to do

1. `find_all_files()` -- recursively find all regular files, return sorted
   relative paths.
2. `find_files_by_extension()` -- recursively find files with a given
   extension.
3. `find_files_skip_hidden()` -- recursively find files but skip any whose
   path passes through a hidden directory (name starts with '.').

---

## Exercise 6: File Size and Timestamps

**Files:** `ex06.h` (edit) - `ex06_test.cpp` (read-only)

`fs::file_size()` returns file size in bytes. `fs::last_write_time()` returns
a time point that can be compared directly to determine which file is newer.

### What to do

1. `get_file_size()` -- return the size of a file in bytes (0 if not a file).
2. `is_newer_than()` -- return true if file `a` was modified more recently
   than file `b`.
3. `find_largest_file()` -- find the largest file in a directory.

---

## Exercise 7: Create Directory Tree

**Files:** `ex07.h` (edit) - `ex07_test.cpp` (read-only)

`fs::create_directories()` creates a directory path including all intermediate
directories, like `mkdir -p`. Use the `error_code` overload for safe error
handling.

### What to do

1. `create_tree()` -- create multiple subdirectories under a base path.
2. `ensure_parent_exists()` -- ensure the parent directory of a file path
   exists.
3. `create_file_in_dir()` -- create a directory and a file inside it.

---

## Exercise 8: Temp Directory with RAII

**Files:** `ex08.h` (edit) - `ex08_test.cpp` (read-only)

Wrap a temporary directory in an RAII class. The constructor creates the
directory; the destructor removes it with `fs::remove_all()`. This guarantees
cleanup even when exceptions are thrown.

### What to do

1. Implement the `TempDirectory` class:
   - Constructor: create a unique directory inside a base path.
   - `path()`: return the directory path.
   - Destructor: remove the directory and all contents.
   - Non-copyable (delete copy operations).
2. `create_temp_file()` -- create a file inside a `TempDirectory` and
   return its path.
