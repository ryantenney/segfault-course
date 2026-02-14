// Exercise 06: Pool Statistics
//
// PROBLEM:
//   Implement StatsPool that tracks:
//     - active_count(): number of tasks currently executing
//     - pending_count(): number of tasks waiting in the queue
//     - completed_count(): number of tasks that have finished
//
// TODO:
//   1. Implement the worker loop with stats tracking.
//   2. Implement submit().
//   3. Implement active_count(), pending_count(), completed_count().
//   4. Implement the gate() helper.
//
// WHY:
//   Production thread pools expose metrics for monitoring and debugging.
//   Tracking active, pending, and completed task counts helps with load
//   balancing, capacity planning, and diagnosing performance issues.

#pragma once
#include <testkit/testkit.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

class StatsPool {
    std::vector<std::jthread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable_any cv_;
    std::atomic<int> active_{0};
    std::atomic<int> completed_{0};

public:
    explicit StatsPool(std::size_t n) {
        gate();
        for (std::size_t i = 0; i < n; ++i) {
            workers_.emplace_back([this](std::stop_token st) {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock lock(mutex_);
                        cv_.wait(lock, st, [this, &st] {
                            return st.stop_requested() || !tasks_.empty();
                        });
                        if (st.stop_requested() && tasks_.empty()) return;
                        if (tasks_.empty()) return;
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    active_.fetch_add(1);
                    task();
                    active_.fetch_sub(1);
                    completed_.fetch_add(1);
                }
            });
        }
    }

    ~StatsPool() {
        cv_.notify_all();
    }

    template <typename F>
    auto submit(F&& f) -> std::future<decltype(f())> {
        using ReturnType = decltype(f());
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::forward<F>(f));
        auto future = task->get_future();
        {
            std::lock_guard lock(mutex_);
            tasks_.push([task]() { (*task)(); });
        }
        cv_.notify_one();
        return future;
    }

    int active_count() const { return active_.load(); }

    int pending_count() const {
        std::lock_guard lock(const_cast<std::mutex&>(mutex_));
        return static_cast<int>(tasks_.size());
    }

    int completed_count() const { return completed_.load(); }

    void gate() {
        TODO();
    }

    StatsPool(const StatsPool&) = delete;
    StatsPool& operator=(const StatsPool&) = delete;
};
