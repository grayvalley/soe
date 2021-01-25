/*
 * Copyright 2020 Juha-Samuli Hellén
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iostream>
#include <grayvalley/soe/SOE.hh>

namespace GVT::SOE {
    std::map<std::string, SOE::MESSAGE_TYPE> soe_enum_map = {
            {"X", SOE::MESSAGE_TYPE_ORDER_CANCELED},
            {"E", SOE::MESSAGE_TYPE_ORDER_EXECUTED},
            {"Y", SOE::MESSAGE_TYPE_ORDER_ACCEPTED},
            {"R", SOE::MESSAGE_TYPE_ORDER_REJECTED}
    };
}

namespace GVT::SOE {
    std::map<std::string, SIDE> map_str_side_to_enum = {
            {"B", SIDE::B},
            {"S", SIDE::S}
    };
}
namespace GVT::SOE {
    std::map<SIDE, std::string> map_enum_side_to_str = {
            {SIDE::B, "B"},
            {SIDE::S, "S"}
    };
}

namespace GVT::SOE {
    std::map<std::string, ORDER_TYPE> map_str_order_type_to_enum = {
            {"LMT", ORDER_TYPE::LIMIT},
            {"MKT", ORDER_TYPE::MARKET}
    };
}

namespace GVT::SOE {
    std::map<ORDER_TYPE, std::string> map_enum_order_type_to_str = {
            {ORDER_TYPE::LIMIT, "LMT"},
            {ORDER_TYPE::MARKET, "MKT"}
    };
}

/**
 * Populates the body of the message from a buffer
 *
 * @param buffer: pointer to the beginning of a buffer
 * @param len: length of the message
 */
namespace GVT::SOE {
    void Message::from(char* buffer, size_t len) {
        m_body = nlohmann::json::parse(buffer, buffer + len);
    }
}

/**
 * Return type id of the message
 *
 * @return: integer id
 */
namespace GVT::SOE {
    int Message::type() const {

        if(m_body.empty()){
            return MESSAGE_TYPE_EMPTY;
        }

        try {
            auto value = m_body["message-type"].get<std::string>();
            return soe_enum_map.find(value)->second;
        } catch (nlohmann::json::exception& e) {
            return MESSAGE_TYPE_INVALID;
        }
    }
}

/**
 * Return an item from the message body
 */
namespace GVT::SOE {
    template <typename T>
    T Message::get(std::string key) {
        return m_body[key].get<T>();
    }
}

namespace GVT::SOE {
    std::string Message::dump() {
        return m_body.dump();
    }
}

/**
 * Get nlohmann::json object from OrderAddMessage.
 */
namespace GVT::SOE {
    nlohmann::json OrderNewMessage::to_json() {
        nlohmann::json payload;
        payload["message-type"] = "A";
        payload["instrument"] = Instrument;
        payload["price"] = Price;
        payload["quantity"] = Quantity;
        payload["side"] = map_enum_side_to_str[Side];
        payload["order-type"] = map_enum_order_type_to_str[OrderType];
        return payload;
    }
}

/**
 * Get nlohmann::json object from OrderCancelMessage.
 */
namespace GVT::SOE {
    nlohmann::json OrderCancelMessage::to_json() {
        nlohmann::json payload;
        payload["message-type"] = "X";
        payload["order-id"] = OrderId;
        return payload;
    }
}

/**
 * Get OrderAcceptedMessage from generic IMessage.
 */
namespace GVT::SOE {
    void OrderAcceptedMessage::get(IMessage* p_imessage) {
        auto* p_message = reinterpret_cast<GVT::SOE::Message*>(p_imessage);
        Instrument = p_message->get<std::string>("instrument");
        OrderId   = p_message->get<uint64_t>("order-id");
        Price     = p_message->get<uint64_t>("price");
        Quantity  = p_message->get<uint64_t>("quantity");
        auto side = p_message->get<std::string>("side");
        Side      = map_str_side_to_enum.find(side)->second;
        auto order_type =  p_message->get<std::string>("order-type");
        OrderType = map_str_order_type_to_enum.find(order_type)->second;
    }
}

/**
 * Get SOE OrderAcceptedEvent from OrderAcceptedMessage.
 */
namespace GVT::SOE {
    void OrderAcceptedMessage::put(IOrderAcceptedEvent* p_event){
        p_event->Exchange = "sandbox";
        p_event->Instrument = Instrument;
        p_event->OrderId = OrderId;
        p_event->Price = Price;
        p_event->Quantity = Quantity;
        p_event->Side = Side;
        p_event->OrderType = OrderType;
    }
}

/**
 * Get SOE OrderRejectedMessage from generic IMessage.
 */
namespace GVT::SOE {
    void OrderRejectedMessage::get(IMessage* p_imessage) {
        auto* p_message = reinterpret_cast<GVT::SOE::Message*>(p_imessage);
        Instrument = p_message->get<std::string>("instrument");
        Price      = p_message->get<uint64_t>("price");
        Quantity   = p_message->get<uint64_t>("quantity");
        auto side  = p_message->get<std::string>("side");
        Side       = map_str_side_to_enum[side];
        auto order_type = p_message->get<std::string>("order-type");
        OrderType = map_str_order_type_to_enum[order_type];
        Reason    = p_message->get<std::string>("reason");
    }
}

