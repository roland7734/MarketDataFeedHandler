#include "book/OrderBookManager.hpp"

#include "logger/Logger.hpp"

std::shared_ptr<OrderBook> OrderBookManager::get_or_create_book(const std::string& symbol) {
    auto it = books_.find(symbol);
    if (it != books_.end()) return it->second;

    auto book = std::make_shared<OrderBook>(symbol);
    books_[symbol] = book;
    return book;
}

void OrderBookManager::add_order(std::shared_ptr<Order> order) {
    auto book = get_or_create_book(order->symbol);
    book->add_order(order);
    order_ref_to_symbol_[order->order_ref] = order->symbol;
}

void OrderBookManager::delete_order(uint64_t order_ref) {
    auto it = order_ref_to_symbol_.find(order_ref);
    if (it == order_ref_to_symbol_.end()) return;
    auto book_it = books_.find(it->second);
    if (book_it != books_.end()) book_it->second->delete_order(order_ref);
    order_ref_to_symbol_.erase(it);
}

void OrderBookManager::cancel_order(uint64_t order_ref, uint32_t qty) {
    auto it = order_ref_to_symbol_.find(order_ref);
    if (it == order_ref_to_symbol_.end()) return;
    auto book_it = books_.find(it->second);
    if (book_it != books_.end()) book_it->second->cancel_order(order_ref, qty);
}

void OrderBookManager::replace_order(uint64_t old_ref, uint64_t new_ref, uint32_t qty, uint32_t price) {
    auto it = order_ref_to_symbol_.find(old_ref);
    if (it == order_ref_to_symbol_.end()) return;
    auto book_it = books_.find(it->second);
    if (book_it != books_.end()) book_it->second->replace_order(old_ref, new_ref, qty, price);
    // Update mapping: remove old, add new
    order_ref_to_symbol_.erase(old_ref);
    order_ref_to_symbol_[new_ref] = it->second;
}

void OrderBookManager::execute_order(uint64_t order_ref, uint32_t qty) {
    auto it = order_ref_to_symbol_.find(order_ref);
    if (it == order_ref_to_symbol_.end()) return;
    auto book_it = books_.find(it->second);
    if (book_it != books_.end()) book_it->second->execute_order(order_ref, qty);
}

void OrderBookManager::execute_order_with_price(uint64_t order_ref, uint32_t qty, uint32_t execPrice, bool printable, uint64_t match_id) {
    auto it = order_ref_to_symbol_.find(order_ref);
    if (it == order_ref_to_symbol_.end()) return;
    auto book_it = books_.find(it->second);
    if (book_it != books_.end()) book_it->second->execute_order_with_price(order_ref, qty, execPrice, printable, match_id);
}

void OrderBookManager::log_all_books() const {
    for (const auto& [symbol, book] : books_) {
        Logger::getInstance().log("OrderBook for " + symbol + ":");
        for (const auto& [ref, order] : book->orders()) {
            Logger::getInstance().log(order->toString());
        }
    }
}
