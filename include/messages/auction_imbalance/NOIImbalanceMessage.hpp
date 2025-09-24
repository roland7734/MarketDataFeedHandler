#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <cstring>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

    struct NOIImbalanceMessage {
        uint16_t stock_locate;
        uint16_t tracking_number;
        uint64_t timestamp;
        uint64_t paired_shares;
        uint64_t imbalance_shares;
        char stock[9]; // 8 + null
        uint32_t far_price;
        uint32_t near_price;
        uint32_t ref_price;
        char cross_type;       // O, C, H
        char price_var_ind;    // L, 1..9, A, B, C, space

        std::string toString() const {
            std::ostringstream oss;
            oss << "NOIImbalanceMessage ["
                << "stock_locate=" << stock_locate
                << ", tracking_number=" << tracking_number
                << ", timestamp=" << timestamp
                << ", paired_shares=" << paired_shares
                << ", imbalance_shares=" << imbalance_shares
                << ", stock=" << stock
                << ", far_price=" << far_price
                << ", near_price=" << near_price
                << ", ref_price=" << ref_price
                << ", cross_type=" << cross_type
                << ", price_var_ind=" << price_var_ind
                << "]";
            return oss.str();
        }
        void logParsed() const {
            Logger::getInstance().log("Parsed: " + toString());
        }
    };

    inline NOIImbalanceMessage parse_noii(const char* p) {
        using namespace itch::endian;
        NOIImbalanceMessage msg{};
        msg.stock_locate     = read_u16(p + 1);
        msg.tracking_number  = read_u16(p + 3);
        msg.timestamp        = read_u48(p + 5);
        msg.paired_shares    = read_u64(p + 11);
        msg.imbalance_shares = read_u64(p + 19);
        std::memcpy(msg.stock, p + 27, 8);
        msg.stock[8] = '\0';
        msg.far_price        = read_u32(p + 35);
        msg.near_price       = read_u32(p + 39);
        msg.ref_price        = read_u32(p + 43);
        msg.cross_type       = p[47];
        msg.price_var_ind    = p[48];
        return msg;
    }

    static_assert(sizeof(NOIImbalanceMessage) == 51, "NOIImbalanceMessage size mismatch");

} // namespace itch

#pragma pack(pop)
