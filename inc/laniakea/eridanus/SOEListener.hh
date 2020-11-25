#ifndef _SOELISTENER_HH
#define _SOELISTENER_HH
#include <list>
#include <laniakea/eridanus/SOE.hh>
#include <laniakea/virgo/macros.hh>
namespace SOE {
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
    };
}
#endif //_SOELISTENER_HH