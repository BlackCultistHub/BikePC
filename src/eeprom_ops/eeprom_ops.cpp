#include "eeprom_ops.h"

void EEPROMwipe() //wipe everything [0-FF]
{
  for (size_t i = 0; i < EEPROM.length(); i++)
    EEPROM.put(i, 0);
  EEPROM.commit();
}

uint8_t EEPROMGetWiFiMode() //[0]
{
  uint8_t wifiMode = 0;
  EEPROM.get(0, wifiMode);
  return wifiMode;
}

void EEPROMSetWiFiMode(bool mode) //[0]
{
  uint8_t wifiMode = mode;
  EEPROM.put(0, wifiMode);
  EEPROM.commit();
}

uint32_t EEPROMGetdtSd() //[1]
{
  uint8_t dtSdRaw = 0;
  uint32_t dtSd = 0;
  EEPROM.get(1, dtSdRaw);
  dtSdRaw &= 0x0F; // 0000'xxxx
  switch (dtSdRaw)
  {
    case 0x00:
      dtSd = 300000; //5m
      break;
    case 0x01:
      dtSd = 30000; //30s
      break;
    case 0x02:
      dtSd = 60000; //1m
      break;
    case 0x03:
      dtSd = 600000; //10m
      break;
  }
  return dtSd;
}
bool EEPROMSetdtSd(uint32_t dtSd) //[1]
{
  uint8_t dtSdRaw = 0;
  switch (dtSd)
  {
  case 300000:
    dtSdRaw = 0x00; //5m
    break;
  case 30000:
    dtSdRaw = 0x01; //30s
    break;
  case 60000:
    dtSdRaw = 0x02; //1m
    break;
  case 600000:
    dtSdRaw = 0x03; //10m
    break;
  default:
    return false;
    break;
  }
  EEPROM.put(1, dtSdRaw);
  EEPROM.commit();
  return true;
}

uint8_t EEPROMGetBeginMode() //[2]
{
  uint8_t mode;
  EEPROM.get(2, mode);
  return mode;
}
void EEPROMSetBeginMode(bool mode) //[2]
{
  uint8_t Mode = mode;
  EEPROM.put(2, Mode);
  EEPROM.commit();
}

bool EEPROMGetSleepMode() //[3] {xxxx}xxxx
{
  uint8_t mode;
  EEPROM.get(3, mode);
  mode >>= 4; //0000'xxxx
  return mode;
}
void EEPROMSetSleepMode(bool mode) //[3] {xxxx}xxxx
{
  //save counts
  uint8_t counts;
  EEPROM.get(3, counts);
  counts &= 0x0F; //mask 0000'xxxx
  //add mode
  mode <<= 4; //xxxx'0000
  counts += mode;
  //save summary ('counts' because of defined size)
  EEPROM.put(3, counts);
  EEPROM.commit();
}
uint8_t EEPROMGetSleepCounter() //[3] xxxx{xxxx}
{
  uint8_t counts;
  EEPROM.get(3, counts);
  counts &= 0x0F; //mask 0000'xxxx
  return counts;
}
void EEPROMSetSleepCounter(uint8_t counts) //[3] xxxx{xxxx}
{
  //save mode
  uint8_t mode;
  EEPROM.get(3, mode);
  mode &= 0xF0; //mask 1111'0000
  //add counts
  counts &= 0x0F; //mask 0000'1111 just in case
  counts += mode;
  //save summary
  EEPROM.put(3, counts);
  EEPROM.commit();
}

String EEPROMGetSSID()  //[4-23]
{
  char ssid[20]; 
  EEPROM.get(4, ssid);
  return ssid;
}

void EEPROMSetSSID(String ssid)  //[4-23]
{
  for (int i = 0; i < 20; i++)
   EEPROM.put(i+4, ssid[i]);
  EEPROM.commit();
}

String EEPROMGetPassword()  //[24-43]
{
  char password[20];
  EEPROM.get(24, password);
  return password;
}

void EEPROMSetPassword(String password)  //[24-43]
{
  for (int i = 0; i < 20; i++)
   EEPROM.put(i+24, password[i]);
  EEPROM.commit();
}

String EEPROMGetClientSSID()  //[44-63]
{
  char ssid[20];
  EEPROM.get(44, ssid);
  return ssid;
}

void EEPROMSetClientSSID(String ssid)  //[44-63]
{
  for (int i = 0; i < 20; i++)
    EEPROM.put(i+44, ssid[i]);
  EEPROM.commit();
}

String EEPROMGetClientPassword()  //[64-83]
{
  char password[20];
  EEPROM.get(64, password);
  return password;
}

void EEPROMSetClientPassword(String password)  //[64-83]
{
  for (int i = 0; i < 20; i++)
    EEPROM.put(i+64, password[i]);
  EEPROM.commit();
}
/*
* @return radius in mm
*/
uint16_t EEPROMGetWheelRadius() //[84-85]
{
  uint16_t wheel_radius;
  EEPROM.get(84, wheel_radius);
  return wheel_radius;
}
/*
* Input in mm
*/
void EEPROMSetWheelRadius(uint16_t wheel_radius)  //[84-85]
{
  EEPROM.put(84, wheel_radius);
  EEPROM.commit();
}

