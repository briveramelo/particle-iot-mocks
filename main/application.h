// /Users/brandonrivera-melo/Documents/Repos/particle-device-os/wiring/inc/
#pragma once
#include <cstdint>
#include "typedefs.h"
#include "Vector.h"
#include "mockString.h"
#include "json.h"
#include "LoggingServices.h"
#include "Logging.h"
#include "Constants.h"
#include "IPAddress.h"
#include "Stream.h"
#include "TCPClient.h"
#include "UDP.h"
#include "I2C.h"
#include "Serial.h"
#include "Print.h"
#include "TimeMock.h"
#include "SPI.h"
#include "Ticks.h"
#include "PinMode.h"
#include "Wiring.h"
using spark::Vector;
using ::PinMode;

#define HAL_RNG_GetRandomNumber() 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0