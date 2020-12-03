#pragma once
#include <chrono>

system_tick_t millis(void);
system_tick_t millis(){ return 0; }
unsigned long micros(void);
void delay(unsigned long ms){}
inline void delayMicroseconds(unsigned int us);
static inline void delay(std::chrono::milliseconds ms);
static inline void delayMicroseconds(std::chrono::microseconds us);