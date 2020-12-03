#pragma once

#include <memory>
#include "Client.h"
//#include "IPAddress.h"
//#include "Print.h"

#define TCPCLIENT_BUF_MAX_SIZE  128

class TCPClient : public Client {

public:
    TCPClient(){}
    TCPClient(sock_handle_t sock){}
    ~TCPClient() {};

    uint8_t status(){return 0;}
    int connect(IPAddress ip, uint16_t port, network_interface_t=0){return 0;}
    int connect(const char *host, uint16_t port, network_interface_t=0){return 0;}
    size_t write(uint8_t){return 0;}
    size_t write(const uint8_t *buffer, size_t size){return 0;}
    size_t write(uint8_t, system_tick_t timeout){return 0;}
    size_t write(const uint8_t *buffer, size_t size, system_tick_t timeout){return 0;}
    int available(){return 0;}
    int read(){return 0;}
    int read(uint8_t *buffer, size_t size){return 0;}
    int peek(){return 0;}
    void flush(){}
    void flush_buffer();
    void stop(){}
    uint8_t connected(){return 0;}
    operator bool();

    IPAddress remoteIP(){return d_->remoteIP;}

    friend class TCPServer;

protected:
    inline sock_handle_t sock_handle() { return d_->sock; }

private:
    struct Data {
        sock_handle_t sock;
        uint8_t buffer[TCPCLIENT_BUF_MAX_SIZE];
        uint16_t offset;
        uint16_t total;
        IPAddress remoteIP;

        explicit Data(sock_handle_t sock){}
        ~Data(){}
    };

    std::shared_ptr<Data> d_;

    int bufferCount(){return 0;}
};