#include "book/OrderBook.hpp"

OrderBook::OrderBook(const std::string& symbol)
    : symbol_(symbol) {}

void OrderBook::add_order(std::shared_ptr<Order> order) {
    orders_[order->order_ref] = order;
}

void OrderBook::delete_order(uint64_t order_ref) {
    orders_.erase(order_ref);
}

void OrderBook::cancel_order(uint64_t order_ref, uint32_t qty) {
    auto it = orders_.find(order_ref);
    if (it != orders_.end()) {
        auto& order = it->second;
        if (order->quantity > qty) {
            order->quantity -= qty;
        } else {
            orders_.erase(it);
        }
    }
}

void OrderBook::replace_order(uint64_t old_ref, uint64_t new_ref, uint32_t qty, uint32_t price) {
    auto it = orders_.find(old_ref);
    if (it != orders_.end()) {
        auto old_order = it->second;
        auto new_order = std::make_shared<Order>(
            new_ref,
            old_order->symbol,
            old_order->side,
            qty,
            price
        );
        orders_.erase(it);
        orders_[new_ref] = new_order;
    }
}

void OrderBook::execute_order(uint64_t order_ref, uint32_t qty) {
    auto it = orders_.find(order_ref);
    if (it != orders_.end()) {
        auto& order = it->second;
        if (order->quantity > qty) {
            order->quantity -= qty;
        } else {
            orders_.erase(it);
        }
    }
}

void OrderBook::execute_order_with_price(uint64_t order_ref, uint32_t qty, uint32_t execPrice, bool /*printable*/, uint64_t /*match_id*/) {
    auto it = orders_.find(order_ref);
    if (it != orders_.end()) {
        auto& order = it->second;
        // Optionally update price or log execution details
        if (order->quantity > qty) {
            order->quantity -= qty;
        } else {
            orders_.erase(it);
        }
    }
}
