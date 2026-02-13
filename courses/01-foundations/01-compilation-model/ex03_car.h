// Exercise 03 — Car class (read-only)
#pragma once
#include <string>

class Car {
    std::string name_;
    int speed_;
public:
    Car(std::string name, int speed)
        : name_(std::move(name)), speed_(speed) {}

    const std::string& name() const { return name_; }
    int speed() const { return speed_; }
};
