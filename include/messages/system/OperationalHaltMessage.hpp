#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <cstring>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct OperationalHaltMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        char stock[9]; // 8 + null
        char market_center; // Q, B, X
        char halt_action;   // H, T

        std::string toString() const {
            std::ostringstream oss;
            oss << "OperationalHaltMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", stock=" << stock
                << ", market_center=" << market_center
                << ", halt_action=" << halt_action
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline OperationalHaltMessage parse_halt(const char* p) {
        using namespace itch::endian;
        OperationalHaltMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        std::memcpy(msg.stock, p + 11, 8);
        msg.stock[8] = '\0';
        msg.market_center   = p[19];
        msg.halt_action     = p[20];
        return msg;
    }

    static_assert(sizeof(OperationalHaltMessage) == 23, "OperationalHaltMessage size mismatch");

} // namespace itch

#pragma pack(pop)
