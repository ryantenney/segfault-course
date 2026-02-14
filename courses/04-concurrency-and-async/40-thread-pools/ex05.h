// Exercise 05: Graceful Shutdown
//
// PROBLEM:
//   Implement ShutdownPool with an explicit shutdown() method. After
//   shutdown, no new tasks are accepted (submit throws). Workers finish
//   current/pending tasks and exit.
//
// TODO:
//   1. Implement the worker loop.
//   2. Implement submit().
//   3. Implement shutdown().
//   4. Implement the gate() helper.
//
// WHY:
//   Thread pools need controlled shutdown to avoid data races and resource
//   leaks. A graceful shutdown signals workers to stop, lets in-flight
//   tasks complete, then joins all threads.

#pragma once
#include <testkit/testkit.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <stdexcept>

class ShutdownPool {
    std::vector<std::jthread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool stopped_ = false;

public:
    explicit ShutdownPool(std::size_t n) {
        gate();
        for (std::size_t i = 0; i < n; ++i) {
            workers_.emplace_back([this](std::stop_token) {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock lock(mutex_);
                        cv_.wait(lock, [this] {
                            return stopped_ || !tasks_.empty();
                        });
                        if (stopped_ && tasks_.empty()) return;
                        if (tasks_.empty()) continue;
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ShutdownPool() {
        shutdown();
    }

    // Submits a callable. Throws std::runtime_error if pool is shut down.
    template <typename F>
    auto submit(F&& f) -> std::future<decltype(f())> {
        using ReturnType = decltype(f());
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::forward<F>(f));
        auto future = task->get_future();
        {
            std::lock_guard lock(mutex_);
            if (stopped_) {
                throw std::runtime_error("pool is shut down");
            }
            tasks_.push([task]() { (*task)(); });
        }
        cv_.notify_one();
        return future;
    }

    // Signals workers to finish pending tasks and stop.
    void shutdown() {
        {
            std::lock_guard lock(mutex_);
            if (stopped_) return;
            stopped_ = true;
        }
        cv_.notify_all();
        for (auto& w : workers_) {
            if (w.joinable()) w.join();
        }
    }

    // Returns true if shutdown() has been called.
    bool is_shutdown() const {
        return stopped_;
    }

    void gate() {
        TODO();
    }

    ShutdownPool(const ShutdownPool&) = delete;
    ShutdownPool& operator=(const ShutdownPool&) = delete;
};
