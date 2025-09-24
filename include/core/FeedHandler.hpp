#pragma once
#include <string>
#include "../parser/ITCHParser.hpp"
#include "Dispatcher.hpp"
#include <unordered_map>
#include <chrono>

struct FeedStats {
    std::unordered_map<char, size_t> msg_counts;
    size_t total_msgs = 0;
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    double elapsed_seconds() const {
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time).count();
    }
};

class FeedHandler {
public:
    FeedHandler(const std::string& path, Dispatcher& dispatcher)
        : parser_(path), dispatcher_(dispatcher) {}

    void run();  // Main loop to process the feed

private:
    ITCHParser parser_;
    Dispatcher& dispatcher_;
    FeedStats stats_;
    void print_stats() const;

};
