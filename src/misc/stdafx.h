#pragma once

#include <Arduino.h>
#include <Wire.h>

//Resources
#include "../bikeScreen/bikeScreen.h"

//EEPROM
#include "../eeprom_ops/eeprom_ops.h"

//Web
#include "../webServerStuff/webServerStuff.h"

//WiFi
#include <ESP8266WiFi.h>

//Time&Date
#include <ESP8266TimerInterrupt.h>
#include <ESP8266_ISR_Timer.h>
#include "timeWrapper/timeModule.h"

//counter
#include "bikeCounter/bikeCounter.h"

//SD
#include <SD.h>
//#include "../sd_ops/sd_ops.h"

//battery
#include "misc/battery.h"