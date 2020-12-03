#pragma once
void setADCSampleTime(uint8_t ADC_SampleTime);
int32_t analogRead(uint16_t pin);

void pinMode(uint16_t pin, PinMode mode);
void pinMode(uint8_t pin, PinMode mode);
void pinMode(uint8_t pin, int mode);
PinMode getPinMode(uint16_t pin);
bool pinAvailable(uint16_t pin);
void digitalWrite(uint16_t pin, uint8_t value);
int32_t digitalRead(uint16_t pin);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

void serialReadLine(Stream *serialObj, char *dst, int max_len, system_tick_t timeout);

uint32_t pulseIn(pin_t pin, uint16_t value);

void analogWrite(pin_t pin, uint32_t value);
void analogWrite(pin_t pin, uint32_t value, uint32_t pwm_frequency);
uint8_t analogWriteResolution(pin_t pin, uint8_t value);
uint8_t analogWriteResolution(pin_t pin);
uint32_t analogWriteMaxFrequency(pin_t pin);
void setDACBufferred(pin_t pin, uint8_t state);

int map(int value, int fromStart, int fromEnd, int toStart, int toEnd);
double map(double value, double fromStart, double fromEnd, double toStart, double toEnd);