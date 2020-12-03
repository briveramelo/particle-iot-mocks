#include <chrono>
#define HAL_I2C_DEFAULT_TIMEOUT_MS (100)
typedef enum
{
    I2C_MODE_MASTER = 0, I2C_MODE_SLAVE = 1
} I2C_Mode;

typedef enum HAL_I2C_Interface {
    HAL_I2C_INTERFACE1 = 0,
    HAL_I2C_INTERFACE2 = 1,
    HAL_I2C_INTERFACE3 = 2
} HAL_I2C_Interface;

/*! I2c Config Structure Version */
typedef enum HAL_I2C_Config_Version {
    HAL_I2C_CONFIG_VERSION_1 = 0,
    HAL_I2C_CONFIG_VERSION_LATEST = HAL_I2C_CONFIG_VERSION_1,
} HAL_I2C_Config_Version;

typedef struct HAL_I2C_Config {
    uint16_t size;
    uint16_t version;
    uint8_t* rx_buffer;
    uint32_t rx_buffer_size;
    uint8_t* tx_buffer;
    uint32_t tx_buffer_size;
} HAL_I2C_Config;

typedef enum HAL_I2C_Transmission_Flag {
    HAL_I2C_TRANSMISSION_FLAG_NONE = 0x00,
    HAL_I2C_TRANSMISSION_FLAG_STOP = 0x01
} HAL_I2C_Transmission_Flag;

typedef struct HAL_I2C_Transmission_Config {
    uint16_t size;
    uint16_t version;

    uint8_t address;
    uint8_t reserved[3];
    uint32_t quantity;
    system_tick_t timeout_ms;
    uint32_t flags;
} HAL_I2C_Transmission_Config;

class WireTransmission {
public:
    WireTransmission(uint8_t address)
            : address_{address},
              size_{0},
              stop_{true},
              timeout_{HAL_I2C_DEFAULT_TIMEOUT_MS} {
    }

    WireTransmission() = delete;

    WireTransmission& quantity(size_t size) {
        size_ = size;
        return *this;
    }

    WireTransmission& timeout(system_tick_t ms) {
        timeout_ = ms;
        return *this;
    }

    WireTransmission& timeout(std::chrono::milliseconds ms) {
        return timeout((system_tick_t)ms.count());
    }

    WireTransmission& stop(bool stop) {
        stop_ = stop;
        return *this;
    }

    HAL_I2C_Transmission_Config halConfig() const {
        HAL_I2C_Transmission_Config conf = {
                .size = sizeof(HAL_I2C_Transmission_Config),
                .version = 0,
                .address = address_,
                .reserved = {0},
                .quantity = (uint32_t)size_,
                .timeout_ms = timeout_,
                .flags = (uint32_t)(stop_ ? HAL_I2C_TRANSMISSION_FLAG_STOP : 0)
        };
        return conf;
    }

private:
    uint8_t address_;
    size_t size_;
    bool stop_;
    system_tick_t timeout_;
};

class TwoWire : public Stream
{
public:
    TwoWire(HAL_I2C_Interface i2c, const HAL_I2C_Config& config);
    virtual ~TwoWire() {};
    inline void setClock(uint32_t speed) {
        setSpeed(speed);
    }
    void setSpeed(uint32_t);
    void enableDMAMode(bool);
    void stretchClock(bool);
    void begin();
    void begin(uint8_t);
    void begin(int);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    void beginTransmission(const WireTransmission& transfer);
    void end();
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    size_t requestFrom(uint8_t, size_t);
    size_t requestFrom(uint8_t, size_t, uint8_t);
    size_t requestFrom(const WireTransmission& transfer);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive(void (*)(int));
    void onRequest(void (*)(void));

    bool lock();
    bool unlock();

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;

    bool isEnabled(void);

    /**
     * Attempts to reset this I2C bus.
     */
    void reset();
};

HAL_I2C_Config __attribute__((weak)) acquireWireBuffer();

#define Wire __fetch_global_Wire()
TwoWire& __fetch_global_Wire();