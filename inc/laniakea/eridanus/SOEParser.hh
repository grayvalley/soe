#ifndef SOEPARSER_HH
#define SOEPARSER_HH
#include <laniakea/eridanus/SOE.hh>
#include <laniakea/eridanus/SOEListener.hh>
namespace SOE {
    class SOEParser
    {
    private:
        Message*       m_p_message       = nullptr;
        OrderAccepted* m_p_orderAccepted = nullptr;
        OrderRejected* m_p_orderRejected = nullptr;
        OrderExecuted* m_p_orderExecuted = nullptr;
        SOEListener*   m_p_listener      = nullptr;
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
#endif //SOEPARSER_HH
