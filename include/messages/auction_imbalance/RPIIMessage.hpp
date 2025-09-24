#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <cstring>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct RPIIMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        char stock[9]; // 8 + null
        char interest_flag;   // B, S, A, N

        std::string toString() const {
            std::ostringstream oss;
            oss << "RPIIMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", stock=" << stock
                << ", interest_flag=" << interest_flag
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline RPIIMessage parse_rpii(const char* p) {
        using namespace itch::endian;
        RPIIMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        std::memcpy(msg.stock, p + 11, 8);
        msg.stock[8] = '\0';
        msg.interest_flag   = p[19];
        return msg;
    }

    static_assert(sizeof(RPIIMessage) == 22, "RPIIMessage size mismatch");

} // namespace itch

#pragma pack(pop)
