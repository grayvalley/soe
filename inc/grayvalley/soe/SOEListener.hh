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
#ifndef _SOELISTENER_HH
#define _SOELISTENER_HH
#include <list>
#include <grayvalley/core/Macros.hh>
#include <grayvalley/soe/SOE.hh>
namespace GVT::SOE {
    class SOEListener {
    public:
        PREVENT_COPY(SOEListener);
    public:
         SOEListener() = default;
        ~SOEListener() = default;
    public:
        virtual void onOrderAccepted(OrderAcceptedMessage* p_message) = 0;
        virtual void onOrderRejected(OrderRejectedMessage* p_message) = 0;
        virtual void onOrderExecuted(OrderExecutedMessage* p_message) = 0;
        virtual void onOrderCanceled(OrderCanceledMessage* p_message) = 0;
    };
}
#endif //_SOELISTENER_HH