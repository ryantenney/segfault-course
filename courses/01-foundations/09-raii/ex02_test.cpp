// Exercise 02 — Tests (read-only)
//
// Verifies the FileHandle RAII wrapper.

#include <cstdio>
#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("01-09-ex02: File Handle Wrapper");

// Helper to create a temporary file path.
// Uses tmpnam-style naming but with a fixed prefix for clarity.
static std::string temp_path() {
    static int counter = 0;
    return "/tmp/segfault_ex02_" + std::to_string(counter++) + ".txt";
}

TEST(runner, "is_open returns true for valid file") {
    std::string path = temp_path();
    FileHandle fh(path.c_str(), "w");
    ASSERT_TRUE(fh.is_open());
}

TEST(runner, "is_open returns false for bad path") {
    FileHandle fh("/nonexistent/dir/file.txt", "r");
    ASSERT_FALSE(fh.is_open());
}

TEST(runner, "write and read_all round-trip") {
    std::string path = temp_path();
    {
        FileHandle writer(path.c_str(), "w");
        ASSERT_TRUE(writer.is_open());
        writer.write("Hello, RAII!");
    }
    // File is closed by destructor; now read it back
    {
        FileHandle reader(path.c_str(), "r");
        ASSERT_TRUE(reader.is_open());
        ASSERT_EQ(reader.read_all(), std::string("Hello, RAII!"));
    }
    std::remove(path.c_str());
}

TEST(runner, "destructor closes file (no double-close crash)") {
    std::string path = temp_path();
    {
        FileHandle fh(path.c_str(), "w");
        fh.write("test");
    }
    // If destructor didn't close properly, this might fail
    {
        FileHandle fh(path.c_str(), "r");
        ASSERT_TRUE(fh.is_open());
        ASSERT_EQ(fh.read_all(), std::string("test"));
    }
    std::remove(path.c_str());
}

TESTKIT_MAIN(runner)
