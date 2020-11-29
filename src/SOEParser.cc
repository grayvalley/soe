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
#include <grayvalley/soe/SOE.hh>
#include <grayvalley/soe/SOEListener.hh>
#include <grayvalley/soe/SOEParser.hh>

namespace GVT::SOE {
    SOEParser::SOEParser(SOE::SOEListener* p_listener) {

        m_p_listener = p_listener;

        m_p_message = new Message();

        m_p_orderAcceptedMessage = new OrderAcceptedMessage();
        m_p_orderRejectedMessage = new OrderRejectedMessage();
        m_p_orderExecutedMessage = new OrderExecutedMessage();
        m_p_orderCanceledMessage = new OrderCanceledMessage();

    }
}

namespace GVT::SOE {
    SOEParser::~SOEParser() {
        delete m_p_message;
        delete m_p_orderAcceptedMessage;
        delete m_p_orderRejectedMessage;
        delete m_p_orderExecutedMessage;
        delete m_p_orderCanceledMessage;
    }
}

namespace GVT::SOE {
    void SOEParser::parse(char* buffer, size_t len) {
        m_p_message->from(buffer, len);
        auto type = m_p_message->type();
        switch (type)
        {
            case MESSAGE_TYPE_EMPTY: {
                return;
            }
            case MESSAGE_TYPE_INVALID: {
                return;
            }
            case MESSAGE_TYPE_ORDER_ACCEPTED: {
                m_p_orderAcceptedMessage->get(m_p_message);
                m_p_listener->onOrderAccepted(m_p_orderAcceptedMessage);
                break;
            }
            case MESSAGE_TYPE_ORDER_REJECTED: {
                m_p_orderRejectedMessage->get(m_p_message);
                m_p_listener->onOrderRejected(m_p_orderRejectedMessage);
                break;
            }
            case MESSAGE_TYPE_ORDER_EXECUTED: {
                m_p_orderExecutedMessage->get(m_p_message);
                m_p_listener->onOrderExecuted(m_p_orderExecutedMessage);
                break;
            }
            case MESSAGE_TYPE_ORDER_CANCELED: {
                m_p_orderCanceledMessage->get(m_p_message);
                m_p_listener->onOrderCanceled(m_p_orderCanceledMessage);
                break;
            }
        }
    }
}