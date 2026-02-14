// Exercise 08 -- Tests (read-only)

#include <fstream>
#include <sstream>
#include <testkit/testkit.h>

#include "ex08.h"

namespace {

std::string read_file(const fs::path& p) {
    std::ifstream ifs(p);
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

} // namespace

static testkit::TestRunner runner("02-23-ex08: Temp Directory with RAII");

TEST(runner, "TempDirectory creates a directory") {
    auto base = fs::temp_directory_path();
    TempDirectory tmp(base, "test-create");
    ASSERT_TRUE(fs::is_directory(tmp.path()));
}

TEST(runner, "TempDirectory path is inside base path") {
    auto base = fs::temp_directory_path();
    TempDirectory tmp(base, "test-base");
    // The directory should be a child of base
    auto rel = tmp.path().lexically_relative(base);
    ASSERT_FALSE(rel.empty());
    ASSERT_TRUE(rel.string().find("..") == std::string::npos);
}

TEST(runner, "TempDirectory cleans up on destruction") {
    auto base = fs::temp_directory_path();
    fs::path saved_path;
    {
        TempDirectory tmp(base, "test-cleanup");
        saved_path = tmp.path();
        // Create a file inside to verify cleanup removes contents
        std::ofstream(saved_path / "data.txt") << "temp data";
        ASSERT_TRUE(fs::exists(saved_path));
    }
    // After destruction, the directory should be gone
    ASSERT_FALSE(fs::exists(saved_path));
}

TEST(runner, "TempDirectory creates unique directories") {
    auto base = fs::temp_directory_path();
    TempDirectory tmp1(base, "test-unique");
    TempDirectory tmp2(base, "test-unique");
    ASSERT_NE(tmp1.path().string(), tmp2.path().string());
}

TEST(runner, "create_temp_file creates file with content") {
    auto base = fs::temp_directory_path();
    TempDirectory tmp(base, "test-file");
    auto file_path = create_temp_file(tmp, "hello.txt", "hello world");
    ASSERT_TRUE(fs::is_regular_file(file_path));
    ASSERT_EQ(read_file(file_path), std::string("hello world"));
}

TEST(runner, "create_temp_file returns path inside temp directory") {
    auto base = fs::temp_directory_path();
    TempDirectory tmp(base, "test-file-path");
    auto file_path = create_temp_file(tmp, "test.dat", "data");
    ASSERT_EQ(file_path.parent_path(), tmp.path());
}

TEST(runner, "create_temp_file works with multiple files") {
    auto base = fs::temp_directory_path();
    TempDirectory tmp(base, "test-multi");
    auto f1 = create_temp_file(tmp, "a.txt", "alpha");
    auto f2 = create_temp_file(tmp, "b.txt", "beta");
    ASSERT_TRUE(fs::is_regular_file(f1));
    ASSERT_TRUE(fs::is_regular_file(f2));
    ASSERT_EQ(read_file(f1), std::string("alpha"));
    ASSERT_EQ(read_file(f2), std::string("beta"));
}

TESTKIT_MAIN(runner)
