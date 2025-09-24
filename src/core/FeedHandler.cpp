#include "core/FeedHandler.hpp"
#include <iostream>
#include <iomanip>

void FeedHandler::print_stats() const {
    std::cout << "---- Feed Stats ----\n";
    std::cout << "Total messages: " << stats_.total_msgs << "\n";
    std::cout << "Elapsed seconds: " << stats_.elapsed_seconds() << "\n";
    std::cout << "Messages/sec: " << std::fixed << std::setprecision(2)
              << (stats_.total_msgs / stats_.elapsed_seconds()) << "\n";
    std::cout << "Message type breakdown:\n";
    for (const auto& [type, count] : stats_.msg_counts) {
        std::cout << "  Type '" << type << "': " << count << "\n";
    }
    std::cout << "--------------------\n";
}
void FeedHandler::run() {
    stats_.start_time = std::chrono::steady_clock::now();
    size_t msg_count = 0;

    while (parser_.has_next()) {
        char msgType = parser_.next_message_type();
        stats_.msg_counts[msgType]++;
        stats_.total_msgs++;

        const char* msg = parser_.next_message();
        const uint8_t msgLen = parser_.next_message_len();

        // Dispatch the message
        // std::cout << "Dispatching message of type: " << msg << "\n";
        dispatcher_.dispatch(msg);

        // Advance cursor by message length
        parser_.advance(msgLen + 2); // +2 for type and length bytes

        // ++msg_count;
        // if (msg_count % 10000 == 0) {
        //     dispatcher_.orderBookManager().log_all_books();
        //     print_stats();
        //
        // }
    }
    print_stats();
    dispatcher_.orderBookManager().log_all_books();

}
