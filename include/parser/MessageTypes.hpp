#pragma once

namespace itch {

    // -------------------------
    // Add / Order Messages
    // -------------------------
    constexpr char MSG_ADD_ORDER             = 'A'; // Add Order
    constexpr char MSG_ADD_ORDER_MPID        = 'F'; // Add Order with MPID Attribution

    constexpr char MSG_ORDER_EXECUTED        = 'E'; // Order Executed
    constexpr char MSG_ORDER_EXECUTED_PRICE  = 'C'; // Order Executed with Price
    constexpr char MSG_ORDER_CANCEL          = 'X'; // Order Cancel
    constexpr char MSG_ORDER_DELETE          = 'D'; // Order Delete
    constexpr char MSG_ORDER_REPLACE         = 'U'; // Order Replace

    // -------------------------
    // Trade Messages
    // -------------------------
    constexpr char MSG_TRADE                 = 'P'; // Trade Message (non-cross)
    constexpr char MSG_CROSS_TRADE           = 'Q'; // Cross Trade
    constexpr char MSG_BROKEN_TRADE          = 'B'; // Broken Trade

    // -------------------------
    // System / Administrative Messages
    // -------------------------
    constexpr char MSG_SYSTEM_EVENT          = 'S'; // System Event
    constexpr char MSG_STOCK_DIRECTORY       = 'R'; // Stock Directory
    constexpr char MSG_TRADING_ACTION        = 'H'; // Stock Trading Action
    constexpr char MSG_OPERATIONAL_HALT      = 'h'; // Operational Halt

    // -------------------------
    // Regulatory / Market Structure Messages
    // -------------------------
    constexpr char MSG_REG_SHO               = 'Y'; // Reg SHO Short Sale Price Test Indicator
    constexpr char MSG_MKT_PARTICIPANT_POS   = 'L'; // Market Participant Position
    constexpr char MSG_MWCB_DECLINE          = 'V'; // Market-Wide Circuit Breaker Decline Level
    constexpr char MSG_MWCB_STATUS           = 'W'; // Market-Wide Circuit Breaker Status
    constexpr char MSG_IPO_QUOTE_UPDATE      = 'K'; // IPO Quoting Period Update
    constexpr char MSG_LULD_AUCTION_COLLAR   = 'J'; // LULD Auction Collar

    // -------------------------
    // Auction / Imbalance Messages
    // -------------------------
    constexpr char MSG_NOII                  = 'I'; // Net Order Imbalance Indicator
    constexpr char MSG_RPII                  = 'N'; // Retail Price Improvement Indicator
    // -------------------------
    // Message Sizes (ITCH 5.0 protocol)
    // -------------------------
    constexpr std::size_t MSG_ADD_ORDER_SIZE             = 36;
    constexpr std::size_t MSG_ADD_ORDER_MPID_SIZE        = 40;

    constexpr std::size_t MSG_ORDER_EXECUTED_SIZE        = 31;
    constexpr std::size_t MSG_ORDER_EXECUTED_PRICE_SIZE  = 36;
    constexpr std::size_t MSG_ORDER_CANCEL_SIZE          = 23;
    constexpr std::size_t MSG_ORDER_DELETE_SIZE          = 19;
    constexpr std::size_t MSG_ORDER_REPLACE_SIZE         = 35;

    constexpr std::size_t MSG_TRADE_SIZE                 = 44;
    constexpr std::size_t MSG_CROSS_TRADE_SIZE           = 40;
    constexpr std::size_t MSG_BROKEN_TRADE_SIZE          = 19;

    constexpr std::size_t MSG_SYSTEM_EVENT_SIZE          = 12;
    constexpr std::size_t MSG_STOCK_DIRECTORY_SIZE       = 39;
    constexpr std::size_t MSG_TRADING_ACTION_SIZE        = 25;
    constexpr std::size_t MSG_OPERATIONAL_HALT_SIZE      = 21;

    constexpr std::size_t MSG_REG_SHO_SIZE               = 20;
    constexpr std::size_t MSG_MKT_PARTICIPANT_POS_SIZE   = 26;
    constexpr std::size_t MSG_MWCB_DECLINE_SIZE          = 35;
    constexpr std::size_t MSG_MWCB_STATUS_SIZE           = 12;
    constexpr std::size_t MSG_IPO_QUOTE_UPDATE_SIZE      = 28;
    constexpr std::size_t MSG_LULD_AUCTION_COLLAR_SIZE   = 35;

    constexpr std::size_t MSG_NOII_SIZE                  = 50;
    constexpr std::size_t MSG_RPII_SIZE                  = 20;
} // namespace itch
