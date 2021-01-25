#ifndef GVT_SOE_CLIENT_HH
#define GVT_SOE_CLIENT_HH
#include <string>
#include <functional>
#include <grayvalley/core/Engine.hh>
#include <grayvalley/core/IOrderClient.hh>
#include <grayvalley/core/RFC6455.hh>
#include <grayvalley/soe/SOE.hh>
#include <grayvalley/soe/SOEParser.hh>

namespace GVT::SOE {
    class SOEClient :
            public IOrderClient,
            public Epollable {
    private:
        RFC6455::Session m_session;
        SOEParser* m_p_parser;
    public:
        SOEClient() = delete;
        PREVENT_COPY(SOEClient);
    public:
        explicit SOEClient(SOEParser* p_parser);
        ~SOEClient() override;
    private:
        void recv(Epoller* p_epoller) override;
        void read();
        void read_handshake_response();
        void read_websocket_frame();
    public:
        void connect(const RFC6455::Session& session);
        void open();
        void send(const StringView& fragment);
    public:
        inline void sendOrder( std::string symbol,
                uint64_t price, uint64_t quantity, SIDE side, ORDER_TYPE order_type) override;

        void cancelOrder(std::string instrument, uint64_t order_id) override;
    };
}

#endif //GVT_SOE_CLIENT_HH