/**
 * Get OrderRejectedEvent from OrderRejectedMessage.
 */
namespace GVT::SOE {
    void OrderRejectedMessage::put(IOrderRejectedEvent* p_event){
        p_event->Exchange = "sandbox";
        p_event->Instrument = Instrument;
        p_event->Price = Price;
        p_event->Quantity = Quantity;
        p_event->Side = Side;
        p_event->OrderType = OrderType;
        p_event->Reason = Reason;
    }
}

/**
 * Get OrderExecutedMessage from generic IMessage.
 */
namespace GVT::SOE {
    void OrderExecutedMessage::get(IMessage* p_imessage) {
        auto* p_message = reinterpret_cast<GVT::SOE::Message*>(p_imessage);
        Instrument = p_message->get<std::string>("instrument");
        OrderId = p_message->get<uint64_t>("order-id");
        Price = p_message->get<uint64_t>("price");
        Quantity = p_message->get<uint64_t>("quantity");
        auto side = p_message->get<std::string>("side");
        Side = map_str_side_to_enum.find(side)->second;

    }
}

/**
 * Get OrderExecutedEvent from OrderExecutedMessage.
 */
namespace GVT::SOE {
    void OrderExecutedMessage::put(IOrderExecutedEvent* p_event){
        p_event->Exchange = "sandbox";
        p_event->Instrument = Instrument;
        p_event->OrderId = OrderId;
        p_event->Price = Price;
        p_event->Quantity = Quantity;
        p_event->Side = Side;

    }
}

/**
 * Get OrderCanceledMessage from generic IMessage.
 */
namespace GVT::SOE {
    void OrderCanceledMessage::get(IMessage* p_imessage) {
        auto* p_message = reinterpret_cast<GVT::SOE::Message*>(p_imessage);
        OrderId   = p_message->get<uint64_t>("order-id");
        Price     = p_message->get<uint64_t>("price");
        Quantity  = p_message->get<uint64_t>("quantity");
        auto side = p_message->get<std::string>("side");
        Side      = map_str_side_to_enum.find(side)->second;
        Reason    = p_message->get<std::string>("reason");
    }
}

/**
 * Get OrderExecutedEvent from OrderExecutedMessage.
 */
 namespace GVT::SOE {
     void OrderCanceledMessage::put(IOrderCanceledEvent* p_event) {
         p_event->Exchange = "sandbox";
         p_event->Instrument = Instrument;
         p_event->OrderId = OrderId;
         p_event->Price = Price;
         p_event->Quantity = Quantity;
         p_event->Side = Side;
         p_event->Reason = Reason;
     }
 }

namespace GVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderNewMessage& order){
        s <<      " --- [OrderAddMessage] ---"  << std::endl;
        s << "Instrument: " << order.Instrument << std::endl;
        s << "Price: "      << order.Price      << std::endl;
        s << "Quantity: "   << order.Quantity   << std::endl;
        s << "Side: "       << map_enum_side_to_str[order.Side] << std::endl;
        s << "OrderType: "  << map_enum_order_type_to_str[order.OrderType] << std::endl;
        return s;
    }
}

namespace GVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderCancelMessage& order){
        s <<   " --- [OrderCancelMessage] ---" << std::endl;
        s << "OrderId: " << order.OrderId      << std::endl;
        return s;
    }
}

namespace GVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderAcceptedMessage& order){
        s <<     " --- [OrderAcceptedMessage] ---" << std::endl;
        s << "OrderId: "  << order.OrderId      << std::endl;
        s << "Price: "    << order.Price        << std::endl;
        s << "Quantity: " << order.Quantity     << std::endl;
        s << "Side: "       << map_enum_side_to_str[order.Side] << std::endl;
        s << "OrderType: "  << map_enum_order_type_to_str[order.OrderType] << std::endl;
        return s;
    }
}

namespace GVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderRejectedMessage& order){
        s << " --- [OrderRejectedMessage] ---"    << std::endl;
        s << "Price: "      << order.Price        << std::endl;
        s << "Quantity: "   << order.Quantity     << std::endl;
        s << "Side: "       << map_enum_side_to_str[order.Side] << std::endl;
        s << "OrderType: "  << map_enum_order_type_to_str[order.OrderType] << std::endl;
        s << "Reason: "     << order.Reason << std::endl;
        return s;
    }
}

namespace GVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderExecutedMessage& order){
        s << " --- [OrderExecutedMessage] ---" << std::endl;
        s << "OrderId: "  << order.OrderId     << std::endl;
        s << "Price: "    << order.Price       << std::endl;
        s << "Quantity: " << order.Quantity    << std::endl;
        return s;
    }
}

namespace GVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderCanceledMessage& order){
        s << " --- [OrderCanceledMessage] ---" << std::endl;
        s << "OrderId: "  << order.OrderId     << std::endl;
        s << "Price: "    << order.Price       << std::endl;
        s << "Quantity: " << order.Quantity    << std::endl;
        s << "Side: "     << map_enum_side_to_str[order.Side] << std::endl;
        return s;
    };
}
