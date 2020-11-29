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
#ifndef _SOEPARSER_HH
#define _SOEPARSER_HH

#include <grayvalley/soe/SOE.hh>
#include <grayvalley/soe/SOEListener.hh>

namespace GVT::SOE {
    class SOEParser
    {
    private:

        SOEListener* m_p_listener = nullptr;

        Message* m_p_message = nullptr;

        OrderAcceptedMessage* m_p_orderAcceptedMessage = nullptr;
        OrderRejectedMessage* m_p_orderRejectedMessage = nullptr;
        OrderExecutedMessage* m_p_orderExecutedMessage = nullptr;
        OrderCanceledMessage* m_p_orderCanceledMessage = nullptr;

    public:
        SOEParser() = delete;
        explicit SOEParser(SOEListener* p_listener);
        SOEParser(SOEParser& other) = delete;
        SOEParser& operator=(SOEParser& other) = delete;
        ~SOEParser();
    public:
        void parse(char* buffer, size_t len);
    };
}
#endif //_SOEPARSER_HH
