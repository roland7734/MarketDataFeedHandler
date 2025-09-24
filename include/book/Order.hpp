#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <sstream>

struct Execution {
    uint32_t quantity;
    uint32_t price;      // Execution price
    bool printable;
    uint64_t match_id;

    std::string toString() const {
        std::ostringstream oss;
        oss << "[quantity=" << quantity
            << ", price=" << price
            << ", printable=" << printable
            << ", match_id=" << match_id << "]";
        return oss.str();
    }
};

class Order {
    public:
    uint64_t order_ref;
    std::string symbol;
    char side;
    uint32_t quantity;
    uint32_t price;  // Display price
    std::string mpid; // Optional, for MPID-attributed orders
    std::vector<Execution> executions;

    Order(uint64_t ref, const std::string& sym, char s, uint32_t qty, uint32_t p, const std::string& m = "")
        : order_ref(ref), symbol(sym), side(s), quantity(qty), price(p), mpid(m) {}

    void execute(uint32_t qty) {
        if (qty > quantity) qty = quantity;
        quantity -= qty;
    }

    void execute_with_price(uint32_t qty, uint32_t execPrice, bool printable, uint64_t match_id) {
        if (qty > quantity) qty = quantity;
        quantity -= qty;
        executions.push_back({qty, execPrice, printable, match_id});
    }

    void cancel(uint32_t qty) {
        if (qty > quantity) qty = quantity;
        quantity -= qty;
    }

    void replace(uint32_t newQuantity, uint32_t newPrice, uint64_t newOrderRef) {
        order_ref = newOrderRef;
        quantity = newQuantity;
        price = newPrice;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "Order [ref=" << order_ref
            << ", symbol=" << symbol
            << ", side=" << side
            << ", qty=" << quantity
            << ", price=" << price
            << ", mpid=" << mpid
            << ", executions=";
        for (auto& e : executions) oss << e.toString() << " ";
        oss << "]";
        return oss.str();
    }
};
