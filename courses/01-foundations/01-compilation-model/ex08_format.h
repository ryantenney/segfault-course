// Exercise 08: Multi-TU Build — Format header
//
// This header declares formatting functions.  The implementations
// live in ex08_format.cpp.
//
// Note how this header #includes ex08_math.h because the format
// functions use math helpers internally.  The include guards
// (#pragma once) on both headers prevent double-inclusion.
//
// TODO: Implement the functions in ex08_format.cpp.

#pragma once

#include "ex08_math.h"

#include <string>

// Formats an integer as a string with a sign prefix: "+5" or "-3".
std::string format_signed(int value);

// Formats a range as "lo..hi" after clamping both ends to [min, max].
std::string format_range(int a, int b, int min, int max);
