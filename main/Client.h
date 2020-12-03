#pragma once
#include "application.h"

class Client {

public:
    Client(){}
    Client(uint8_t){}
    Client(uint8_t *, uint16_t){}

    uint8_t status(){return 0;}
    uint8_t connect(){return 0;}
    size_t write(uint8_t){return 0;}
    size_t write(const char *str){return 0;}
    size_t write(const uint8_t *buf, size_t size){return 0;}
    int available(){return 0;}
    int read(){return 0;}
    int read(uint8_t *buf, size_t size){return 0;}
    int peek(){return 0;}
    void flush(){}
    void stop(){}
    uint8_t connected(){return 0;}
    uint8_t operator==(int){return 0;}
    uint8_t operator!=(int){return 0;}
    operator bool();

    friend class Server;

private:
    static uint16_t _srcport;
    uint8_t _sock;
    uint8_t *_ip;
    uint16_t _port;
};