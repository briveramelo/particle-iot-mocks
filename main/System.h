#pragma once

#include "SystemSleepConfiguration.h"
#include "SystemPowerConfiguration.h"

class System
{
public:
    uint32_t freeMemory(){return 0;}
    void sleep(SystemSleepConfiguration config){}
    int setPowerConfiguration(SystemPowerConfiguration& conf){}
    int powerSource(){return 0;}
    int batteryState(){return 0;}
    float batteryCharge(){return 0;}
};
extern System System;