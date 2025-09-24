#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct AddOrderMPIDMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t order_ref;
        char side;          // 'B' or 'S'
        uint32_t shares;
        char stock[9];      // 8 chars + null-terminator
        uint32_t price;
        char mpid[5];       // 4 chars + null-terminator

        std::string toString() const {
            std::ostringstream oss;
            oss << "AddOrderMPIDMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", order_ref=" << order_ref
                << ", side=" << side
                << ", shares=" << shares
                << ", stock=" << stock
                << ", price=" << price
                << ", mpid=" << mpid
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    // Decode function from raw ITCH buffer
    inline AddOrderMPIDMessage parse_add_order_mpid(const char* p) {
        using namespace itch::endian;
        AddOrderMPIDMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.order_ref       = read_u64(p + 11);
        msg.side            = p[19];
        msg.shares          = read_u32(p + 20);
        memcpy(msg.stock, p + 24, 8);
        msg.stock[8] = '\0';
        msg.price = read_u32(p + 32);
        memcpy(msg.mpid, p + 36, 4);
        msg.mpid[4] = '\0';
        return msg;
    }

    static_assert(sizeof(AddOrderMPIDMessage) == 43, "AddOrderMPIDMessage size mismatch");

} // namespace itch

#pragma pack(pop)
