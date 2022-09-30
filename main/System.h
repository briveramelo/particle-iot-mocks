#pragma once

#include "SystemSleepConfiguration.h"
#include "SystemPowerConfiguration.h"

#define FEATURE_RETAINED_MEMORY 0
class System
{
public:
    uint32_t freeMemory(){return 0;}
    void sleep(SystemSleepConfiguration config){}
    int setPowerConfiguration(SystemPowerConfiguration& conf){return 0;}
    int powerSource(){return 0;}
    int batteryState(){return 0;}
    float batteryCharge(){return 0;}
    void enableFeature(int feature){};
    void disableUpdates(){};
    void enableUpdates(){};
    bool updatesEnabled(){return false;};
    void reset(){};
};
extern System System;