#include <laniakea/eridanus/SOEParser.hh>
#include <iostream>

namespace SOE {
    SOEParser::SOEParser(SOE::SOEListener* p_listener) {
        m_p_listener      = p_listener;
        m_p_message       = new Message();
        m_p_orderAccepted = new OrderAccepted();
        m_p_orderRejected = new OrderRejected();
        m_p_orderExecuted = new OrderExecuted();
    }
}

namespace SOE {
    SOEParser::~SOEParser() {
        delete m_p_message;
        delete m_p_orderAccepted;
        delete m_p_orderRejected;
        delete m_p_orderExecuted;
    }
}

namespace SOE {
    void SOEParser::parse(char* buffer, size_t len) {

       m_p_message->from(buffer, len);
       m_p_message->print();

       auto message_type = m_p_message->messageType();

       switch (message_type)
       {
           case MESSAGE_TYPE_EMPTY: {
               return;
           }
           case MESSAGE_TYPE_INVALID: {
               return;
           }
           case MESSAGE_TYPE_ORDER_ACCEPTED: {
               m_p_orderAccepted->get(m_p_message);
               m_p_listener->onOrderAccepted(m_p_orderAccepted);
               break;
           }
           case MESSAGE_TYPE_ORDER_REJECTED: {
               m_p_orderRejected->get(m_p_message);
               m_p_listener->onOrderRejected(m_p_orderRejected);
               break;
           }
           case MESSAGE_TYPE_ORDER_EXECUTED: {
               m_p_orderExecuted->get(m_p_message);
               m_p_listener->onOrderExecuted(m_p_orderExecuted);
               break;
           }
       }
    }
}