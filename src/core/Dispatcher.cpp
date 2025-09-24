#include "core/Dispatcher.hpp"
#include <stdexcept>
#include <memory>
#include <cstring>
#include <iostream>

#include "messages/ITCHMessages.hpp"
#include "parser/MessageTypes.hpp"


void Dispatcher::dispatch(const char* msg) {
    char type = msg[0];

    // std::cout<<"Received message type: " << type << "\n";
    // std::cout<<"Message content: " << std::string(msg, message_length(type)) << "\n";

    switch (type) {
        case itch::MSG_ADD_ORDER: {
            auto orderMsg = itch::parse_add_order(msg);
            auto order = std::make_shared<Order>(
                orderMsg.order_ref,
                std::string(orderMsg.stock),
                orderMsg.side,
                orderMsg.shares,
                orderMsg.price
            );
            // Logger::getInstance().log("Parsed " + orderMsg.toString());

            orderBookManager_.add_order(order);
            break;
        }
        case itch::MSG_ADD_ORDER_MPID: {
            auto orderMsg = itch::parse_add_order_mpid(msg);
            auto order = std::make_shared<Order>(
                orderMsg.order_ref,
                std::string(orderMsg.stock),
                orderMsg.side,
                orderMsg.shares,
                orderMsg.price,
                std::string(orderMsg.mpid)
            );
            // Logger::getInstance().log("Parsed " + orderMsg.toString());

            orderBookManager_.add_order(order);

            break;
        }
        case itch::MSG_ORDER_CANCEL: {
            auto cancelMsg = itch::parse_cancel_order(msg);
            orderBookManager_.cancel_order(
                cancelMsg.order_ref,
                cancelMsg.quantity
            );
            // Logger::getInstance().log("Parsed " + cancelMsg.toString());

            break;
        }
        case itch::MSG_ORDER_DELETE: {
            auto deleteMsg = itch::parse_delete_order(msg);
            orderBookManager_.delete_order(
                deleteMsg.order_ref
            );
            // Logger::getInstance().log("Parsed " + deleteMsg.toString());
            break;
        }
        case itch::MSG_ORDER_REPLACE: {
            auto replaceMsg = itch::parse_replace_order(msg);
            orderBookManager_.replace_order(
                replaceMsg.original_order_ref,
                replaceMsg.new_order_ref,
                replaceMsg.shares,
                replaceMsg.price
            );
            break;
        }
        case itch::MSG_ORDER_EXECUTED: {
            auto execMsg = itch::parse_execute_order(msg);
            orderBookManager_.execute_order(
                execMsg.order_ref,
                execMsg.quantity
            );
            // Logger::getInstance().log("Parsed " + execMsg.toString());

            break;
        }
        case itch::MSG_ORDER_EXECUTED_PRICE: {
            auto execMsg = itch::parse_execute_with_price(msg);
            orderBookManager_.execute_order_with_price(
                execMsg.order_ref,
                execMsg.quantity,
                execMsg.price,
                execMsg.printable == 'Y',
                execMsg.match_id
            );
            // Logger::getInstance().log("Parsed " + execMsg.toString());

            break;
        }
        // --- Trade Messages ---
        case itch::MSG_TRADE: {
            auto tradeMsg = itch::parse_trade(msg);
            // Logger::getInstance().log("Parsed " + tradeMsg.toString());

            break;
        }
        case itch::MSG_CROSS_TRADE: {
            auto crossMsg = itch::parse_cross_trade(msg);
            // Logger::getInstance().log("Parsed " + crossMsg.toString());
            break;
        }
        case itch::MSG_BROKEN_TRADE: {
            auto brokenMsg = itch::parse_broken_trade(msg);
            // Logger::getInstance().log("Parsed " + brokenMsg.toString());
            break;
        }
        // --- System / Admin Messages ---
        case itch::MSG_SYSTEM_EVENT: {
            auto sysMsg = itch::parse_system_event(msg);
            // Logger::getInstance().log("Parsed " + sysMsg.toString());
            break;
        }
        case itch::MSG_STOCK_DIRECTORY: {
            auto dirMsg = itch::parse_stock_directory(msg);
            // Logger::getInstance().log("Parsed " + dirMsg.toString());
            break;
        }
        case itch::MSG_TRADING_ACTION: {
            auto actionMsg = itch::parse_stock_trading_action(msg);
            // Logger::getInstance().log("Parsed " + actionMsg.toString());
            break;
        }
        case itch::MSG_OPERATIONAL_HALT: {
            auto haltMsg = itch::parse_halt(msg);
            // Logger::getInstance().log("Parsed " + haltMsg.toString());
            break;
        }
        // --- Regulatory / Market Structure ---
        case itch::MSG_REG_SHO: {
            auto regShoMsg = itch::parse_reg_sho(msg);
            // Logger::getInstance().log("Parsed " + regShoMsg.toString());
            break;
        }
        case itch::MSG_MKT_PARTICIPANT_POS: {
            auto  mktPosMsg = itch::parse_market_participant(msg);
            // Logger::getInstance().log("Parsed " + mktPosMsg.toString());
            break;
        }
        case itch::MSG_MWCB_DECLINE: {
            auto mwcbDeclineMsg = itch::parse_mwcb_decline(msg);
            // Logger::getInstance().log("Parsed " + mwcbDeclineMsg.toString());
            break;
        }
        case itch::MSG_MWCB_STATUS: {
            auto mwcbStatusMsg = itch::parse_mwcb_status(msg);
            // Logger::getInstance().log("Parsed " + mwcbStatusMsg.toString());
            break;
        }
        case itch::MSG_IPO_QUOTE_UPDATE: {
            auto ipoQuoteMsg = itch::parse_ipo_quoting(msg);
            // Logger::getInstance().log("Parsed " + ipoQuoteMsg.toString());
            break;
        }
        case itch::MSG_LULD_AUCTION_COLLAR: {
            auto luldMsg = itch::parse_luld(msg);
            // Logger::getInstance().log("Parsed " + luldMsg.toString());
            break;
        }
        // --- Auction / Imbalance ---
        case itch::MSG_NOII: {
            auto noiiMsg = itch::parse_noii(msg);
            // Logger::getInstance().log("Parsed " + noiiMsg.toString());
            break;
        }
        case itch::MSG_RPII: {
            auto rpiiMsg = itch::parse_rpii(msg);
            // Logger::getInstance().log("Parsed " + rpiiMsg.toString());
            break;
        }
        default:
            // std::cerr << "Unknown message type: " << type << "\n";
            break;
    }
}
std::size_t Dispatcher::message_length(char msgType) const {
    switch (msgType) {
        case itch::MSG_ADD_ORDER:             return itch::MSG_ADD_ORDER_SIZE;
        case itch::MSG_ADD_ORDER_MPID:        return itch::MSG_ADD_ORDER_MPID_SIZE;
        case itch::MSG_ORDER_EXECUTED:        return itch::MSG_ORDER_EXECUTED_SIZE;
        case itch::MSG_ORDER_EXECUTED_PRICE:  return itch::MSG_ORDER_EXECUTED_PRICE_SIZE;
        case itch::MSG_ORDER_CANCEL:          return itch::MSG_ORDER_CANCEL_SIZE;
        case itch::MSG_ORDER_DELETE:          return itch::MSG_ORDER_DELETE_SIZE;
        case itch::MSG_ORDER_REPLACE:         return itch::MSG_ORDER_REPLACE_SIZE;
        // --- Trade Messages ---
        case itch::MSG_TRADE:                 return itch::MSG_TRADE_SIZE;
        case itch::MSG_CROSS_TRADE:           return itch::MSG_CROSS_TRADE_SIZE;
        case itch::MSG_BROKEN_TRADE:          return itch::MSG_BROKEN_TRADE_SIZE;
        // --- System / Admin Messages ---
        case itch::MSG_SYSTEM_EVENT:          return itch::MSG_SYSTEM_EVENT_SIZE;
        case itch::MSG_STOCK_DIRECTORY:       return itch::MSG_STOCK_DIRECTORY_SIZE;
        case itch::MSG_TRADING_ACTION:        return itch::MSG_TRADING_ACTION_SIZE;
        case itch::MSG_OPERATIONAL_HALT:      return itch::MSG_OPERATIONAL_HALT_SIZE;
        // --- Regulatory / Market Structure ---
        case itch::MSG_REG_SHO:               return itch::MSG_REG_SHO_SIZE;
        case itch::MSG_MKT_PARTICIPANT_POS:   return itch::MSG_MKT_PARTICIPANT_POS_SIZE;
        case itch::MSG_MWCB_DECLINE:          return itch::MSG_MWCB_DECLINE_SIZE;
        case itch::MSG_MWCB_STATUS:           return itch::MSG_MWCB_STATUS_SIZE;
        case itch::MSG_IPO_QUOTE_UPDATE:      return itch::MSG_IPO_QUOTE_UPDATE_SIZE;
        case itch::MSG_LULD_AUCTION_COLLAR:   return itch::MSG_LULD_AUCTION_COLLAR_SIZE;
        // --- Auction / Imbalance ---
        case itch::MSG_NOII:                  return itch::MSG_NOII_SIZE;
        case itch::MSG_RPII:                  return itch::MSG_RPII_SIZE;
        default: return 0;
    }
}
