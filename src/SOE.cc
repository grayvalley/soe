#include <grayvalley/soe/SOE.hh>
#include <iostream>

namespace QVT::SOE {
    std::map<std::string, SOE::MESSAGE_TYPE> soe_enum_map = {
            {"A", SOE::MESSAGE_TYPE_ORDER_ADD},
            {"C", SOE::MESSAGE_TYPE_ORDER_CANCEL},
            {"E", SOE::MESSAGE_TYPE_ORDER_EXECUTED},
            {"Y", SOE::MESSAGE_TYPE_ORDER_ACCEPTED},
            {"R", SOE::MESSAGE_TYPE_ORDER_REJECTED}
    };
}

namespace QVT::SOE {
    std::map<std::string, SIDE> map_side_char_enum = {
            {"B", SIDE::B},
            {"S", SIDE::S}
    };
}

namespace QVT::SOE {
    std::map<std::string, ORDER_TYPE> map_str_order_type_enum = {
            {"LMT", ORDER_TYPE::LIMIT},
            {"MKT", ORDER_TYPE::MARKET}
    };
}

namespace QVT::SOE {
    SOE::MESSAGE_TYPE Message::messageType() {
        if(m_body.empty()){
            return MESSAGE_TYPE_EMPTY;
        }
        try{
            auto type = m_body["message-type"].get<std::string>();
            return soe_enum_map.find(type)->second;
        } catch (nlohmann::json::exception& e){
            return MESSAGE_TYPE_INVALID;
        }
    }
}

namespace QVT::SOE {
    void Message::from(char* buffer, size_t len) {
        m_body = nlohmann::json::parse(buffer, buffer + len);
    }
}

namespace QVT::SOE {
    template <typename T>
    T Message::get(const std::string& key) {
        return m_body[key].get<T>();
    }
}

namespace QVT::SOE {
    void Message::print() {
        std::cout << m_body.dump() << std::endl;
    }
}

namespace QVT::SOE {
    void OrderAdd::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
        auto side = message->get<std::string>("side");
    }
}

namespace QVT::SOE {
    nlohmann::json OrderAdd::to_json() {
        nlohmann::json payload;
        payload["message-type"] = "E";
        payload["price"] = Price;
        payload["quantity"] = Quantity;
        if(Side == SIDE::B){
            payload["side"] = "B";
        }
        else if(Side == SIDE::S){
            payload["side"] = "S";
        }
        if(OrderType == ORDER_TYPE::LIMIT){
            payload["order-type"] = "LMT";
        }
        else if(OrderType == ORDER_TYPE::MARKET){
            payload["order-type"] = "MKT";
        }
        return payload;
    }
}

namespace QVT::SOE {
    nlohmann::json OrderCancel::to_json() {
        nlohmann::json payload;
        payload["message-type"] = "X";
        payload["order-id"] = OrderId;
        return payload;
    }
}

namespace QVT::SOE {
    void OrderAccepted::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
        auto side = message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
        auto order_type = message->get<std::string>("order-type");
        OrderType = map_str_order_type_enum.find(side)->second;
    }
}

namespace QVT::SOE {
    void OrderRejected::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Reason = message->get<std::string>("reason");
    }
}

namespace QVT::SOE {
    void OrderExecuted::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
        auto side = message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
        auto order_type = message->get<std::string>("order-type");
        OrderType = map_str_order_type_enum.find(side)->second;
    }
}

namespace QVT::SOE {
    void OrderCanceled::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
        auto side = message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
        Reason = message->get<std::string>("reason");
    }
}

namespace QVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderAdd& instance){
        s << " --- [OrderAdd] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;

        if(instance.OrderType == ORDER_TYPE::LIMIT){
            s << "OrderType: LMT" << std::endl;
        }
        else
        {
            s << "OrderType: MKT" << std::endl;
        }

        if(instance.Side == SIDE::B){
            s << "Side: B" << std::endl;
        }
        else
        {
            s << "Side: S" << std::endl;
        }

        return s;
    }
}

namespace QVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderCancel& instance){
        s << " --- [OrderCancel] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        return s;
    }
}

namespace QVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderAccepted& instance){
        s << " --- [OrderAccepted] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}

namespace QVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderRejected& instance){
        s << " --- [OrderRejected] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "OrderId: " << instance.Reason << std::endl;
        return s;
    }
}

namespace QVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderExecuted& instance){
        s << " --- [OrderExecuted] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}

namespace QVT::SOE {
    std::ostream &operator<<(std::ostream& s, const OrderCanceled& instance){
        s << " --- [OrderCanceled] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        if(instance.Side == SIDE::B){
            s << "Side: B" << std::endl;
        }
        else
        {
            s << "Side: S" << std::endl;
        }
        return s;
    }
}
