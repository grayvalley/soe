#ifndef RFC6455_HH
#define RFC6455_HH
#include <string>
#include <random>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <utility>
#include <regex>
#include <grayvalley/soe/sha1/sha1.hh>
#include <grayvalley/soe/base64/base64.h>

#define OPCODE_CONTINUE 0x0
#define OPCODE_TEXT 0x1
#define OPCODE_BINARY 0x2
#define OPCODE_CLOSE 0x8
#define OPCODE_PING 0x9
#define OPCODE_PONG 0xA

#define _FIN 0x01
#define _OPCODE 0x0f
#define _MASK 0x01
#define _PAYLOAD_LEN ~0x80

static
std::string
create_rfc6455_secret_key()
{
    std::independent_bits_engine<std::mt19937, 8, std::uint8_t> generator;
    std::vector<unsigned char> data(16);
    std::generate(begin(data), end(data), std::ref(generator));
    std::string raw_sec_key{data.begin(), data.end()};
    std::string sec_key;
    Base64::Encode(raw_sec_key, &sec_key);
    return sec_key;
}

namespace RFC6455 {
    enum state: int {
        NONE,
        CONNECTING,
        CONNECTED,
        ERROR
    };
}

namespace RFC6455 {
    class Session {
    public:
        std::string ID;
        std::string Scheme;
        std::string Host;
        std::string Path;
        int Port  = 0;
        state State = NONE;
    public:
        Session(){
            ID = create_rfc6455_secret_key();
        }
    public:

        std::string create_handshake() {
            std::string crlf = "\r\n";
            std::stringstream handshake;
            handshake << "GET " << Scheme
                      << "://"
                      << Host << ":" << std::to_string(Port)
                      << "/"
                      << Path
                      << " HTTP/1.1" << crlf;
            handshake << "Host: "
                      << Host << ":"
                      << std::to_string(Port)
                      << crlf;
            handshake << "Upgrade: websocket"
                      << crlf;
            handshake << "Connection: Upgrade"
                      << crlf;
            handshake << "Sec-WebSocket-Key: "
                      << ID
                      << crlf;
            handshake << "Sec-WebSocket-Version: 13"
                      << crlf;
            handshake << crlf;
            std::string hs = handshake.str();
            return hs;
        }

        void validate(const std::string& handshake_response){
            auto resp = parse_handshake(handshake_response);
            auto expected = get_expected_key();
            std::string received_key = std::string(resp["Sec-WebSocket-Accept"]);
            if(received_key.find(expected) != std::string::npos){
                State = RFC6455::CONNECTED;
            } else {
                State = RFC6455::ERROR;
            }

        }

    private:

        std::map<std::string, std::string> parse_handshake(const std::string& response){
            auto ss = std::stringstream{response};
            std::map<std::string, std::string> result;
            for (std::string line; std::getline(ss, line, '\n');) {
                std::string::size_type pos = 0;
                while ((pos = line.find ("\r",pos) ) != std::string::npos) {
                    line.erase ( pos, 2 );
                }
                auto index = line.find(':');
                std::pair<std::string, std::string> keyVal;
                if (index != std::string::npos) {
                    std::string key = line.substr(0,index);
                    std::string val = line.substr(index+1);
                    keyVal = std::make_pair(key, val);
                    while (!keyVal.second.empty() && keyVal.second.front() == ' ') {
                        keyVal.second.erase(0,1);
                    }
                    result.insert(keyVal);
                }
            }
            return result;
        }

        std::string get_expected_key(){
            std::string accept_key = ID;
            accept_key += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
            char base64[SHA1_BASE64_SIZE];
            sha1(accept_key.c_str()).finalize().print_base64(base64);
            std::string expected_key = std::string(base64);
            return expected_key;
        }

    };
}


#endif //TEST_RFC6455_HH
