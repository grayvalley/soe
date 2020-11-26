#ifndef _SOECLIENT_HH
#define _SOECLIENT_HH
#include <string>
#include <functional>
#include <grayvalley/core/epolling.hh>
#include <grayvalley/core/fragment.hh>
#include <grayvalley/soe/SOE.hh>
#include <grayvalley/soe/SOEParser.hh>
#include <grayvalley/soe/RFC6455.hh>
namespace QVT::SOE {
    class SOEClient : public Epollable {
    private:
        RFC6455::Session m_session;
        SOEParser* m_p_parser;
    public:
        SOEClient() = delete;
        PREVENT_COPY(SOEClient);
    public:
        explicit SOEClient(SOEParser* p_parser);
        ~SOEClient();
    private:
        void recv(Epoller* p_epoller) override;
        void read();
        void read_handshake_response();
        void read_websocket_frame();
    public:
        void connect(const RFC6455::Session& session);
        void open();
        void send(const FragmentView& fragment);
    };
}

#endif //_SOECLIENT_HH
