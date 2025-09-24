#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct DeleteOrderMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t order_ref;

        std::string toString() const {
            std::ostringstream oss;
            oss << "DeleteOrderMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", order_ref=" << order_ref
                << "]";
            return oss.str();
        }
        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline DeleteOrderMessage parse_delete_order(const char* p) {
        using namespace itch::endian;
        DeleteOrderMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.order_ref       = read_u64(p + 11);
        return msg;
    }

    static_assert(sizeof(DeleteOrderMessage) == 20, "DeleteOrderMessage size mismatch");

} // namespace itch

#pragma pack(pop)
