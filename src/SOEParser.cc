#include <grayvalley/soe/SOE.hh>
#include <grayvalley/soe/SOEListener.hh>
#include <grayvalley/soe/SOEParser.hh>

namespace GVT::SOE {
    SOEParser::SOEParser(SOE::SOEListener* p_listener) {
        m_p_listener      = p_listener;
        m_p_message       = new Message();
        m_p_orderAccepted = new OrderAccepted();
        m_p_orderRejected = new OrderRejected();
        m_p_orderExecuted = new OrderExecuted();
        m_p_orderCanceled = new OrderCanceled();
    }
}

namespace GVT::SOE {
    SOEParser::~SOEParser() {
        delete m_p_message;
        delete m_p_orderAccepted;
        delete m_p_orderRejected;
        delete m_p_orderExecuted;
        delete m_p_orderCanceled;
    }
}

namespace GVT::SOE {
    void SOEParser::parse(char* buffer, size_t len) {
        m_p_message->from(buffer, len);
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
            case MESSAGE_TYPE_ORDER_CANCELED: {
                m_p_orderCanceled->get(m_p_message);
                m_p_listener->onOrderCanceled(m_p_orderCanceled);
                break;
            }
        }
    }
}