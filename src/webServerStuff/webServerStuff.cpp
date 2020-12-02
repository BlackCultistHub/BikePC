#include "webServerStuff.h"

//***********[ Handlers ]***********
void handler404()
{
    server.send(404, "text/html", Page404);
}

void handlerIndex()
{
    server.send(200, "text/html", getMainPage());
}

void handlerChange()
{
  bool restart = false;
    if (server.hasArg("TimeDate"))
    {
      if (server.arg("TimeDate") == "true")
      {
        //time&date
        String timeRAW = server.arg("time");
        String hours = String(timeRAW[0]) + String(timeRAW[1]);
        String minutes = String(timeRAW[timeRAW.length()-2]) + String(timeRAW[timeRAW.length()-1]);
        String dateRAW = server.arg("date");
        String year = String(dateRAW[0]) + String(dateRAW[1]) + String(dateRAW[2]) + String(dateRAW[3]);
        String month = String(dateRAW[5]) + String(dateRAW[6]);
        String day = String(dateRAW[8]) + String(dateRAW[9]);

        EEPROMSetYear((uint16_t)year.toInt());
        EEPROMSetMonth((uint8_t)month.toInt());
        EEPROMSetDay((uint8_t)day.toInt());
        EEPROMSetHours((uint8_t)hours.toInt());
        EEPROMSetMinutes((uint8_t)minutes.toInt());
        EEPROMSetDayOfTheWeek(getDayOfTheYear(day.toInt(), (uint8_t)month.toInt(), (uint16_t)year.toInt()));
      }
    }    
    if (server.hasArg("wheel_radius_cm"))
    {
      EEPROMSetWheelRadius((uint16_t)server.arg("wheel_radius_cm").toInt());
    }
    if (server.hasArg("odo_m"))
    {
      EEPROMSetODO((uint32_t)server.arg("odo_m").toInt());
    }
    if (server.hasArg("sd_dt"))
    {
      if (server.arg("sd_dt") == "sd_time_30")
        EEPROMSetdtSd(30000);
      else if (server.arg("sd_dt") == "sd_time_60")
        EEPROMSetdtSd(60000);
      else if (server.arg("sd_dt") == "sd_time_300")
        EEPROMSetdtSd(300000);
      else if (server.arg("sd_dt") == "sd_time_600")
        EEPROMSetdtSd(600000);
    }
    if (server.hasArg("SetType"))
    {
      if (server.arg("SetType") == "AP")
      {
        //AP
        EEPROMSetSSID(server.arg("SSID"));
        EEPROMSetPassword(server.arg("password"));
        restart = true;
      }
      else if (server.arg("SetType") == "Client")
      {
        //Client
        EEPROMSetClientSSID(server.arg("SSID"));
        EEPROMSetClientPassword(server.arg("password"));
        restart = true;
      }
    }
    server.send(200, "text/html", PageChange);
    updateHW = true;
    if (restart)
    {
      delay(700);
      ESP.restart();
    }
}

void handlerSwitch()
{
    bool mode = EEPROMGetWiFiMode();
    EEPROMSetWiFiMode(!mode);
    server.send(200, "text/html", PageSwitch);
    delay(700);
    ESP.restart();
}

void handlerHardReset()
{
    EEPROMwipe();
    server.send(200, "text/html", PageHardReset);
    delay(700);
    ESP.restart();
}

void handlerInfo()
{
  server.send(200, "text/html", "Empty yet."); //!!!!!!!!!
}

void handlerStats()
{
    server.send(200, "text/html", getStatsPage());
}

void handlerGetSettings()
{
  server.send(200, "text/html", getSettingsPage());
}

void handlerData()
{
  //main
  if (server.hasArg("pulse"))
  {
    pulseRaw = server.arg("pulse");
    pulseUint = (uint8_t)pulseRaw.toInt();
    pulse_summ += pulseUint;
    pulse_measures++;
    update = true;
  }
  else
  {
    pulseRaw = "0";
  }
  /*
  for (uint8_t i = 0; i < MAX_DATA_ARGUMENT_AMOUNT; i++)
  {
    args[i] = "0";
    argVals[i] = "0";
  }
  for(uint8_t i = 0; i < server.args(); i++)
  {
    args[i] = server.argName(i);
    argVals[i] = server.arg(i);
  }
  argLen = server.args();
  String msg = String("<h1>Hello! ESP8266.<h1><br>")+
                      "Data recieve completed.<br>"+
                      "Recieved "+server.args()+" arguments.<br>"+
                      "Argument list:<br>";
  for(uint8_t i = 0; i < server.args(); i++)
    msg += (i+1)+". "+server.argName(i)+": "+server.arg(i)+"<br>";
  update = true;*/
  //server.send(200, "text/html", msg);
  server.send(200, "text/plain", "");
}

