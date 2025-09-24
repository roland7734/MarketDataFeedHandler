#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Order.hpp"

class OrderBook {
public:
    explicit OrderBook(const std::string& symbol);

    void add_order(std::shared_ptr<Order> order);
    void delete_order(uint64_t order_ref);
    void cancel_order(uint64_t order_ref, uint32_t qty);
    void replace_order(uint64_t old_ref, uint64_t new_ref, uint32_t qty, uint32_t price);
    void execute_order(uint64_t order_ref, uint32_t qty);
    void execute_order_with_price(uint64_t order_ref, uint32_t qty, uint32_t execPrice, bool printable, uint64_t match_id);

    const std::string& symbol() const { return symbol_; }
    const std::unordered_map<uint64_t, std::shared_ptr<Order>>& orders() const { return orders_; }
private:
    std::string symbol_;
    std::unordered_map<uint64_t, std::shared_ptr<Order>> orders_;
};
