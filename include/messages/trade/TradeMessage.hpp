#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"
#pragma pack(push, 1)

namespace itch {

    struct TradeMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t order_ref;
        char side;           // 'B' or 'S'
        uint32_t shares;
        char stock[9];       // 8-char symbol + null
        uint64_t price;
        uint64_t match_id;

        std::string toString() const {
            std::ostringstream oss;
            oss << "TradeMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", order_ref=" << order_ref
                << ", side=" << side
                << ", shares=" << shares
                << ", stock=" << stock
                << ", price=" << price
                << ", match_id=" << match_id
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline TradeMessage parse_trade(const char* p) {
        using namespace itch::endian;
        TradeMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.order_ref       = read_u64(p + 11);
        msg.side            = p[19];
        msg.shares          = read_u32(p + 20);
        memcpy(msg.stock, p + 24, 8);
        msg.stock[8] = '\0';
        msg.price           = read_u64(p + 32);
        msg.match_id        = read_u64(p + 40);
        return msg;
    }

    static_assert(sizeof(TradeMessage) == 50, "TradeMessage size mismatch");

} // namespace itch

#pragma pack(pop)
