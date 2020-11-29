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
        virtual void sendAddOrder(SOE::OrderAddMessage* p_order_add_msg) = 0;
        virtual void sendCancelOrder(SOE::OrderCancelMessage* p_order_cancel_msg) = 0;
    };
}
#endif //_SOEORDERENTRY_HH
