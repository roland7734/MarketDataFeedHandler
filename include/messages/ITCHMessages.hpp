#pragma once

// === Add order messages ===
#include "messages/add/AddOrderMessage.hpp"
#include "messages/add/AddOrderMPIDMessage.hpp"

// === Auction imbalance messages ===
#include "messages/auction_imbalance/NOIImbalanceMessage.hpp"
#include "messages/auction_imbalance/RPIIMessage.hpp"

// === Market structure messages ===
#include "messages/market_structure/IPOQuotingPeriodUpdateMessage.hpp"
#include "messages/market_structure/LULDAuctionCollarMessage.hpp"
#include "messages/market_structure/MarketParticipantPositionMessage.hpp"
#include "messages/market_structure/MWCBDeclineLevelMessage.hpp"
#include "messages/market_structure/MWCBStatusMessage.hpp"
#include "messages/market_structure/RegSHOMessage.hpp"

// === Order messages ===
#include "messages/order/CancelOrderMessage.hpp"
#include "messages/order/DeleteOrderMessage.hpp"
#include "messages/order/ExecuteOrderMessage.hpp"
#include "messages/order/ExecuteOrderWithPriceMessage.hpp"
#include "messages/order/ReplaceOrderMessage.hpp"

// === System messages ===
#include "messages/system/OperationalHaltMessage.hpp"
#include "messages/system/StockDirectoryMessage.hpp"
#include "messages/system/StockTradingActionMessage.hpp"
#include "messages/system/SystemEventMessage.hpp"

// === Trade messages ===
#include "messages/trade/BrokenTradeMessage.hpp"
#include "messages/trade/CrossTradeMessage.hpp"
#include "messages/trade/TradeMessage.hpp"
