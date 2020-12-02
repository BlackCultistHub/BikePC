#include "timeModule.h"

TimeModule::TimeModule() 
{
    
}

void TimeModule::begin()
{
    //checking date
    if (EEPROMGetYear() == 0)
    {
        EEPROMSetYear(2001);
        EEPROMSetMonth(1);
        EEPROMSetDay(1);
        EEPROMSetDayOfTheWeek(0); //0 is Monday
        reset = true;
    }
    else if (EEPROMGetYear() == 2001)
    {
        reset = true;
    }
}

bool TimeModule::isSet()
{
    return !reset;
}

bool TimeModule::setTime(uint8_t hours, uint8_t minutes)
    {
        if (hours < 24)
            EEPROMSetHours(hours);
        else
            return false;
        if (minutes < 60)
            EEPROMSetMinutes(minutes);
        else
            return false;
        return true;
    }

void TimeModule::addMinute(bikeCounter& tripNumberTarget)
{
    auto mins = EEPROMGetMinutes();
    if (mins+1 < 60)
        EEPROMSetMinutes(mins+1);
    else //New hour
    {
        mins = 0;
        auto hours = EEPROMGetHours();
        if (hours+1 < 24)
        {
            EEPROMSetMinutes(mins);
            EEPROMSetHours(hours+1);
        }
        else //New day
        {
            //check to reset trip number
            if (!tripNumberTarget.tripIsRunning())
            {
                EEPROMSetTripNumber(0);
            }
            hours = 0;
            //check month
            uint8_t daysInMonth = 0;
            auto day = EEPROMGetDay();
            auto dayOTW = EEPROMGetDayOfTheWeek();
            auto month = EEPROMGetMonth();
            auto year = EEPROMGetYear();
            switch (month)
            {
                case 1: //January
                    daysInMonth = 31;
                    break;
                case 2: //February
                    //check leap year
                    if (year % 4 == 0)
                        daysInMonth = 29;
                    else
                        daysInMonth = 28;
                    break;
                case 3: //March
                    daysInMonth = 31;
                    break;
                case 4: //April
                    daysInMonth = 30;
                    break;
                case 5: //May
                    daysInMonth = 31;
                    break;
                case 6: //June
                    daysInMonth = 30;
                    break;
                case 7: //July
                    daysInMonth = 31;
                    break;
                case 8: //August
                    daysInMonth = 31;
                    break;
                case 9: //September
                    daysInMonth = 30;
                    break;
                case 10: //October
                    daysInMonth = 31;
                    break;
                case 11: //November
                    daysInMonth = 30;
                    break;
                case 12: //December
                    daysInMonth = 31;
                    break;
            }
            if (day+1 <= daysInMonth)
            {
                EEPROMSetMinutes(mins);
                EEPROMSetHours(hours);
                EEPROMSetDay(day+1);
            }
            else //New month
            {
                day = 1;
                if (month+1 <= 12)
                {
                    EEPROMSetMinutes(mins);
                    EEPROMSetHours(hours);
                    EEPROMSetDay(day); 
                    EEPROMSetMonth(month+1);
                }
                else //New year!
                {
                    month = 1;
                    EEPROMSetMinutes(mins);
                    EEPROMSetHours(hours);
                    EEPROMSetDay(day); 
                    EEPROMSetMonth(month);
                    EEPROMSetYear(year+1);
                }
            }
            //check day of the week anyways
            if (dayOTW+1 < 6)
                EEPROMSetDayOfTheWeek(dayOTW+1);
            else
                EEPROMSetDayOfTheWeek(0);
        }
    }
}

void TimeModule::setDate(uint8_t day, uint8_t month, uint16_t year)
{
    EEPROMSetDay(day); 
    EEPROMSetMonth(month);
    EEPROMSetYear(year);
}

// TimeModuleNTP::TimeModuleNTP(WiFiUDP& udp_, const char* NTPServer_, const uint32_t UTCOffsetInSeconds_):
//     NTPClient(udp_, NTPServer_, UTCOffsetInSeconds_)
//     {}

