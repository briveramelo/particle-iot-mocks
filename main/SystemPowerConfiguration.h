#pragma once

#include "enumflags.h"
using particle::EnumFlags;

enum class SystemPowerFeature {
    NONE = 0,
    PMIC_DETECTION = 1,
    USE_VIN_SETTINGS_WITH_USB_HOST = 2,
    DISABLE = 3,
//    DISABLE_CHARGING = 4
};

class SystemPowerConfiguration {
public:

    SystemPowerConfiguration(){}
//            : conf_{} {
//        conf_.size = sizeof(conf_);
//    }

    SystemPowerConfiguration(SystemPowerConfiguration&&) = default;
//    SystemPowerConfiguration(const hal_power_config& conf) : conf_(conf) {}
    SystemPowerConfiguration& operator=(SystemPowerConfiguration&&) = default;
    SystemPowerConfiguration& powerSourceMinVoltage(uint16_t voltage);
//    uint16_t powerSourceMinVoltage() const;
    SystemPowerConfiguration& powerSourceMaxCurrent(uint16_t current);
//    uint16_t powerSourceMaxCurrent() const;
    SystemPowerConfiguration& batteryChargeVoltage(uint16_t voltage);
//    uint16_t batteryChargeVoltage() const;
    SystemPowerConfiguration& batteryChargeCurrent(uint16_t current);
//    uint16_t batteryChargeCurrent() const;
    SystemPowerConfiguration& feature(EnumFlags<SystemPowerFeature> f);
    SystemPowerConfiguration& clearFeature(EnumFlags<SystemPowerFeature> f);
//    bool isFeatureSet(EnumFlags<SystemPowerFeature> f) const;
//    const hal_power_config* config() const;
};