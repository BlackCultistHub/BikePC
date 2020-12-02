#pragma once

#include <Arduino.h>
#include "../eeprom_ops/eeprom_ops.h"
#include <SD.h>
#include <WString.h>
#include "../misc/Shared_params.h"

//------------------ [SD HIERARCHY] -------------
//root
//  |
//  | ODO.txt (number)
//  | Data (folder)
//      |
//      | dd.mm.yy DayOfTheWeek (folder)
//          |
//          | Trip-N (folder)
//              |
//              | Combined_CadPulSpd.csv
//              | Statistics.txt
//                  {
//                  Total time: xx h, xx m
//                  Total trip = x km
//                  Average speed = x km/h
//                  Average pulse = x bpm
//                  Average cadence = x rpm
//                  ODO = x km
//                  }
//              | Separated (folder)
//                  |
//                  | Cadence.csv
//                  | Pulse.csv
//                  | Speed.csv
//                  | Trip.csv
//                  | 
//  | Web (folder)
//      | charts.js
//      | 
//  | Logs (folder)
//      | dd.mm.yy.log
//      |

class bikeCounter
{
    public:
    bikeCounter();

    //Starter funcs
    bool initSD(const uint8_t cs_pin, String* errormsg = nullptr);
    void init();

    //check if need to reset (rpm, spd)
    bool elapsed();

    //***[Cadence - RPM]***
    void cad_impulse(); //impulse
    uint16_t getCadence();

    //***[TRIP]***
    void trip_start();
    void trip_stop();
    bool tripIsRunning();
    uint8_t getCurrentTripNumber();
    float getSessionTrip();

    //***[SPEED]***
    void spd_impulse();
    uint8_t getSpeed(); //real-time speed
    uint8_t getAverageSpeedPerTrip();
    uint8_t getAverageCadencePerTrip();
    uint8_t getAveragePulsePerTrip();
    
    void saveStats(); //eeprom

    bool saveStatsSD();

    //updated detection
    bool cadenceUpdated();
    bool speedUpdated();
    bool tripUpdated();
    bool avgSpdUpdated();
    bool odoUpdated();
    bool tripNumberUpdated();

    void updateRadius(uint16_t radius_mm);

    private:
    //down time
    uint32_t timer_downtime = 0;

    //RPM
    uint32_t lastIsrRpm = 500;
    uint16_t rpm = 0;
    bool rpm_updated = true;
    uint16_t rpm_summ = 0;
    uint16_t rpm_measures = 0;

    //trip
    uint64_t tripStartTimer;
    String tripStartDate;
    String tripStartDateDayOfTheWeek;
    float trip = 0;
    bool trip_updated = true;
    bool tripNumber_updated = true;
    uint16_t getAverageSpeed() //restart session
    {
        if (spd_measures == 0)
            return 0;
        else
            return spd_summ/spd_measures;
    }
    uint16_t getAverageCad() //restart session
    {
        if (rpm_measures == 0)
            return 0;
        else
            return rpm_summ/rpm_measures;
    }
    uint16_t getAveragePulse() //restart session
    {
        if (pulse_measures == 0)
            return 0;
        else
            return pulse_summ/pulse_measures;
    }

    //speed
    uint16_t radiusRAW;
    uint32_t lastIsrSpd = 500;
    uint8_t speed = 0;
    uint16_t radius = 0; //for fast access
    bool spd_updated = true;

    //average speed
    uint16_t spd_summ = 0;
    uint16_t spd_measures = 0;
    bool avgspd_updated = true;

    //odo
    float odo = 0; //for fast access
    bool odo_updated = true;

    //sd
    bool sdCardReady = false;
};
