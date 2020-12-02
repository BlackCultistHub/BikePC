#pragma once

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 512
#endif

#include <Arduino.h>
#include <EEPROM.h>
#include <WString.h>

//----------------- [EEPROM MAP] -------------
// [ADDRESSES]        "PURPOSE"         {SIZE}
//--------------------------------------------
// [0]             "wifi-mode-flag"      {1b}
// [1]                  "dt sd"          {1b}
// [2]               "begin-mode"        {1b}
// [3]              "sleep-settings"     {1b}   4bit-flag + 4bit-counter
// [4-23]             "wifi-ssid"        {20b}
// [24-43]          "wifi-password"      {20b}
// [44-63]         "wifi-client-ssid"    {20b}
// [64-83]         "wifi-client-paswd"   {20b}
// [84-85]          "wheel-radius"       {2b}
// [86]                 "free"           {1b}
// [87]              "trip-number"       {1b}
// [88]                 "day"            {1b}
// [89]                "month"           {1b}
// [90-91]              "year"           {2b}
// [92]             "day-of-the-week"    {1b} //0 for monday
// [93]                 "hours"          {1b}
// [94]                "minutes"         {1b}
// [95-98]             "trip-S"          {4b} //meters
// [99-100]          "trip-hours"        {2b}
// [101-102]        "trip-minutes"       {2b}
// [103]          "trip-average-speed"   {1b}
// [104-107]              "ODO"          {4b} //meters
// [108]         "trip-average-cadence"  {1b}
// [109]          "trip-average-pulse"   {1b}
// [110-119]       "trip-start-date"     {10b}
// [110-512]             "free"          {427b}
//--------------------------------------------

#define EMPTY_20ch "4848484848484848484848484848484848484848"
#define EMPTY_SSID EMPTY_20ch
#define EMPTY_PASWD EMPTY_20ch

//technical
void EEPROMwipe();
uint8_t EEPROMGetWiFiMode();
void EEPROMSetWiFiMode(bool mode);
uint8_t EEPROMGetBeginMode();
void EEPROMSetBeginMode(bool mode);
bool EEPROMGetSleepMode();
void EEPROMSetSleepMode(bool);
uint8_t EEPROMGetSleepCounter();
void EEPROMSetSleepCounter(uint8_t);

//wifi settings
String EEPROMGetSSID();
void EEPROMSetSSID(String ssid);
String EEPROMGetPassword();
void EEPROMSetPassword(String password);
String EEPROMGetClientSSID();
void EEPROMSetClientSSID(String ssid);
String EEPROMGetClientPassword();
void EEPROMSetClientPassword(String password);

//settings

uint16_t EEPROMGetWheelRadius();
void EEPROMSetWheelRadius(uint16_t wheel_radius);
uint32_t EEPROMGetdtSd();
bool EEPROMSetdtSd(uint32_t dtSd);

//stats
uint32_t EEPROMGetODO();
void EEPROMSetODO(uint32_t odo);
uint32_t EEPROMGetTrip();
void EEPROMSetTrip(uint32_t trip);
uint16_t EEPROMGetTripHours();
void EEPROMSetTripHours(uint16_t trip_hours);
uint16_t EEPROMGetTripMinutes();
void EEPROMSetTripMinutes(uint16_t trip_minutes);
uint8_t EEPROMGetTripSpd();
void EEPROMSetTripSpd(uint8_t trip_avgSpd);
uint8_t EEPROMGetTripNumber();
void EEPROMSetTripNumber(uint8_t trip_number);
uint8_t EEPROMGetTripCad();
void EEPROMSetTripCad(uint8_t trip_avgCad);
uint8_t EEPROMGetTripPulse();
void EEPROMSetTripPulse(uint8_t trip_avgPul);
void EEPROMSetTripStartDate(String date);
String EEPROMGetTripStartDate();

//time
uint8_t EEPROMGetDay();
void EEPROMSetDay(uint8_t day);
uint8_t EEPROMGetMonth();
void EEPROMSetMonth(uint8_t month);
uint16_t EEPROMGetYear();
void EEPROMSetYear(uint16_t year);
uint8_t EEPROMGetDayOfTheWeek();
void EEPROMSetDayOfTheWeek(uint8_t dayOTW);
uint8_t EEPROMGetHours();
void EEPROMSetHours(uint8_t hours);
uint8_t EEPROMGetMinutes();
void EEPROMSetMinutes(uint8_t minutes);
