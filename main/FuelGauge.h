class FuelGauge {
public:
    FuelGauge(bool _lock = false);
    // FuelGauge(TwoWire& i2c, bool _lock = false);
    ~FuelGauge();

    bool begin();

    float getVCell();
    float getSoC();
    float getNormalizedSoC();
    int getVersion();
    byte getCompensateValue();
    byte getAlertThreshold();
    int setAlertThreshold(byte threshold);
    bool getAlert();
    int clearAlert();
    int reset();
    int quickStart();
    int sleep();
    int wakeup();

    bool lock();
    bool unlock();
//
//private:
//    static constexpr system_tick_t FUELGAUGE_DEFAULT_TIMEOUT = 10; // In millisecond
//
//    int readConfigRegister(byte &MSB, byte &LSB);
//    int readRegister(byte startAddress, byte &MSB, byte &LSB);
//    int writeRegister(byte address, byte MSB, byte LSB);
//
//    TwoWire& i2c_;
//    bool lock_;
};