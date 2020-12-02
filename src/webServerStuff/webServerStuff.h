#pragma once

#include <ESP8266WebServer.h>
#include "pages/pages.h"
#include "../eeprom_ops/eeprom_ops.h"
#include "../misc/Shared_params.h"
#include "../misc/battery.h"


//server obj
extern ESP8266WebServer server;

//vars


//handlers
void handler404();
void handlerIndex();
void handlerData();
void handlerChange();
void handlerSwitch();
void handlerHardReset();
void handlerStats();
void handlerInfo();
void handlerGetSettings();

//pages
String getHeader();
String getMainPage();
String getStatsPage();
String getSettingsPage();

//funcs
uint8_t getDayOfTheYear(int8_t day, uint8_t month, uint16_t year);