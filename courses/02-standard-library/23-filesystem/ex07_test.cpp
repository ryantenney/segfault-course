// Exercise 07 -- Tests (read-only)

#include <fstream>
#include <sstream>
#include <testkit/testkit.h>

#include "ex07.h"

namespace {

struct TempDir {
    fs::path path;

    TempDir() {
        path = fs::temp_directory_path() / "segfault-02-23-ex07";
        fs::remove_all(path);
        fs::create_directories(path);
    }

    ~TempDir() {
        std::error_code ec;
        fs::remove_all(path, ec);
    }
};

std::string read_file(const fs::path& p) {
    std::ifstream ifs(p);
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

} // namespace

static testkit::TestRunner runner("02-23-ex07: Create Directory Tree");

TEST(runner, "create_tree creates single directory") {
    TempDir tmp;
    ASSERT_TRUE(create_tree(tmp.path, {"subdir"}));
    ASSERT_TRUE(fs::is_directory(tmp.path / "subdir"));
}

TEST(runner, "create_tree creates multiple directories") {
    TempDir tmp;
    ASSERT_TRUE(create_tree(tmp.path, {"src", "include", "tests"}));
    ASSERT_TRUE(fs::is_directory(tmp.path / "src"));
    ASSERT_TRUE(fs::is_directory(tmp.path / "include"));
    ASSERT_TRUE(fs::is_directory(tmp.path / "tests"));
}

TEST(runner, "create_tree creates nested directories") {
    TempDir tmp;
    ASSERT_TRUE(create_tree(tmp.path, {"a/b/c"}));
    ASSERT_TRUE(fs::is_directory(tmp.path / "a" / "b" / "c"));
}

TEST(runner, "create_tree handles already existing directories") {
    TempDir tmp;
    fs::create_directory(tmp.path / "existing");
    ASSERT_TRUE(create_tree(tmp.path, {"existing", "new"}));
    ASSERT_TRUE(fs::is_directory(tmp.path / "existing"));
    ASSERT_TRUE(fs::is_directory(tmp.path / "new"));
}

TEST(runner, "ensure_parent_exists creates parent directory") {
    TempDir tmp;
    auto filepath = tmp.path / "newdir" / "file.txt";
    ASSERT_TRUE(ensure_parent_exists(filepath));
    ASSERT_TRUE(fs::is_directory(tmp.path / "newdir"));
}

TEST(runner, "ensure_parent_exists handles existing parent") {
    TempDir tmp;
    auto filepath = tmp.path / "file.txt";
    ASSERT_TRUE(ensure_parent_exists(filepath));
}

TEST(runner, "ensure_parent_exists creates deep hierarchy") {
    TempDir tmp;
    auto filepath = tmp.path / "a" / "b" / "c" / "file.txt";
    ASSERT_TRUE(ensure_parent_exists(filepath));
    ASSERT_TRUE(fs::is_directory(tmp.path / "a" / "b" / "c"));
}

TEST(runner, "create_file_in_dir creates directory and file") {
    TempDir tmp;
    auto dir = tmp.path / "output";
    ASSERT_TRUE(create_file_in_dir(dir, "result.txt", "success"));
    ASSERT_TRUE(fs::is_directory(dir));
    ASSERT_TRUE(fs::is_regular_file(dir / "result.txt"));
    ASSERT_EQ(read_file(dir / "result.txt"), std::string("success"));
}

TEST(runner, "create_file_in_dir handles existing directory") {
    TempDir tmp;
    ASSERT_TRUE(create_file_in_dir(tmp.path, "data.txt", "content"));
    ASSERT_TRUE(fs::is_regular_file(tmp.path / "data.txt"));
    ASSERT_EQ(read_file(tmp.path / "data.txt"), std::string("content"));
}

TESTKIT_MAIN(runner)
