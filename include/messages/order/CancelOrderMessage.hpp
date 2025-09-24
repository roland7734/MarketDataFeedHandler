#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

 namespace itch {

    struct CancelOrderMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t order_ref;
        uint32_t quantity; // Cancelled shares

        std::string toString() const {
            std::ostringstream oss;
            oss << "CancelOrderMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", order_ref=" << order_ref
                << ", quantity=" << quantity
                << "]";
            return oss.str();
        }
        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline CancelOrderMessage parse_cancel_order(const char* p) {
        using namespace itch::endian;
        CancelOrderMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.order_ref       = read_u64(p + 11);
        msg.quantity        = read_u32(p + 19);
        return msg;
    }

    static_assert(sizeof(CancelOrderMessage) == 24, "CancelOrderMessage size mismatch");

} // namespace itch

#pragma pack(pop)
