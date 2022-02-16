#pragma once

#include "PinMode.h"
#include "InterruptMode.h"
#include <functional>

typedef std::function<void()> wiring_interrupt_handler_t;
bool attachInterrupt(uint16_t pin, wiring_interrupt_handler_t handler, InterruptMode mode, int8_t priority = -1, uint8_t subpriority = 0);
template <typename T>
bool attachInterrupt(uint16_t pin, void (T::*handler)(), T *instance, InterruptMode mode, int8_t priority = -1, uint8_t subpriority = 0);