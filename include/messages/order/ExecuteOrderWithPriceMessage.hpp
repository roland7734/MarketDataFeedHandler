#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct ExecuteOrderWithPriceMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t order_ref;
        uint32_t quantity;   // Executed shares
        uint64_t match_id;
        char printable;      // 'Y' or 'N'
        uint32_t price;      // Execution price

        std::string toString() const {
            std::ostringstream oss;
            oss << "ExecuteOrderWithPriceMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", order_ref=" << order_ref
                << ", quantity=" << quantity
                << ", match_id=" << match_id
                << ", printable=" << printable
                << ", price=" << price
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline ExecuteOrderWithPriceMessage parse_execute_with_price(const char* p) {
        using namespace itch::endian;
        ExecuteOrderWithPriceMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.order_ref       = read_u64(p + 11);
        msg.quantity        = read_u32(p + 19);
        msg.match_id        = read_u64(p + 23);
        msg.printable       = p[31];
        msg.price           = read_u32(p + 32);
        return msg;
    }

    static_assert(sizeof(ExecuteOrderWithPriceMessage) == 37, "ExecuteOrderWithPriceMessage size mismatch");

} // namespace itch

#pragma pack(pop)
