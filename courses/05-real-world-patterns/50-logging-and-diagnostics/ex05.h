// Exercise 05: Log Sink Abstraction
//
// A "sink" is the destination for log messages: console, file, memory,
// network, etc. By defining a Sink interface, the logger becomes
// decoupled from where the output goes. This exercise defines the
// interface and two concrete implementations.
//
// TODO:
//   1. Implement ConsoleSink::write() -- print the message to std::cout
//      followed by a newline.
//   2. Implement MemorySink::write() -- append the message to the
//      internal entries_ vector.
//   3. Implement MemorySink::entries() -- return the vector of messages.
//   4. Implement SinkLogger::log() -- if level >= min_level_, call
//      write() on the sink with the formatted message "[LEVEL] msg".

#pragma once

#include <testkit/testkit.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum class SinkLogLevel {
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3
};

inline std::string sink_level_str(SinkLogLevel l) {
    switch (l) {
        case SinkLogLevel::Debug: return "DEBUG";
        case SinkLogLevel::Info:  return "INFO";
        case SinkLogLevel::Warn:  return "WARN";
        case SinkLogLevel::Error: return "ERROR";
    }
    return "UNKNOWN";
}

// Abstract sink interface.
class Sink {
public:
    virtual ~Sink() = default;
    virtual void write(const std::string& message) = 0;
};

// Prints each message to stdout.
class ConsoleSink : public Sink {
public:
    void write(const std::string& message) override {
        TODO();
    }
};

// Stores messages in memory for testing.
class MemorySink : public Sink {
    std::vector<std::string> entries_;

public:
    void write(const std::string& message) override {
        TODO();
    }

    const std::vector<std::string>& entries() const {
        TODO();
    }
};

// Logger that writes formatted messages to a sink.
class SinkLogger {
    std::shared_ptr<Sink> sink_;
    SinkLogLevel min_level_;

public:
    SinkLogger(std::shared_ptr<Sink> sink, SinkLogLevel min_level = SinkLogLevel::Debug)
        : sink_(std::move(sink)), min_level_(min_level) {}

    void log(SinkLogLevel level, const std::string& message) {
        TODO();
    }
};
