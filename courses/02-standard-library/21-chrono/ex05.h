// Exercise 05: Periodic Timer Logic
//
// Many systems need to fire an action at regular intervals. The pattern is:
//
//   auto next_fire = start;
//   while (running) {
//       if (now >= next_fire) {
//           do_action();
//           next_fire += interval;
//       }
//   }
//
// Note: adding the interval to next_fire (rather than to "now") avoids
// drift — each tick is anchored to the original start time.
//
// In this exercise, rather than actually looping with real time, you'll
// implement the logic that determines when actions should fire given a
// set of simulated time points.
//
// TODO:
//   1. Implement compute_fire_times() — given a start time, an interval,
//      and a list of "now" time points (in order), return which of those
//      time points trigger a fire. A fire occurs when "now >= next_fire",
//      then next_fire advances by interval.
//   2. Implement count_intervals() — given a start and end time plus an
//      interval, return how many complete intervals fit between them.
//   3. Implement next_fire_time() — given the last fire time and the
//      interval, return when the next fire should occur.

#pragma once

#include <testkit/testkit.h>
#include <chrono>
#include <vector>

using SteadyTimePoint = std::chrono::steady_clock::time_point;

// Given a start time and an interval, examine each time point in `timestamps`
// (in chronological order). Each time a timestamp is at or past the next fire
// time, include it in the result and advance the next fire time by `interval`.
// Multiple fires can occur at one timestamp if enough time has passed.
// However, only include each timestamp once in the result, even if it triggers
// multiple interval advances.
inline std::vector<SteadyTimePoint> compute_fire_times(
    SteadyTimePoint start,
    std::chrono::milliseconds interval,
    const std::vector<SteadyTimePoint>& timestamps)
{
    TODO();
}

// Return how many complete intervals fit between start and end.
// If end <= start, return 0.
inline int count_intervals(
    SteadyTimePoint start,
    SteadyTimePoint end,
    std::chrono::milliseconds interval)
{
    TODO();
}

// Return the next fire time: last_fire + interval.
inline SteadyTimePoint next_fire_time(
    SteadyTimePoint last_fire,
    std::chrono::milliseconds interval)
{
    TODO();
}
