#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct SystemEventMessage {
        uint16_t stock_locate;     // always 0
        uint16_t tracking_number;
        uint64_t timestamp;
        char event_code;           // 'O', 'S', 'Q', 'M', 'E', 'C'

        std::string toString() const {
            std::ostringstream oss;
            oss << "SystemEventMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", event_code=" << event_code
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline SystemEventMessage parse_system_event(const char* p) {
        using namespace itch::endian;
        SystemEventMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        msg.event_code      = p[11];
        return msg;
    }

    static_assert(sizeof(SystemEventMessage) == 13, "SystemEventMessage size mismatch");

} // namespace itch

#pragma pack(pop)
