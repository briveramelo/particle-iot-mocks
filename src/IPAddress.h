#pragma once
#include <stdint.h>
#include <string.h>
#include "HALIPAddress.h"
//#include "Printable.h"

class IPAddress : public Printable {
private:

    HAL_IPAddress address;

    operator HAL_IPAddress* () {
        return &address;
    }

    void setVersion(uint8_t version);

public:
    // Constructors
    IPAddress(){}
    IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet){}
    IPAddress(uint32_t address){}
    IPAddress(const uint8_t* address){}
    IPAddress(const HAL_IPAddress& address){}

    ~IPAddress() {}

    /**
     * @return true when this address is not zero.
     */
    operator bool() const;

    // For some reason, without this non-const overload GCC struggles to pick right operator
    // for bool conversion of a non-const object
    operator bool() {
        return static_cast<const IPAddress*>(this)->operator bool();
    }

    // Overloaded cast operator to allow IPAddress objects to be used where a pointer
    // to a four-byte uint8_t array, uint32_t or another IPAddress object is expected.
    bool operator==(uint32_t address) const;
    bool operator==(const uint8_t* address) const;
    bool operator==(const IPAddress& address) const;

    // Overloaded index operator to allow getting and setting individual octets of the address
    uint8_t operator[](int index) const { return (((uint8_t*)(&address.ipv4))[3-index]); }
    uint8_t& operator[](int index) { return (((uint8_t*)(&address.ipv4))[3-index]); }

    void set_ipv4(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3){}


    // Overloaded copy operators to allow initialisation of IPAddress objects from other types
    /**
     *
     * @param address 4 bytes defining the IP address in network order
     * @return *this
     */
    IPAddress& operator=(const uint8_t* address);

    /**
     *
     * @param address   A 32-byte defining the 4 IPv4 octets, in host order.
     * @return
     */
    IPAddress& operator=(uint32_t address);

    operator const HAL_IPAddress& () const {
        return address;
    }

    operator const HAL_IPAddress* () const {
        return &address;
    }


    const HAL_IPAddress& raw() const {
        return address;
    }

    HAL_IPAddress& raw() {
        return address;
    }

    size_t printTo(Print& p) const;

    void clear() { memset(&address, 0, sizeof (address)); }

    String toString() const { return String(*this); }

    uint8_t version() const {
        return 4;
    }

    friend class TCPClient;
    friend class TCPServer;
    friend class UDP;
};

#if !HAL_USE_SOCKET_HAL_POSIX
extern const IPAddress INADDR_NONE;
#endif /* !HAL_USE_SOCKET_HAL_POSIX */