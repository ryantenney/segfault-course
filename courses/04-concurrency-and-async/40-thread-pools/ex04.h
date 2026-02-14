// Exercise 04: Submit Different Types
//
// PROBLEM:
//   Implement TypedPool that supports submitting tasks returning different
//   types: int, std::string, and void.
//
// TODO:
//   1. Implement the worker loop.
//   2. Implement the template submit() method.
//   3. Implement the gate() helper.
//
// WHY:
//   A real thread pool must handle callables with any return type.
//   Template submit() with decltype deduction and std::packaged_task
//   makes this generic.

#pragma once
#include <testkit/testkit.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <string>

class TypedPool {
    std::vector<std::jthread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable_any cv_;

public:
    explicit TypedPool(std::size_t n) {
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

    ~TypedPool() {
        cv_.notify_all();
    }

    // Submits a callable and returns a future for its result.
    // Works with any return type including void.
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

    TypedPool(const TypedPool&) = delete;
    TypedPool& operator=(const TypedPool&) = delete;
};
