#pragma once
class SPIClass;

typedef enum HAL_SPI_Interface {
    HAL_SPI_INTERFACE1 = 0,    //maps to SPI1 (pins: A3, A4, A5)
    HAL_SPI_INTERFACE2 = 1     //maps to SPI3 (pins: D4, D3, D2)
#if PLATFORM_ID == 10 // Electron
    ,HAL_SPI_INTERFACE3 = 2     //maps to SPI3 (pins: C3, C2, C1)
#endif
    ,TOTAL_SPI
} HAL_SPI_Interface;

typedef enum
{
    SPI_MODE_MASTER = 0, SPI_MODE_SLAVE = 1
} SPI_Mode;

typedef void (*HAL_SPI_DMA_UserCallback)(void);
typedef void (*HAL_SPI_Select_UserCallback)(uint8_t);

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
#define SPI_MODE0               0x00
#define SPI_MODE1               0x01
#define SPI_MODE2               0x02
#define SPI_MODE3               0x03

#define SPI_CLOCK_DIV2          0x00
#define SPI_CLOCK_DIV4          0x08
#define SPI_CLOCK_DIV8          0x10
#define SPI_CLOCK_DIV16         0x18
#define SPI_CLOCK_DIV32         0x20
#define SPI_CLOCK_DIV64         0x28
#define SPI_CLOCK_DIV128        0x30
#define SPI_CLOCK_DIV256        0x38

#define SPI_DEFAULT_SS          ((uint16_t)(-1))

#define LSBFIRST                0
#define MSBFIRST                1

typedef void (*wiring_spi_dma_transfercomplete_callback_t)(void);
typedef void (*wiring_spi_select_callback_t)(uint8_t);

enum FrequencyScale
{
    HZ = 1,
    KHZ = HZ*1000,
    MHZ = KHZ*1000,
    SPI_CLK_SYSTEM = 0,         // represents the system clock speed
    SPI_CLK_ARDUINO = 16*MHZ,
    SPI_CLK_PHOTON = 60*MHZ
};

namespace particle {
    class __SPISettings : public Printable {
    public:
        __SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
                : default_{false},
                  clock_{clock},
                  bitOrder_{bitOrder},
                  dataMode_{dataMode}
        {
        }

        __SPISettings()
        {
        }

        bool operator==(const __SPISettings& other) const
        {
            if (default_ && other.default_)
                return true;

            if (default_ == other.default_ &&
                clock_ == other.clock_ &&
                bitOrder_ == other.bitOrder_ &&
                dataMode_ == other.dataMode_)
            {
                return true;
            }

            return false;
        }

        bool operator>=(const __SPISettings& other) const
        {
            if (default_ && other.default_)
                return true;

            if (default_ == other.default_ &&
                clock_ >= other.clock_ &&
                bitOrder_ == other.bitOrder_ &&
                dataMode_ == other.dataMode_)
            {
                return true;
            }

            return false;
        }

        bool operator<=(const __SPISettings& other) const
        {
            if (default_ && other.default_)
                return true;

            if (default_ == other.default_ &&
                clock_ <= other.clock_ &&
                bitOrder_ == other.bitOrder_ &&
                dataMode_ == other.dataMode_)
            {
                return true;
            }

            return false;
        }

        bool operator!=(const __SPISettings& other) const
        {
            return !(other == *this);
        }

        virtual size_t printTo(Print& p);

        uint32_t getClock() const {
            return clock_;
        }

    private:
        friend class ::SPIClass;
        bool default_ = true;
        uint32_t clock_ = 0;
        uint8_t bitOrder_ = 0;
        uint8_t dataMode_ = 0;
    };
}

class SPIClass {
public:
    SPIClass(HAL_SPI_Interface spi);
    ~SPIClass() = default;
    SPIClass(const SPIClass&) = delete;
    SPIClass& operator=(const SPIClass&) = delete;
    void begin();
    void begin(uint16_t);
//    void begin(SPI_Mode mode, uint16_t ss_pin = SPI_DEFAULT_SS);
    void end();
    void setBitOrder(uint8_t);
    void setDataMode(uint8_t);
    static void usingInterrupt(uint8_t) {};
    int32_t beginTransaction();
    int32_t beginTransaction(const particle::__SPISettings& settings);
    void endTransaction();
    void setClockDividerReference(unsigned value, unsigned scale=HZ);
    void setClockDivider(uint8_t divider);
    unsigned setClockSpeed(unsigned value, unsigned scale=HZ);
    static void computeClockDivider(unsigned reference, unsigned targetSpeed, uint8_t& divider, unsigned& clock);
    byte transfer(byte _data);
    void transfer(void* tx_buffer, void* rx_buffer, size_t length, wiring_spi_dma_transfercomplete_callback_t user_callback);
    void attachInterrupt();
    void detachInterrupt();
    bool isEnabled(void);
    void onSelect(wiring_spi_select_callback_t user_callback);
    void transferCancel();
    int32_t available();
    bool trylock();
    int lock();
    void unlock();
};

extern SPIClass SPI;