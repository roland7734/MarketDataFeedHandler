#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct ExecuteOrderMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t order_ref;
        uint32_t quantity;   // Executed shares
        uint64_t match_id;

        std::string toString() const {
            std::ostringstream oss;
            oss << "ExecuteOrderMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", order_ref=" << order_ref
                << ", quantity=" << quantity
                << ", match_id=" << match_id
                << "]";
            return oss.str();
        }
        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline ExecuteOrderMessage parse_execute_order(const char* p) {
        using namespace itch::endian;
        ExecuteOrderMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.order_ref       = read_u64(p + 11);
        msg.quantity        = read_u32(p + 19);
        msg.match_id        = read_u64(p + 23);
        return msg;
    }

    static_assert(sizeof(ExecuteOrderMessage) == 32, "ExecuteOrderMessage size mismatch");

} // namespace itch

#pragma pack(pop)
