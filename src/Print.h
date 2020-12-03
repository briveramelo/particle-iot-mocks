#pragma once
#include <type_traits>
#include <stddef.h>
#include <string.h>
#include <stdint.h> // for uint8_t
//#include "system_tick_hal.h"
#include <climits>
#include "Printable.h"

const unsigned char DEC = 10;
const unsigned char HEX = 16;
const unsigned char OCT = 8;
const unsigned char BIN = 2;

class String;
class __FlashStringHelper;
class Printable;

class Print
{
private:
    int write_error;

    size_t printNumber(unsigned long, uint8_t);
    size_t printNumber(unsigned long long, uint8_t);
    size_t printFloat(double, uint8_t);
protected:
    void setWriteError(int err = 1) { write_error = err; }
    size_t printf_impl(bool newline, const char* format, ...);

public:
    Print() : write_error(0) {}
    virtual ~Print() {}

    int getWriteError() { return write_error; }
    void clearWriteError() { setWriteError(0); }

    virtual size_t write(uint8_t) = 0;
    size_t write(const char *str) {
        if (str == NULL) return 0;
        return write((const uint8_t *)str, strlen(str));
    }
    virtual size_t write(const uint8_t *buffer, size_t size);

    size_t print(const char[]);
    size_t print(char);
//    template <typename T, std::enable_if_t<std::is_integral<T>::value || std::is_convertible<T, unsigned long long>::value ||
//                                           std::is_convertible<T, long long>::value, int> = 0>
//    size_t print(T, int = DEC);
    size_t print(float, int = 2);
    size_t print(double, int = 2);
    size_t print(const Printable&);
    size_t print(const __FlashStringHelper*);

    size_t println(const char[]);
    size_t println(char);
//    template <typename T, std::enable_if_t<std::is_integral<T>::value || std::is_convertible<T, unsigned long long>::value ||
//                                           std::is_convertible<T, long long>::value, int> = 0>
//    size_t println(T b, int base = DEC) {
//        size_t n = print(b, base);
//        n += println();
//        return n;
//    }
    size_t println(float, int = 2);
    size_t println(double, int = 2);
    size_t println(const Printable&);
    size_t println(void);
    size_t println(const __FlashStringHelper*);

    template <typename... Args>
    inline size_t printf(const char* format, Args... args)
    {
        return this->printf_impl(false, format, args...);
    }

    template <typename... Args>
    inline size_t printlnf(const char* format, Args... args)
    {
        return this->printf_impl(true, format, args...);
    }

};

//template <typename T, std::enable_if_t<std::is_integral<T>::value || std::is_convertible<T, unsigned long long>::value ||
//                                       std::is_convertible<T, long long>::value, int>>
//size_t Print::print(T n, int base)
//{
//    if (base == 0) {
//        return write(n);
//    } else {
//        size_t t = 0;
//        using PrintNumberType = typename PrintNumberTypeSelector<T>::type;
//        PrintNumberType val;
//        if (n < 0 && base == 10) {
//            t = print('-');
//            val = -n;
//        } else {
//            val = n;
//        }
//        return printNumber(val, base) + t;
//    }
//}