String getHeader()
{
  //inits
  PageHeaderBattery = String(getBatteryCharge()); //number
  PageHeaderDate = String(EEPROMGetDay()) + "/" + String(EEPROMGetMonth()) + "/" + String(EEPROMGetYear()); //dd/mm/yy
  PageHeaderTime = String(EEPROMGetHours()) + ":" + String(EEPROMGetMinutes()); //hh:mm
  String daysOfTheWeek[] = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
  PageHeaderDOTW = daysOfTheWeek[EEPROMGetDayOfTheWeek()]; //day of the week
  //forming page
  String header = "";
  header += PageHeader1;
  header += PageHeaderBattery;
  header += PageHeader2;
  header += PageHeaderDate;
  header += PageHeader3;
  header += PageHeaderTime;
  header += PageHeader4;
  header += PageHeaderDOTW;
  header += PageHeader5;
  return header;
}

String getMainPage()
{
  //forming page
  String indexPage = "";
  indexPage += PageIndex1;
  indexPage += getHeader();
  indexPage += PageIndex2;
  return indexPage;
}

String getStatsPage()
{
  //inits
  PageStatsTripNumber = String(EEPROMGetTripNumber()); //number
  PageStatsTrip = String(EEPROMGetTrip()); //number
  PageStatsHours = String(EEPROMGetTripHours()); //hours
  PageStatsMinutes = String(EEPROMGetTripMinutes()); //mins
  PageStatsAvgSpd = String(EEPROMGetTripSpd()); //number
  PageStatsAvgPulse = String(EEPROMGetTripPulse()); //number OR --
  PageStatsODO = String(EEPROMGetODO()); //number
  PageStatsAvgCad = String(EEPROMGetTripCad()); //number
  //forming page
  String page = "";
  page += PageStats1;
  page += getHeader();
  page += PageStats2;
  page += PageStatsTripNumber; //number
  page += PageStats3;
  page += PageStatsTrip; //number
  page += PageStats4;
  page += PageStatsHours; //hours
  page += PageStats5;
  page += PageStatsMinutes; //mins
  page += PageStats6;
  page += PageStatsAvgSpd; //number
  page += PageStats7;
  page += PageStatsAvgPulse; //number OR --
  page += PageStats8;
  page += PageStatsODO; //number
  page += PageStats9;
  page += PageStatsAvgCad; //number
  page += PageStats10;
  return page;
}

String getSettingsPage()
{
  //inits
  PageSettingsWheelRadius = String(EEPROMGetWheelRadius()); //number
  switch (EEPROMGetdtSd())
  {
    case 30000:
    PageSettingsTime30s = "checked";
      break;
    case 60000:
    PageSettingsTime60s = "checked";
      break;
    case 300000:
    PageSettingsTime5m = "checked";
      break;
    case 600000:
    PageSettingsTime10m = "checked";
      break;
  }
  if (EEPROMGetWiFiMode() == 1)
    PageSettingsWiFiMode = "Клиент"; //Client
  else
    PageSettingsWiFiMode = "Точка доступа"; //AP
  PageSettingsODO = String(EEPROMGetODO());; //number
  //forming page
  String page = "";
  page += PageSettings1;
  //insert header in here
  page += getHeader();
  page += PageSettings2;
  page += PageSettingsWheelRadius; //number
  page += PageSettings3;
  page += PageSettingsTime30s;
  page += PageSettings4;
  page += PageSettingsTime60s;
  page += PageSettings5;
  page += PageSettingsTime5m;
  page += PageSettings6;
  page += PageSettingsTime10m;
  page += PageSettings7;
  page += PageSettingsWiFiMode; //AP OR Client
  page += PageSettings8;
  page += PageSettingsODO; //number
  page += PageSettings9;
  return page;
}

uint8_t getDayOfTheYear(int8_t day, uint8_t month, uint16_t year)
{
  uint8_t MonthCodes[] = {0,3,3,6,1,4,6,2,5,0,3,5}; //jan to dec
  uint8_t centuryCodes[] = {6,4}; //XXI and XXII
  //1. year code
  String year2lastdigits = String(year);
  year2lastdigits = String(year2lastdigits[2]) + String(year2lastdigits[3]);
  uint8_t yd = year2lastdigits.toInt();
  int8_t yearCode = (yd + (yd / 4)) % 7;
  //2. month code
  int8_t monthCode = MonthCodes[month-1];
  //3. century code
  year2lastdigits = String(year);
  int8_t centuryCode;
  if (String(String(year2lastdigits[0]) + String(year2lastdigits[1])) == "20")
    centuryCode = centuryCodes[0];
  else if (String(String(year2lastdigits[0]) + String(year2lastdigits[1])) == "21")
    centuryCode = centuryCodes[1];
  else
    centuryCode = centuryCodes[0]; // force XXI
  //4. day number (done)
  //5. leap year index
  int8_t leapYearCode = 0;
  if (month == 1 || month == 2)
  {
    if (year%400 == 0)
    {
      if (year%100 == 0)
      {
        if (year%4 == 0)
        {
          leapYearCode = -1;
        }
      }
      else
      {
        leapYearCode = -1;
      }
    }
  }
  //6. calc
  uint8_t dayoftheweek = (yearCode + monthCode + day + centuryCode - leapYearCode)%7;
  if (dayoftheweek == 0)
    dayoftheweek = 6;
  else
    dayoftheweek--;
  return dayoftheweek;
}