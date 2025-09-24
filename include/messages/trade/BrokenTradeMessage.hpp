#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct BrokenTradeMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t match_number;

        std::string toString() const {
            std::ostringstream oss;
            oss << "BrokenTradeMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", match_number=" << match_number
                << "]";
            return oss.str();
        }
        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline BrokenTradeMessage parse_broken_trade(const char* p) {
        using namespace itch::endian;
        BrokenTradeMessage msg{};
        msg.stock_locate   = read_u16(p + 1);
        msg.tracking_number= read_u16(p + 3);
        msg.timestamp      = read_u48(p + 5);
        msg.match_number   = read_u64(p + 11);
        return msg;
    }

    static_assert(sizeof(BrokenTradeMessage) == 20, "BrokenTradeMessage size mismatch");

} // namespace itch

#pragma pack(pop)
