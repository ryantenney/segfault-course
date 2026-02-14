// Exercise 02: Worker Loop
//
// PROBLEM:
//   Implement WorkerPool where threads pull std::function<void()> tasks
//   from a shared queue and execute them. Provide submit() to enqueue.
//
// TODO:
//   1. Implement the worker loop in the constructor lambda.
//   2. Implement submit() to push tasks onto the queue.
//   3. Implement the gate() helper.
//
// WHY:
//   The worker loop is the heart of a thread pool. Each thread waits for
//   tasks on a condition variable, dequeues one, runs it, and loops back.
//   This is the classic producer-consumer pattern.

#pragma once
#include <testkit/testkit.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class WorkerPool {
    std::vector<std::jthread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable_any cv_;

public:
    explicit WorkerPool(std::size_t n) {
        gate();  // gates on TODO()
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

    ~WorkerPool() {
        {
            std::lock_guard lock(mutex_);
            // Queue is cleared on destruction so workers drain and exit.
        }
        cv_.notify_all();
    }

    // Submits a task to the pool.
    void submit(std::function<void()> task) {
        {
            std::lock_guard lock(mutex_);
            tasks_.push(std::move(task));
        }
        cv_.notify_one();
    }

    // Gate function: tests call this first.
    void gate() {
        TODO();
    }

    WorkerPool(const WorkerPool&) = delete;
    WorkerPool& operator=(const WorkerPool&) = delete;
};
