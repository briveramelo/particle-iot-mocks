#pragma once
typedef uint16_t pin_t;

typedef enum PinMode {
    INPUT,
    OUTPUT,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    AF_OUTPUT_PUSHPULL, // Used internally for Alternate Function Output PushPull(TIM, UART, SPI etc)
    AF_OUTPUT_DRAIN,    // Used internally for Alternate Function Output Drain(I2C etc). External pullup resistors required.
    AN_INPUT,           // Used internally for ADC Input
    AN_OUTPUT,          // Used internally for DAC Output,
    OUTPUT_OPEN_DRAIN = AF_OUTPUT_DRAIN,
    PIN_MODE_NONE = 0xFF
} PinMode;