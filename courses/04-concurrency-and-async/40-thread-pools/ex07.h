// Exercise 07: Pool Resize
//
// PROBLEM:
//   Implement ResizablePool with a resize(n) method that can grow or
//   shrink the number of worker threads at runtime.
//
// TODO:
//   1. Implement the worker loop.
//   2. Implement submit().
//   3. Implement resize() to add or remove workers.
//   4. Implement the gate() helper.
//
// WHY:
//   Fixed-size pools can be wasteful (too many threads for light load)
//   or insufficient (too few for burst load). Resizing lets you adapt
//   the pool to changing demand — an important feature in production
//   systems that handle variable traffic.

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

class ResizablePool {
    struct Worker {
        std::jthread thread;
    };

    std::vector<Worker> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable_any cv_;
    std::mutex resize_mutex_;

    void start_worker() {
        workers_.push_back({std::jthread([this](std::stop_token st) {
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
        })});
    }

public:
    explicit ResizablePool(std::size_t n) {
        gate();
        for (std::size_t i = 0; i < n; ++i) {
            start_worker();
        }
    }

    ~ResizablePool() {
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

    // Resizes the pool to `n` threads.
    // If growing, adds new workers. If shrinking, requests stop on
    // excess workers and joins them.
    void resize(std::size_t n) {
        std::lock_guard rlock(resize_mutex_);
        if (n > workers_.size()) {
            std::size_t to_add = n - workers_.size();
            for (std::size_t i = 0; i < to_add; ++i) {
                start_worker();
            }
        } else if (n < workers_.size()) {
            // Request stop on excess workers from the back.
            while (workers_.size() > n) {
                workers_.back().thread.request_stop();
                cv_.notify_all();
                workers_.pop_back();  // jthread joins on destruction
            }
        }
    }

    std::size_t size() const {
        return workers_.size();
    }

    void gate() {
        TODO();
    }

    ResizablePool(const ResizablePool&) = delete;
    ResizablePool& operator=(const ResizablePool&) = delete;
};
