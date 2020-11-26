#ifndef _SOE_HH
#define _SOE_HH
#include <nlohmann/json.hpp>
#include <grayvalley/core/fragment.hh>
#include <grayvalley/core/macros.hh>
#include <grayvalley/core/enums.hh>

namespace QVT::SOE {
    enum MESSAGE_TYPE: int {
        MESSAGE_TYPE_EMPTY,
        MESSAGE_TYPE_INVALID,
        MESSAGE_TYPE_ORDER_ADD,
        MESSAGE_TYPE_ORDER_CANCEL,
        MESSAGE_TYPE_ORDER_EXECUTED,
        MESSAGE_TYPE_ORDER_ACCEPTED,
        MESSAGE_TYPE_ORDER_REJECTED,
    };
}

namespace QVT::SOE {
    class Message {
    protected:
        nlohmann::json m_body;
    public:
        Message() = default;
        PREVENT_COPY(Message);
    public:
        void from(char* buffer, size_t len);
        MESSAGE_TYPE messageType();
        template<typename T>
        T get(const std::string& key);
        void print();
    };
}

namespace QVT::SOE {
    class InboundMessage {
    public:
        InboundMessage() = default;
        PREVENT_COPY(InboundMessage);
    public:
        virtual void get(Message* message) = 0;
    };
}

namespace QVT::SOE {
    class OutboundMessage {
    public:
        OutboundMessage() = default;
        PREVENT_COPY(OutboundMessage);
    };
}

namespace QVT::SOE {
    class OrderAdd: public InboundMessage, OutboundMessage {
    public:
        int OrderId;
        int Price;
        int Quantity;
        ORDER_TYPE OrderType;
        SIDE Side;
    public:
        OrderAdd() = default;
        PREVENT_COPY(OrderAdd);
    public:
        void get(Message* message) override;
        nlohmann::json to_json();
        friend std::ostream &operator<<(std::ostream& s, const OrderAdd& instance);
    };
}

namespace QVT::SOE {
    class OrderCancel: public OutboundMessage {
    public:
        int OrderId;
    public:
        OrderCancel() = default;
        PREVENT_COPY(OrderCancel);
    public:
        nlohmann::json to_json();
        friend std::ostream &operator<<(std::ostream& s, const OrderCancel& instance);
    };
}

namespace QVT::SOE {
    class OrderAccepted: public InboundMessage {
        int OrderId;
        int Price;
        int Quantity;
        ORDER_TYPE OrderType;
        SIDE Side;
    public:
        OrderAccepted() = default;
        PREVENT_COPY(OrderAccepted);
    public:
        void get(Message* message) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderAccepted& instance);
    };
}

namespace QVT::SOE {
    class OrderRejected: public InboundMessage {
        int OrderId;
        std::string Reason;
    public:
        OrderRejected() = default;
        PREVENT_COPY(OrderRejected);
    public:
        void get(Message* message) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderRejected& instance);
    };
}

namespace QVT::SOE {
    class OrderExecuted: public InboundMessage {
        int OrderId;
        int Price;
        int Quantity;
        ORDER_TYPE OrderType;
        SIDE Side;
    public:
        OrderExecuted() = default;
        PREVENT_COPY(OrderExecuted);
    public:
        void get(Message* message) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderExecuted& instance);
    };
}

#endif //SOE_HH
