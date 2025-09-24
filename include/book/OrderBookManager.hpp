#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "OrderBook.hpp"
#include "Order.hpp"

class OrderBookManager {
public:
    std::shared_ptr<OrderBook> get_or_create_book(const std::string& symbol);

    void add_order(std::shared_ptr<Order> order);
    void delete_order(uint64_t order_ref);
    void cancel_order(uint64_t order_ref, uint32_t qty);
    void replace_order(uint64_t old_ref, uint64_t new_ref, uint32_t qty, uint32_t price);
    void execute_order(uint64_t order_ref, uint32_t qty);
    void execute_order_with_price(uint64_t order_ref, uint32_t qty, uint32_t execPrice, bool printable, uint64_t match_id);

    void log_all_books() const;

private:
    std::unordered_map<std::string, std::shared_ptr<OrderBook>> books_;
    std::unordered_map<uint64_t, std::string> order_ref_to_symbol_;
};
