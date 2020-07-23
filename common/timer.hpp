#pragma once
#include <chrono>
#include <stdexcept>
#include <atomic>

class Timer;

class Timer {
protected:
    inline static std::chrono::high_resolution_clock::time_point t_start;
    inline static std::atomic<bool> running{false};
public: 
    static void start() {
        if (running.exchange(true) == true) {
            throw std::runtime_error("Timer class is not intended for multi-threaded use or another start was called before a stop");
        }
        t_start = std::chrono::high_resolution_clock::now();
    }

    static std::chrono::nanoseconds stop() {
        auto t_stop = std::chrono::high_resolution_clock::now();
        auto ret = t_stop - t_start;
        running.store(false);
        return ret;
    }
};

