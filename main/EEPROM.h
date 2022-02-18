#pragma once
#include "typedefs.h"

class EEPROM
{
public:
    int length();
    template <typename T> const T &put( int idx, const T &t );
    template <typename T> T &get( int idx, T &t );
    void write(int addr, byte val);
    void clear();
};
extern EEPROM EEPROM;