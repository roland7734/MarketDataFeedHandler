#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct StockTradingActionMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        char stock[9];        // 8-char symbol + null
        char trading_state;
        char reserved;
        char reason[4];       // 4-char reason code

        std::string toString() const {
            std::ostringstream oss;
            oss << "StockTradingActionMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", stock=" << stock
                << ", trading_state=" << trading_state
                << ", reserved=" << reserved
                << ", reason=" << reason[0] << reason[1] << reason[2] << reason[3]
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline StockTradingActionMessage parse_stock_trading_action(const char* p) {
        using namespace itch::endian;
        StockTradingActionMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        memcpy(msg.stock, p + 11, 8);
        msg.stock[8] = '\0';
        msg.trading_state   = p[19];
        msg.reserved        = p[20];
        memcpy(msg.reason, p + 21, 4);
        return msg;
    }

    static_assert(sizeof(StockTradingActionMessage) == 27, "StockTradingActionMessage size mismatch");

} // namespace itch

#pragma pack(pop)
