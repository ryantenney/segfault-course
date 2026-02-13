# testkit — header-only test framework
#
# Usage: target_link_libraries(my_test PRIVATE testkit)
# This gives the target access to <testkit/testkit.h>.

add_library(testkit INTERFACE)
target_include_directories(testkit INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
