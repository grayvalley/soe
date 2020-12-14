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
#ifndef _SOEORDERENTRY_HH
#define _SOEORDERENTRY_HH

#include <grayvalley/soe/SOE.hh>

namespace GVT::SOE {
    class SOEOrderEntry {
    public:
        PREVENT_COPY(SOEOrderEntry);
    public:
        SOEOrderEntry() = default;
        ~SOEOrderEntry() = default;
    public:
        virtual void sendAddOrder(SOE::OrderNewMessage* p_order_add_msg) = 0;
        virtual void sendCancelOrder(SOE::OrderCancelMessage* p_order_cancel_msg) = 0;
    };
}
#endif //_SOEORDERENTRY_HH
