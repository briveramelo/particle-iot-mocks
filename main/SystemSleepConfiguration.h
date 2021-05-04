#pragma once

#include "SystemSleepMode.h"
#include "PinMode.h"

class SystemSleepConfiguration
{
public:
    SystemSleepConfiguration mode(SystemSleepMode mode) {return *this;}
    SystemSleepConfiguration gpio(pin_t pin, InterruptMode mode) {return *this;}
    SystemSleepConfiguration duration(system_tick_t ms) {return *this;}
};