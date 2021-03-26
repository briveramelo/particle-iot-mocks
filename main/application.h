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
#include "InterruptMode.h"
#include "PMIC.h"
#include "SystemSleepMode.h"
#include "SystemSleepConfiguration.h"
#include "SystemPowerConfiguration.h"
#include "Print.h"
#include "TimeMock.h"
#include "SPI.h"
#include "System.h"
#include "FuelGauge.h"
#include "Ticks.h"
#include "PinMode.h"
#include "Particle.h"
#include "Wiring.h"
#include "WiFi.h"

#include "spark_wiring_string.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_usbserial.h"
#include "timer_hal.h"

using spark::Vector;
using ::PinMode;

#define HAL_RNG_GetRandomNumber() 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0
#define SEMI_AUTOMATIC 0
#define SYSTEM_MODE(mode)
#define D0 0
#define D1 0
#define BATT 0
#define PWR 0
#define CHG 0
#define WKP 17
