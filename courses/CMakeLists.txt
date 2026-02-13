# ---------------------------------------------------------------------------
# add_exercise(TARGET TEST_SRC [extra_srcs...])
#
# Creates a test executable for a single exercise.
#   - TARGET:    Name like "01-01-ex01" (course-lesson-exercise)
#   - TEST_SRC:  The main test .cpp file
#   - extra_srcs: Additional .cpp files to compile into the target
#
# The executable is linked against testkit and registered with CTest.
# ---------------------------------------------------------------------------

function(add_exercise TARGET TEST_SRC)
    add_executable(${TARGET} ${TEST_SRC} ${ARGN})
    target_link_libraries(${TARGET} PRIVATE testkit)

    # Let exercises #include their own files with plain names (e.g. "ex01.h").
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    add_test(NAME ${TARGET} COMMAND ${TARGET})
endfunction()

# ---------------------------------------------------------------------------
# Courses
# ---------------------------------------------------------------------------

add_subdirectory(01-foundations)
