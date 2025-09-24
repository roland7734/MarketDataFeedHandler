#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <cstring>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct MarketParticipantPositionMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        char mpid[5];   // 4 chars + null terminator
        char stock[9];  // 8 chars + null terminator
        char primary_mm; // 'Y' or 'N'
        char mm_mode;   // N, P, S, R, L
        char mp_state;  // A, E, W, S, D

        std::string toString() const {
            std::ostringstream oss;
            oss << "MarketParticipantPositionMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", mpid=" << mpid
                << ", stock=" << stock
                << ", primary_mm=" << primary_mm
                << ", mm_mode=" << mm_mode
                << ", mp_state=" << mp_state
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline MarketParticipantPositionMessage parse_market_participant(const char* p) {
        using namespace itch::endian;
        MarketParticipantPositionMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        std::memcpy(msg.mpid, p + 11, 4);
        msg.mpid[4] = '\0';
        std::memcpy(msg.stock, p + 15, 8);
        msg.stock[8] = '\0';
        msg.primary_mm = p[23];
        msg.mm_mode    = p[24];
        msg.mp_state   = p[25];
        return msg;
    }

    static_assert(sizeof(MarketParticipantPositionMessage) == 29, "MarketParticipantPositionMessage size mismatch");

} // namespace itch

#pragma pack(pop)
