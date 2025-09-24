#pragma once
#include <string>
#include "../book/OrderBookManager.hpp"

class Dispatcher {
public:
    explicit Dispatcher(OrderBookManager& obm) : orderBookManager_(obm) {}

    void dispatch(const char* msg);

    std::size_t message_length(char msgType) const;
    OrderBookManager& orderBookManager() { return orderBookManager_; }


private:
    OrderBookManager& orderBookManager_;
};
