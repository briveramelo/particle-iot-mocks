#pragma once

enum class SystemSleepMode: uint8_t {
    NONE            = 0,
    STOP            = 1,
    ULTRA_LOW_POWER = 2,
    HIBERNATE       = 3,
};