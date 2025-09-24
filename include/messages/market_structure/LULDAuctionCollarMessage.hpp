#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <cstring>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct LULDAuctionCollarMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        char stock[9]; // 8 + null
        uint64_t ref_price;
        uint64_t upper_price;
        uint64_t lower_price;
        uint32_t extensions;

        std::string toString() const {
            std::ostringstream oss;
            oss << "LULDAuctionCollarMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", stock=" << stock
                << ", ref_price=" << ref_price
                << ", upper_price=" << upper_price
                << ", lower_price=" << lower_price
                << ", extensions=" << extensions
                << "]";
            return oss.str();
        }

        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline LULDAuctionCollarMessage parse_luld(const char* p) {
        using namespace itch::endian;
        LULDAuctionCollarMessage msg{};
        msg.stock_locate    = read_u16(p + 1);
        msg.tracking_number = read_u16(p + 3);
        msg.timestamp       = read_u48(p + 5);
        std::memcpy(msg.stock, p + 11, 8);
        msg.stock[8] = '\0';
        msg.ref_price       = read_u64(p + 19);
        msg.upper_price     = read_u64(p + 27);
        msg.lower_price     = read_u64(p + 35);
        msg.extensions      = read_u32(p + 43);
        return msg;
    }

    static_assert(sizeof(LULDAuctionCollarMessage) == 49, "LULDAuctionCollarMessage size mismatch");

} // namespace itch

#pragma pack(pop)