// bool TimeModuleNTP::start()
// {
//     //checking date
//     if (EEPROMGetYear() == 0)
//     {
//         EEPROMSetYear(2001);
//         EEPROMSetMonth(1);
//         EEPROMSetDay(1);
//         EEPROMSetDayOfTheWeek(1); //0 is Sunday
//     }
//     //NTP
//     this->begin();
//     if (!this->update())
//         return false;
//     //update time
//     EEPROMSetHours(this->getHours());
//     EEPROMSetMinutes(this->getMinutes());
//     return true;
// }

// bool TimeModuleNTP::setTime(uint8_t hours, uint8_t minutes)
//     {
//         if (hours < 24)
//             EEPROMSetHours(hours);
//         else
//             return false;
//         if (minutes < 60)
//             EEPROMSetMinutes(minutes);
//         else
//             return false;
//         return true;
//     }

// void TimeModuleNTP::addMinute()
// {
//     auto mins = EEPROMGetMinutes();
//     if (mins+1 < 60)
//         EEPROMSetMinutes(mins+1);
//     else //New hour
//     {
//         mins = 0;
//         auto hours = EEPROMGetHours();
//         if (hours+1 < 24)
//         {
//             EEPROMSetMinutes(mins);
//             EEPROMSetHours(hours+1);
//         }
//         else //New day
//         {
//             hours = 0;
//             //check month
//             uint8_t daysInMonth = 0;
//             auto day = EEPROMGetDay();
//             auto dayOTW = EEPROMGetDayOfTheWeek();
//             auto month = EEPROMGetMonth();
//             auto year = EEPROMGetYear();
//             switch (month)
//             {
//                 case 1: //January
//                     daysInMonth = 31;
//                     break;
//                 case 2: //February
//                     //check leap year
//                     if (year % 4 == 0)
//                         daysInMonth = 29;
//                     else
//                         daysInMonth = 28;
//                     break;
//                 case 3: //March
//                     daysInMonth = 31;
//                     break;
//                 case 4: //April
//                     daysInMonth = 30;
//                     break;
//                 case 5: //May
//                     daysInMonth = 31;
//                     break;
//                 case 6: //June
//                     daysInMonth = 30;
//                     break;
//                 case 7: //July
//                     daysInMonth = 31;
//                     break;
//                 case 8: //August
//                     daysInMonth = 31;
//                     break;
//                 case 9: //September
//                     daysInMonth = 30;
//                     break;
//                 case 10: //October
//                     daysInMonth = 31;
//                     break;
//                 case 11: //November
//                     daysInMonth = 30;
//                     break;
//                 case 12: //December
//                     daysInMonth = 31;
//                     break;
//             }
//             if (day+1 <= daysInMonth)
//             {
//                 EEPROMSetMinutes(mins);
//                 EEPROMSetHours(hours);
//                 EEPROMSetDay(day+1);
//             }
//             else //New month
//             {
//                 day = 1;
//                 if (month+1 <= 12)
//                 {
//                     EEPROMSetMinutes(mins);
//                     EEPROMSetHours(hours);
//                     EEPROMSetDay(day); 
//                     EEPROMSetMonth(month+1);
//                 }
//                 else //New year!
//                 {
//                     month = 1;
//                     EEPROMSetMinutes(mins);
//                     EEPROMSetHours(hours);
//                     EEPROMSetDay(day); 
//                     EEPROMSetMonth(month);
//                     EEPROMSetYear(year+1);
//                 }
//             }
//             //check day of the week anyways
//             if (dayOTW+1 < 6)
//                 EEPROMSetDayOfTheWeek(dayOTW+1);
//             else
//                 EEPROMSetDayOfTheWeek(0);
//         }
//     }
// }

// void TimeModuleNTP::setDate(uint8_t day, uint8_t month, uint16_t year)
// {
//     EEPROMSetDay(day); 
//     EEPROMSetMonth(month);
//     EEPROMSetYear(year);
// }

// bool TimeModuleNTP::updateTime()
// {

//     if (!this->update())
//         return false;
//     EEPROMSetMinutes(this->getMinutes());
//     EEPROMSetHours(this->getHours());
//     return true;
// }