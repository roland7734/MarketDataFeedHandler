#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <cstring>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct RegSHOMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        char stock[9];  // 8 chars + null terminator
        char reg_sho_action; // '0', '1', or '2'

        std::string toString() const {
            std::ostringstream oss;
            oss << "RegSHOMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", stock=" << stock
                << ", reg_sho_action=" << reg_sho_action
                << "]";
            return oss.str();
        }
        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline RegSHOMessage parse_reg_sho(const char* p) {
        using namespace itch::endian;
        RegSHOMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        std::memcpy(msg.stock, p + 11, 8);
        msg.stock[8] = '\0';
        msg.reg_sho_action = p[19];
        return msg;
    }

    static_assert(sizeof(RegSHOMessage) == 22, "RegSHOMessage size mismatch");

} // namespace itch

#pragma pack(pop)
