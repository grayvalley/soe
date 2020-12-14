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
#ifndef _SOE_HH
#define _SOE_HH
#include <nlohmann/json.hpp>
#include <grayvalley/core/macros.hh>
#include <grayvalley/core/enums.hh>
#include <grayvalley/core/events.hh>
#include <grayvalley/core/messages.hh>

namespace GVT::SOE {
    enum MESSAGE_TYPE: int {
        MESSAGE_TYPE_EMPTY,
        MESSAGE_TYPE_INVALID,
        MESSAGE_TYPE_ORDER_ADD,
        MESSAGE_TYPE_ORDER_CANCEL,
        MESSAGE_TYPE_ORDER_CANCELED,
        MESSAGE_TYPE_ORDER_EXECUTED,
        MESSAGE_TYPE_ORDER_ACCEPTED,
        MESSAGE_TYPE_ORDER_REJECTED,
    };
}

namespace GVT::SOE {

    class Message: public IMessage {

    public:

        Message() = default;

        PREVENT_COPY(Message);

    public:

        /**
         * Populates the body of the message from a buffer
         *
         * @param buffer: pointer to the beginning of a buffer
         * @param len: length of the message
         */
        void from(char* buffer, size_t len) override;

        /**
         * Return type id of the message
         *
         * @return: integer id
         */
        [[nodiscard]] int type() const override;

    public:

        template<typename T>
        T get(std::string key);

    protected:

        nlohmann::json m_body;

    };
}


/**
 *
 */
namespace GVT::SOE {

    class OutboundJSONMessage: public IOutboundMessage {

    public:

        OutboundJSONMessage() = default;

        PREVENT_COPY(OutboundJSONMessage);

    public:

        /**
         * Converts message into a json object
         *
         * @return: json object
         */
        virtual nlohmann::json to_json() = 0;

    };
}


namespace GVT::SOE {
    class OrderNewMessage: public IOrderNewMessage, public OutboundJSONMessage {
    public:
        OrderNewMessage() = default;
        PREVENT_COPY(OrderNewMessage);
    public:
        nlohmann::json to_json() override;
        friend std::ostream &operator<<(std::ostream& s, const OrderNewMessage& instance);
    };
}

namespace GVT::SOE {
    class OrderCancelMessage: public IOrderCancelMessage, public OutboundJSONMessage {
    public:
        OrderCancelMessage() = default;
        PREVENT_COPY(OrderCancelMessage);
    public:
        nlohmann::json to_json() override;
        friend std::ostream &operator<<(std::ostream& s, const OrderCancelMessage& instance);
    };
}

namespace GVT::SOE {
    class OrderAcceptedMessage: public IInboundMessage, public IOrderAcceptedMessage {

    public:
        OrderAcceptedMessage() = default;
        PREVENT_COPY(OrderAcceptedMessage);
    public:
        void get(IMessage* message) override;
        void put(IOrderAcceptedEvent* p_event) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderAcceptedMessage& instance);
    };
}

namespace GVT::SOE {
    class OrderRejectedMessage: public IInboundMessage, public IOrderRejectedMessage {
    public:
        OrderRejectedMessage() = default;
        PREVENT_COPY(OrderRejectedMessage);
    public:
        void get(IMessage* message) override;
        void put(IOrderRejectedEvent* p_event) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderRejectedMessage& instance);
    };
}

namespace GVT::SOE {
    class OrderExecutedMessage: public IInboundMessage, public IOrderExecutedMessage {
    public:
        OrderExecutedMessage() = default;
        PREVENT_COPY(OrderExecutedMessage);
    public:
        void get(IMessage* message) override;
        void put(IOrderExecutedEvent* p_event) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderExecutedMessage& instance);
    };
}

namespace GVT::SOE {
    class OrderCanceledMessage: public IInboundMessage, public IOrderCanceledMessage {
        int OrderId;
        int Price;
        int Quantity;
        SIDE Side;
        std::string Reason;
    public:
        OrderCanceledMessage() = default;
        PREVENT_COPY(OrderCanceledMessage);
    public:
        void get(IMessage* message) override;
        void put(IOrderCanceledEvent* p_event) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderCanceledMessage& instance);
    };
}

#endif //SOE_HH
