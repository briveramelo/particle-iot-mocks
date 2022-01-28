#pragma once

class SerialStream : public Stream
{
public:
    void begin(int val){}
    void end(){}
    void print(int val){}
    void print(float val){}
    void print(const char* val){}
    void print(float val1, int val2){}
    void println(){}
    void println(int val){}
    void println(const char* val){}
    void println(uint8_t val1, const unsigned char charac){}
    void println(const char* val, int num){}
    void println(const char* val, const char* other){}

    size_t write(uint8_t){return 0;}
    int available(){return 0;}
    int read(){return 0;}
    int peek(){return 0;}
    void flush(){}
};

extern SerialStream Serial;