#pragma once

#include "typedefs.h"

//Default PMIC (BQ24195) I2C address
#define PMIC_ADDRESS                            0x6B

// Register address definitions
#define INPUT_SOURCE_REGISTER                   0x00
#define POWERON_CONFIG_REGISTER                 0x01
#define CHARGE_CURRENT_CONTROL_REGISTER         0x02
#define PRECHARGE_CURRENT_CONTROL_REGISTER      0x03
#define CHARGE_VOLTAGE_CONTROL_REGISTER         0x04
#define CHARGE_TIMER_CONTROL_REGISTER           0x05
#define THERMAL_REG_CONTROL_REGISTER            0x06
#define MISC_CONTROL_REGISTER                   0x07
#define SYSTEM_STATUS_REGISTER                  0x08
#define FAULT_REGISTER                          0x09
#define PMIC_VERSION_REGISTER                   0x0A

class PMIC {

public:
    PMIC(bool _lock=false);
    ~PMIC();
    bool begin();
    byte getVersion();
    byte getSystemStatus();
    byte getFault();

    // Input source control register
    byte readInputSourceRegister(void);
    bool enableBuck(void);
    bool disableBuck(void);
    bool isBuckEnabled();
    bool setInputCurrentLimit(uint16_t current);
    uint16_t getInputCurrentLimit(void);
    bool setInputVoltageLimit(uint16_t voltage);
    uint16_t getInputVoltageLimit(void);

    // Power ON configuration register
    bool enableCharging(void);
    bool disableCharging(void);
    bool isChargingEnabled(void);
    bool enableOTG(void);
    bool disableOTG(void);
    bool resetWatchdog(void);
    bool setMinimumSystemVoltage(uint16_t voltage);
    uint16_t getMinimumSystemVoltage();
    byte readPowerONRegister(void);
    void reset();

    // Charge current control register
    bool setChargeCurrent(bool bit7, bool bit6, bool bit5, bool bit4, bool bit3, bool bit2);
    bool setChargeCurrent(uint16_t current);
    byte getChargeCurrent(void);
    uint16_t getChargeCurrentValue();

    //PreCharge/ Termination Current Control Register
    bool setPreChargeCurrent();
    byte getPreChargeCurrent();
    bool setTermChargeCurrent();
    byte getTermChargeCurrent();

    //Charge Voltage Control Register
    bool setChargeVoltage(uint16_t voltage);
    byte getChargeVoltage();
    uint16_t getChargeVoltageValue();

    //CHARGE_TIMER_CONTROL_REGISTER
    byte readChargeTermRegister();
    bool disableWatchdog(void);
    bool setWatchdog(byte time);
    bool enableSafetyTimer();
    bool disableSafetyTimer();


    //Thermal Regulation Control Register
    bool setThermalRegulation();
    byte getThermalRegulation();

    // Recharge threshold
    uint16_t getRechargeThreshold();
    bool setRechargeThreshold(uint16_t voltage);

    //Misc Operation Control Register
    byte readOpControlRegister();
    bool enableDPDM(void);
    bool disableDPDM(void);
    bool enableBATFET(void);
    bool disableBATFET(void);
    bool isBATFETEnabled();
    bool safetyTimer(); //slow/ normal
    bool isInDPDM();

    bool enableChargeFaultINT();
    bool disableChargeFaultINT();
    bool enableBatFaultINT();
    bool disableBatFaultINT();

    //System Status Register
    byte getVbusStat();
    byte getChargingStat();
    bool getDPMStat();
    bool isPowerGood(void);
    bool isHot(void);
    bool getVsysStat();

    //Fault Register
    bool isWatchdogFault();
    byte getChargeFault();
    bool isBatFault();
    byte getNTCFault();


    bool lock();
    bool unlock();


};