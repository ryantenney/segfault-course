// Exercise 02: File Handle Wrapper
//
// PROBLEM:
//   C-style FILE* requires manual fclose(). If you forget — or if an
//   exception occurs before fclose — you leak the file handle. RAII
//   wraps the FILE* so the destructor always calls fclose().
//
// TODO:
//   Implement the FileHandle class:
//   - Constructor: open the file with fopen(path, mode)
//   - Destructor: close the file with fclose() if it was opened
//   - is_open(): return whether the file was opened successfully
//   - write(): write a string to the file using fputs()
//   - read_all(): read the entire file contents into a std::string
//
// WHY:
//   This is the fundamental RAII pattern: acquire in constructor,
//   release in destructor. std::fstream does this automatically,
//   but building it yourself reveals the mechanics.

#pragma once
#include <cstdio>
#include <string>
#include <testkit/testkit.h>

class FileHandle {
    // TODO: Add a FILE* member, initialized to nullptr
public:
    // Open a file. Store the FILE* from fopen(path, mode).
    FileHandle(const char* path, const char* mode) {
        TODO();
    }

    // Close the file if it was opened.
    ~FileHandle() {
        // TODO: if file_ is not null, call fclose(file_)
    }

    // Return true if the file was opened successfully.
    bool is_open() const {
        TODO();
    }

    // Write a string to the file using fputs().
    void write(const char* text) {
        TODO();
    }

    // Read the entire file contents into a std::string.
    // Use fread or fgetc in a loop.
    std::string read_all() {
        TODO();
    }

    // Prevent copying (we'll learn why in exercise 08)
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
};
