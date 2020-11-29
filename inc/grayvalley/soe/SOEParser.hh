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
