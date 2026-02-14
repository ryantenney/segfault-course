cmake_minimum_required(VERSION 3.20)
project(segfault-course LANGUAGES CXX)

# ---------------------------------------------------------------------------
# C++ standard and compiler flags
# ---------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings — strict but practical.
# -Wno-unused-parameter: TODO() stubs don't reference their args.
# -Wno-unused-private-field: RAII stubs have members used only in destructors
#   that students haven't implemented yet.
# -Wno-self-move: intentional self-move tests in move-semantics exercises.
# All three go away once students implement the function bodies.
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Werror=return-type
    -Wno-unused-parameter
    -Wno-unused-private-field
    -Wno-self-move
)

# ---------------------------------------------------------------------------
# CTest — enables `ctest` and the `./run` convenience script.
# ---------------------------------------------------------------------------

enable_testing()

# ---------------------------------------------------------------------------
# Subdirectories
# ---------------------------------------------------------------------------

add_subdirectory(testkit)
add_subdirectory(courses)
