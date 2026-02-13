// Exercise 06: Extern Variables
//
// PROBLEM:
//   The variables below are DEFINED in this header (they have initial
//   values and allocate storage).  Right now only one .cpp file includes
//   this header, so there's no conflict.  But if a second .cpp file
//   includes it, the linker sees two definitions → error.
//
// TODO:
//   1. Change each variable below to an `extern` DECLARATION (remove the
//      initializer):
//        extern int max_connections;
//        extern double pi;
//        extern const char* app_name;
//
//   2. In ex06.cpp, include this header and provide the DEFINITIONS
//      with correct values:
//        int max_connections = 100;
//        double pi = 3.14159265358979;
//        const char* app_name = "SegfaultCourse";
//
//   3. Implement init_config() in ex06.cpp (see instructions there).
//
// WHY:
//   `extern` tells the compiler: "this variable exists, but it's defined
//   elsewhere."  You can put extern declarations in a header safely —
//   every TU that includes it learns about the variable without creating
//   a duplicate.  The actual definition (with the initial value) lives in
//   exactly one .cpp file.

#pragma once

int max_connections = 0;
double pi = 0.0;
const char* app_name = nullptr;
