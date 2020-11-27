#ifndef _SOELISTENER_HH
#define _SOELISTENER_HH
#include <list>
#include <grayvalley/core/macros.hh>
#include <grayvalley/soe/SOE.hh>
namespace GVT::SOE {
    class SOEListener {
    public:
        PREVENT_COPY(SOEListener);
    public:
        SOEListener() = default;
        ~SOEListener() = default;
    public:
        virtual void onOrderAccepted(OrderAccepted* p_message) = 0;
        virtual void onOrderRejected(OrderRejected* p_message) = 0;
        virtual void onOrderExecuted(OrderExecuted* p_message) = 0;
        virtual void onOrderCanceled(OrderCanceled* p_message) = 0;
    };
}
#endif //_SOELISTENER_HH