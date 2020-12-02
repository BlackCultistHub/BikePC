#pragma once

#include <Arduino.h>
#include "../eeprom_ops/eeprom_ops.h"
#include "../bikeCounter/bikeCounter.h"

class TimeModule
{
    public:
    TimeModule();

    void begin();
    bool isSet();

    void addMinute(bikeCounter& tripNumberTarget);
    bool setTime(uint8_t hours, uint8_t minutes);
    void setDate(uint8_t day, uint8_t month, uint16_t year);
    private:
    bool reset = false;
};

// class TimeModuleNTP : private NTPClient
// {
//     public:
//     //NTP Contructor
//     TimeModuleNTP(WiFiUDP& udp_, const char* NTPServer_ = "europe.pool.ntp.org", const uint32_t UTCOffsetInSeconds_ = 10800);

//     bool start();
//     void addMinute();
//     bool setTime(uint8_t hours, uint8_t minutes);
//     void setDate(uint8_t day, uint8_t month, uint16_t year);
//     bool updateTime();
// };