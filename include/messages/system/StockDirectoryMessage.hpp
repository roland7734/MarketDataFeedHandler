#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include "../../parser/Endian.hpp"

#pragma pack(push, 1)

namespace itch {

struct StockDirectoryMessage {
    uint16_t stock_locate;
    uint16_t tracking_number;
    uint64_t timestamp;
    char stock[9];             // 8-char symbol + null
    char market_category;
    char financial_status;
    uint32_t round_lot_size;
    char round_lots_only;
    char issue_classification;
    char issue_sub_type[2];
    char authenticity;
    char short_sale_threshold;
    char ipo_flag;
    char ludl_reference;
    char etp_flag;
    uint32_t etp_leverage;
    char inverse_indicator;

    std::string toString() const {
        std::ostringstream oss;
        oss << "StockDirectoryMessage ["
            << "stock_locate=" << stock_locate
            << ", tracking_number=" << tracking_number
            << ", timestamp=" << timestamp
            << ", stock=" << stock
            << ", market_category=" << market_category
            << ", financial_status=" << financial_status
            << ", round_lot_size=" << round_lot_size
            << ", round_lots_only=" << round_lots_only
            << ", issue_classification=" << issue_classification
            << ", issue_sub_type=" << issue_sub_type[0] << issue_sub_type[1]
            << ", authenticity=" << authenticity
            << ", short_sale_threshold=" << short_sale_threshold
            << ", ipo_flag=" << ipo_flag
            << ", ludl_reference=" << ludl_reference
            << ", etp_flag=" << etp_flag
            << ", etp_leverage=" << etp_leverage
            << ", inverse_indicator=" << inverse_indicator
            << "]";
        return oss.str();
    }

    void logParsed() const {
        Logger::getInstance().log("Parsed: " + toString());
    }
};

inline StockDirectoryMessage parse_stock_directory(const char* p) {
    using namespace itch::endian;
    StockDirectoryMessage msg{};
    msg.stock_locate      = read_u16(p + 1);
    msg.tracking_number   = read_u16(p + 3);
    msg.timestamp         = read_u48(p + 5);
    memcpy(msg.stock, p + 11, 8);
    msg.stock[8]          = '\0';
    msg.market_category   = p[19];
    msg.financial_status  = p[20];
    msg.round_lot_size    = read_u32(p + 21);
    msg.round_lots_only   = p[25];
    msg.issue_classification = p[26];
    memcpy(msg.issue_sub_type, p + 27, 2);
    msg.authenticity      = p[29];
    msg.short_sale_threshold = p[30];
    msg.ipo_flag          = p[31];
    msg.ludl_reference    = p[32];
    msg.etp_flag          = p[33];
    msg.etp_leverage      = read_u32(p + 34);
    msg.inverse_indicator = p[38];
    return msg;
}

static_assert(sizeof(StockDirectoryMessage) == 41, "StockDirectoryMessage size mismatch");

} // namespace itch

#pragma pack(pop)
