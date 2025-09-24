#pragma once
#include <cstdint>
#include <cstring>
#include "../../parser/Endian.hpp"
#pragma pack(push, 1)

namespace itch {

    struct CrossTradeMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t order_ref;
        char side;           // 'B' or 'S'
        uint32_t shares;
        char stock[9];       // 8-char symbol + null
        uint32_t cross_price;
        uint64_t match_id;
        char cross_type;     // e.g., 'O', 'C', 'E'

        std::string toString() const {
                    std::ostringstream oss;
                    oss << "CrossTradeMessage ["
                        << "stock_locate=" << stock_locate
                        << ", tracking_number=" << tracking_number
                        << ", timestamp=" << timestamp
                        << ", order_ref=" << order_ref
                        << ", side=" << side
                        << ", shares=" << shares
                        << ", stock=" << stock
                        << ", cross_price=" << cross_price
                        << ", match_id=" << match_id
                        << ", cross_type=" << cross_type
                        << "]";
                    return oss.str();
                }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline CrossTradeMessage parse_cross_trade(const char* p) {
        using namespace itch::endian;
        CrossTradeMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.order_ref       = read_u64(p + 11);
        msg.side            = p[19];
        msg.shares          = read_u32(p + 20);
        memcpy(msg.stock, p + 24, 8);
        msg.stock[8] = '\0';
        msg.cross_price     = read_u32(p + 32);
        msg.match_id        = read_u64(p + 36);
        msg.cross_type      = p[44];
        return msg;
    }

    static_assert(sizeof(CrossTradeMessage) == 47, "CrossTradeMessage size mismatch");

} // namespace itch

#pragma pack(pop)


