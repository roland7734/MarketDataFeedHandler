#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct MWCBStatusMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        char breached_level; // '1', '2', or '3'

        std::string toString() const {
            std::ostringstream oss;
            oss << "MWCBStatusMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", breached_level=" << breached_level
                << "]";
            return oss.str();
        }
        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline MWCBStatusMessage parse_mwcb_status(const char* p) {
        using namespace itch::endian;
        MWCBStatusMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.breached_level  = p[11];
        return msg;
    }

    static_assert(sizeof(MWCBStatusMessage) == 13, "MWCBStatusMessage size mismatch");

} // namespace itch

#pragma pack(pop)
