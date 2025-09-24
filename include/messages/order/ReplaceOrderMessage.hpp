#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct ReplaceOrderMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t original_order_ref;
        uint64_t new_order_ref;
        uint32_t shares;
        uint32_t price;

        std::string toString() const {
            std::ostringstream oss;
            oss << "ReplaceOrderMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", original_order_ref=" << original_order_ref
                << ", new_order_ref=" << new_order_ref
                << ", shares=" << shares
                << ", price=" << price
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline ReplaceOrderMessage parse_replace_order(const char* p) {
        using namespace itch::endian;
        ReplaceOrderMessage msg{};
        msg.stock_locate       = read_u16(p + 1);
        msg.tracking_number    = read_u16(p + 3);
        msg.timestamp          = read_u48(p + 5);
        msg.original_order_ref = read_u64(p + 11);
        msg.new_order_ref      = read_u64(p + 19);
        msg.shares             = read_u32(p + 27);
        msg.price              = read_u32(p + 31);
        return msg;
    }

    static_assert(sizeof(ReplaceOrderMessage) == 36, "ReplaceOrderMessage size mismatch");

} // namespace itch

#pragma pack(pop)