uint8_t EEPROMGetTripNumber() //[87]
{
  uint8_t trip_number;
  EEPROM.get(87, trip_number);
  return trip_number;
}
void EEPROMSetTripNumber(uint8_t trip_number) //[87]
{
  EEPROM.put(87, trip_number);
  EEPROM.commit();
}

uint32_t EEPROMGetODO() //[104-107]
{
  uint32_t odo;
  EEPROM.get(104, odo);
  return odo;
}

void EEPROMSetODO(uint32_t odo) //[104-107]
{
  EEPROM.put(104, odo);
  EEPROM.commit();
}

uint8_t EEPROMGetTripCad() //[108]
{
  uint32_t trip_avgCad;
  EEPROM.get(108, trip_avgCad);
  return trip_avgCad;
}
void EEPROMSetTripCad(uint8_t trip_avgCad) //[108]
{
  EEPROM.put(108, trip_avgCad);
  EEPROM.commit();
}
uint8_t EEPROMGetTripPulse() //[109]
{
  uint32_t trip_avgPul;
  EEPROM.get(109, trip_avgPul);
  return trip_avgPul;
}
void EEPROMSetTripPulse(uint8_t trip_avgPul) //[109]
{
  EEPROM.put(109, trip_avgPul);
  EEPROM.commit();
}

void EEPROMSetTripStartDate(String date)  //[110-119]
{
  uint8_t diff = 10 - date.length();
  for (int i = 0; i < 10-diff; i++)
  {
    EEPROM.put(i+110, date[i]);
  }
  for (int i = 10-diff; i < 10; i++)
  {
    EEPROM.put(i+110, '-');
  }
  EEPROM.commit();
}

String EEPROMGetTripStartDate()  //[110-119]
{
  char date[10];
  EEPROM.get(110, date);
  String dateS = "";
  for (int i = 0; i < 10; i++)
  {
    if (date[i] != '-')
    {
      dateS += date[i];
    }
  }
  return dateS;
}

//-------------------------------------------------------------time
uint8_t EEPROMGetDay() //[88]
{
  uint8_t day;
  EEPROM.get(88, day);
  return day;
}
void EEPROMSetDay(uint8_t day) //[88]
{
  EEPROM.put(88, day);
  EEPROM.commit();
}
uint8_t EEPROMGetMonth() //[89]
{
  uint8_t month;
  EEPROM.get(89, month);
  return month;
}
void EEPROMSetMonth(uint8_t month) //[89]
{
  EEPROM.put(89, month);
  EEPROM.commit();
}
uint16_t EEPROMGetYear() //[90-91]
{
  uint16_t year;
  EEPROM.get(90, year);
  return year;
}
void EEPROMSetYear(uint16_t year) //[90-91]
{
  EEPROM.put(90, year);
  EEPROM.commit();
}
uint8_t EEPROMGetDayOfTheWeek() //[92]
{
  uint8_t dayOTW;
  EEPROM.get(92, dayOTW);
  return dayOTW;
}
void EEPROMSetDayOfTheWeek(uint8_t dayOTW) //[92]
{
  EEPROM.put(92, dayOTW);
  EEPROM.commit();
}
uint8_t EEPROMGetHours() //[93]
{
  uint8_t hours;
  EEPROM.get(93, hours);
  return hours;
}
void EEPROMSetHours(uint8_t hours) //[93]
{
  EEPROM.put(93, hours);
  EEPROM.commit();
}
uint8_t EEPROMGetMinutes() //[94]
{
  uint8_t minutes;
  EEPROM.get(94, minutes);
  return minutes;
}
void EEPROMSetMinutes(uint8_t minutes) //[94]
{
  EEPROM.put(94, minutes);
  EEPROM.commit();
}

//--------------------------------------------------trip
uint32_t EEPROMGetTrip() //[95-98]
{
  uint32_t trip;
  EEPROM.get(95, trip);
  return trip;
}
void EEPROMSetTrip(uint32_t trip) //[95-98]
{
  EEPROM.put(95, trip);
  EEPROM.commit();
}
uint16_t EEPROMGetTripHours() //[99-100]
{
  uint16_t trip_hours;
  EEPROM.get(99, trip_hours);
  return trip_hours;
}
void EEPROMSetTripHours(uint16_t trip_hours) //[99-100]
{
  EEPROM.put(99, trip_hours);
  EEPROM.commit();
}
uint16_t EEPROMGetTripMinutes() //[101-102]
{
  uint16_t trip_minutes;
  EEPROM.get(101, trip_minutes);
  return trip_minutes;
}
void EEPROMSetTripMinutes(uint16_t trip_minutes) //[101-102]
{
  EEPROM.put(101, trip_minutes);
  EEPROM.commit();
}
uint8_t EEPROMGetTripSpd() //[103]
{
  uint8_t trip_avgSpd;
  EEPROM.get(103, trip_avgSpd);
  return trip_avgSpd;
}
void EEPROMSetTripSpd(uint8_t trip_avgSpd) //[103]
{
  EEPROM.put(103, trip_avgSpd);
  EEPROM.commit();
}