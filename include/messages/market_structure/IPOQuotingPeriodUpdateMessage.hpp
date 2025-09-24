#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <cstring>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct IPOQuotingPeriodUpdateMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        char stock[9]; // 8 chars + null
        uint32_t quote_release_time; // seconds since midnight
        char quote_release_qual;     // 'A' or 'C'
        uint64_t ipo_price;          // fixed-point price

        std::string toString() const {
            std::ostringstream oss;
            oss << "IPOQuotingPeriodUpdateMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", stock=" << stock
                << ", quote_release_time=" << quote_release_time
                << ", quote_release_qual=" << quote_release_qual
                << ", ipo_price=" << ipo_price
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline IPOQuotingPeriodUpdateMessage parse_ipo_quoting(const char* p) {
        using namespace itch::endian;
        IPOQuotingPeriodUpdateMessage msg{};
        msg.stock_locate        = read_u16(p + 1);
        msg.tracking_number     = read_u16(p + 3);
        msg.timestamp           = read_u48(p + 5);
        std::memcpy(msg.stock, p + 11, 8);
        msg.stock[8] = '\0';
        msg.quote_release_time  = read_u32(p + 19);
        msg.quote_release_qual  = p[23];
        msg.ipo_price           = read_u64(p + 24);
        return msg;
    }

    static_assert(sizeof(IPOQuotingPeriodUpdateMessage) == 34, "IPOQuotingPeriodUpdateMessage size mismatch");

} // namespace itch

#pragma pack(pop)
