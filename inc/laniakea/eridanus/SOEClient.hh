#ifndef SOECLIENT_HH
#define SOECLIENT_HH
#include <string>
#include <functional>
#include <laniakea/virgo/epolling.hh>
#include <laniakea/virgo/fragment.hh>
#include <laniakea/eridanus/SOE.hh>
#include <laniakea/eridanus/SOEParser.hh>
#include <laniakea/eridanus/RFC6455.hh>
namespace SOE {
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
#endif //SOECLIENT_HH
