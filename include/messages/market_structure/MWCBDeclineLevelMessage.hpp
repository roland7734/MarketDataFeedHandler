#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct MWCBDeclineLevelMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t level1;
        uint64_t level2;
        uint64_t level3;

        std::string toString() const {
            std::ostringstream oss;
            oss << "MWCBDeclineLevelMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", level1=" << level1
                << ", level2=" << level2
                << ", level3=" << level3
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline MWCBDeclineLevelMessage parse_mwcb_decline(const char* p) {
        using namespace itch::endian;
        MWCBDeclineLevelMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.level1          = read_u64(p + 11);
        msg.level2          = read_u64(p + 19);
        msg.level3          = read_u64(p + 27);
        return msg;
    }

    static_assert(sizeof(MWCBDeclineLevelMessage) == 36, "MWCBDeclineLevelMessage size mismatch");

} // namespace itch

#pragma pack(pop)
