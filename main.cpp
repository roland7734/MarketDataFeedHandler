#include "core/FeedHandler.hpp"
#include "core/Dispatcher.hpp"
#include "book/OrderBookManager.hpp"
#include <iostream>
#include <filesystem>

#include "logger/Logger.hpp"

int main() {
    try {
        // Hardcoded ITCH 5.0 file
        Logger::getInstance().init("engine2.log");
        std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";
        // std::string itchFile = (std::filesystem::current_path() / "..\\data\\01302019.NASDAQ_ITCH50\\01302019.NASDAQ_ITCH50").string();
        std::string itchFile = (std::filesystem::current_path() / "..\\data\\01302020.NASDAQ_ITCH50").string();

        // Create the OrderBookManager
        OrderBookManager obManager;

        // Create the Dispatcher
        Dispatcher dispatcher(obManager);

        // Create the FeedHandler
        FeedHandler feedHandler(itchFile, dispatcher);

        // Run the feed
        feedHandler.run();

        std::cout << "Feed processing completed.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
