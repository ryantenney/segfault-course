// Exercise 03: Submit with Future
//
// PROBLEM:
//   Implement FuturePool with a submit() method that accepts a callable
//   and returns a std::future<T> for its result.
//
// TODO:
//   1. Implement the worker loop.
//   2. Implement submit() using std::packaged_task.
//   3. Implement the gate() helper.
//
// WHY:
//   Fire-and-forget submit (void return) is limiting. Real pools let
//   callers retrieve results via futures. std::packaged_task wraps a
//   callable and provides an associated future — perfect for this.

#pragma once
#include <testkit/testkit.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class FuturePool {
    std::vector<std::jthread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable_any cv_;

public:
    explicit FuturePool(std::size_t n) {
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
                    task();
                }
            });
        }
    }

    ~FuturePool() {
        cv_.notify_all();
    }

    // Submits a callable and returns a future for its result.
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

    void gate() {
        TODO();
    }

    FuturePool(const FuturePool&) = delete;
    FuturePool& operator=(const FuturePool&) = delete;
};
