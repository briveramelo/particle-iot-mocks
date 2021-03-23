#pragma once

#include "SystemSleepConfiguration.h"

class System
{
public:
    uint32_t freeMemory();
    void sleep(SystemSleepConfiguration config);
};
extern System System;