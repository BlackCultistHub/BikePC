#include "misc/stdafx.h"
#include "misc/Shared_params.h"

//-----ST7735 TFT module connections-----
#define TFT_CS    1 //TX      // TFT CS  pin is connected to NodeMCU pin D3 (GPIO0)
#define TFT_DC    3 //RX     // TFT DC  pin is connected to NodeMCU pin D2 (GPIO4)
// initialize ST7735 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)

//-----SD PIN DEFINE-----
#define SD_CS D8 // SD CS pin is connected to NodeMCU pin D8

//-----MISC PIN DEFINE-----
#define GIRCONE_CADENCE D3
#define GIRCONE_SPEED D4
#define BUTTON_PIN D1
#define BATTERY_PIN D2 //change in 'misc/battery.h'
#define WAKE_PIN D0

//-----Defines-----
#define TIME_TO_WAKE 5e3 //in ms, time to hold the button for device wake, must be so 60 can be divided by it
#define TIME_BEFORE_SLEEP 180e3 //3min, in ms
#define UPDATE_TIME 60e3 //in ms
#define UPDATE_RPM 500 //in ms
#define TRIP_TIME_UPDATE 30e3 //ms
#define WIFI_CONNECTION_WAIT 10e3 //in ms
#define TIMER_LIMIT 5e3
#define HW_TIMER_INTERVAL_MS 50 //for clock

//-----Default WiFi Settings-----
#define WIFI_AP_SSID "BikePC_Brain"
#define WIFI_AP_PASWD "ESPbikepc2020"
#define WIFI_CL_SSID ""
#define WIFI_CL_PASWD ""

//-----Values-----
//tft
String logo = String("");
uint16_t xs[] = {0, 0, 0, 0}, //frames for screen draw page 0
          widths[] = {128, 128, 128, 128},
          ys[] = {0, 25, 74, 118},
          heights[] = {24, 48, 43, 39};
uint16_t xs1[] = {0, 0, 0, 0, 0},
          widths1[] = {128, 128, 128, 128, 128},
          ys1[] = {0, 25, 65, 96, 127},
          heights1[] = {24, 39, 30, 30, 33};
volatile bool page = 0;
volatile bool pageOnChange = false;
//time
String daysOfTheWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
volatile bool hardwareUpdate = false;
//timers
uint32_t timerTimeUpdate = 1; //universal timer
volatile uint32_t timer_button_isr = 500;
volatile uint32_t timerPushedButton = 0;
uint32_t timerRPMUpdate = 1; //page info timer
uint32_t timerTripTime = 0;
uint32_t timerDataUpdate = 0;
uint32_t timerSDUpdate = 0;
uint64_t timerSleepCheck = 0;

//temp
String temp;

//-----Object Inits-----
BikeScreen tft(TFT_CS, TFT_DC, -1); //tft screen object
ESP8266WebServer server(80);
ESP8266Timer TimerClockBase;
ISRTimer TimerClock;
TimeModule GeneralTime;
bikeCounter MainCounter;

//-----ISR's-----

void ICACHE_RAM_ATTR gircRPMInterr()
{
  if (!MainCounter.tripIsRunning())
    MainCounter.trip_start();
  MainCounter.cad_impulse();
}

void ICACHE_RAM_ATTR gircSpdInterr()
{
  MainCounter.spd_impulse();
}

void ICACHE_RAM_ATTR buttonInterr()
{
  if (millis() - timer_button_isr > 200)
  {
    timer_button_isr = millis();
    timerPushedButton = millis();
    while (digitalRead(BUTTON_PIN) && page)
    {
      if (millis() - timerPushedButton >= 5000)
      {
        MainCounter.trip_stop();
        pageOnChange = true;
        break;
      }
      wdt_reset();
    }
    if (!pageOnChange)
    {
      page = !page;
      pageOnChange = true;
    }
  }
}

void ICACHE_RAM_ATTR runTimer(void)
{
  TimerClock.run();
}

void ICACHE_RAM_ATTR countMinute()
{
  GeneralTime.addMinute(MainCounter);
  hardwareUpdate = true;
}

void ICACHE_RAM_ATTR countTripMinute()
{
  if (MainCounter.tripIsRunning())
  {
    if (EEPROMGetTripMinutes() >= 60)
    {
      EEPROMSetTripMinutes(0);
      EEPROMSetTripHours(EEPROMGetTripHours()+1);
    }
    else
    {
      EEPROMSetTripMinutes(EEPROMGetTripMinutes()+1);
    }
  }
}

//-----Function Prototypes-----
void refresh(Adafruit_ST7735*);
void updateBattery();

//-----Inits and One-Time Run-----
void setup(void)
{
  //Serial.begin(9600);
  //delay(10);
  //Serial.println("");  

  EEPROM.begin(EEPROM_SIZE);
  if (EEPROMGetSleepMode())
  {
    pinMode(BUTTON_PIN, INPUT);
    uint32_t press_timer = millis();
    bool sleep = true;
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
      if (millis()-press_timer >= TIME_TO_WAKE)
      {
        sleep = false;
        EEPROMSetSleepMode(0);
        EEPROMSetSleepCounter(0);
        break;
      }
    }
    if (sleep)
    {
      uint8_t sleep_counter = EEPROMGetSleepCounter();
      if (sleep_counter >= 60/(TIME_TO_WAKE/1000))
      {
        EEPROMSetSleepCounter(0);
        GeneralTime.addMinute(MainCounter);
      }
      else
      {
        EEPROMSetSleepCounter(sleep_counter+1);
      }
      ESP.deepSleep(TIME_TO_WAKE * 1000);
    }
  }

  // initialize a ST7735S chip, black tab
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  delay(500);

  // EEPROM INIT
  tft.print("EEPROM ");
  tft.setTextColor(ST7735_GREEN);
  tft.println("OK");
  tft.setTextColor(ST7735_WHITE);

  
  pinMode(BUTTON_PIN, INPUT);
  uint32_t hardResetTimer = millis();
  bool wipe = false;
  bool wifiReset = false;
  bool wipeWarning = false;
  while (digitalRead(BUTTON_PIN))
  {
    if (!wipeWarning)
    {
      wipeWarning = true;
      tft.println("Hold to WiFi Reset!");
    }
    if (millis() - hardResetTimer > 10000)
    {
      EEPROMSetSSID("");
      EEPROMSetPassword("");
      EEPROMSetWiFiMode(false);
      wifiReset = true;
      break;
    }
    wdt_reset();
  }
  wipeWarning = false;
  hardResetTimer = millis();
  //wipe info message
  if (wifiReset)
  {
    tft.setTextColor(ST7735_RED);
    tft.println("WiFi Reset.");
    tft.setTextColor(ST7735_WHITE);
  }
  while (digitalRead(BUTTON_PIN))
  {
    if (!wipeWarning)
    {
      wipeWarning = true;
      tft.println("Hold to FULL WIPE!");
    }
    if (millis() - hardResetTimer > 10000)
    {
      EEPROMwipe();
      wipe = true;
      break;
    }
    wdt_reset();
  }
  //wipe info message
  if (wipe)
  {
    tft.setTextColor(ST7735_RED);
    tft.println("EEPROM wiped.");
    tft.setTextColor(ST7735_WHITE);
  }
  if (wipe || wifiReset)
  {
    tft.println("Restarting...");
    tft.println("");
    tft.setTextColor(ST7735_YELLOW);
    tft.println("Re-Insert SD-card!");
    tft.setTextColor(ST7735_WHITE);
    delay(2000);
    ESP.restart();
  }

  // initialize pins
  pinMode(GIRCONE_CADENCE, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(GIRCONE_CADENCE), gircRPMInterr, FALLING);
  pinMode(GIRCONE_SPEED, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(GIRCONE_SPEED), gircSpdInterr, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterr, RISING);
  pinMode(BATTERY_PIN, INPUT);

  //SD INIT
  String SD_ERROR_MESSAGE = "";
  if (MainCounter.initSD(SD_CS, &SD_ERROR_MESSAGE))
  {
    tft.print("SD ");
    tft.setTextColor(ST7735_GREEN);
    tft.println("OK");
    tft.setTextColor(ST7735_WHITE);
  }
  else
  {
    tft.setTextColor(ST7735_RED);
    tft.println("SD ERROR:");
    tft.println(SD_ERROR_MESSAGE);
    tft.setTextColor(ST7735_WHITE);
  }

  // WIFI INIT
  bool WiFiMode = EEPROMGetWiFiMode();
  String ssid = "",
        password = "";
  if (WiFiMode)
  {
    //Client mode
    tft.println("Entering Client mode:\n");

    //SSID define
    if (EEPROMGetClientSSID() == "")
    {
      //default AP ssid
      ssid = WIFI_CL_SSID;
      tft.println("using default ssid");
    }
    else
    {
      ssid = EEPROMGetClientSSID();
      tft.println("using custom ssid");
    }

    //Password define
    if (EEPROMGetClientPassword() == "")
    {
      //default AP paswd
      password = WIFI_CL_PASWD;
      tft.println("with default passw.");
    }
    else
    {
      password = EEPROMGetClientPassword();
      tft.println("with custom passw.");
    }

    //Connecting
    tft.printf("Connecting to\n%s\n", ssid.c_str());
    WiFi.persistent(false);
    WiFi.disconnect(true);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      tft.print(".");
      if ((millis() - timerRPMUpdate) > WIFI_CONNECTION_WAIT)
      {
        tft.setTextColor(ST7735_RED);
        tft.println("Could not connect to WIFI.");
        tft.setTextColor(ST7735_WHITE);
        timerRPMUpdate = millis();
        break;
      }
    }
    timerRPMUpdate = 1;
    if (WiFi.status() == WL_CONNECTED)
    {
      tft.setTextColor(ST7735_GREEN);
      tft.println("\nConnected.");
      tft.setTextColor(ST7735_WHITE);
    }
  }
  else
  {
    //Access point mode
    tft.println("Entering AP mode:");

    //SSID define
    if (EEPROMGetSSID() == "")
    {
      //default AP ssid
      ssid = WIFI_AP_SSID;
      tft.println("using deflt ssid");
    }
    else
    {
      ssid = EEPROMGetSSID();
      tft.println("using custom ssid");
    }

    //Password define
    if (EEPROMGetPassword() == "")
    {
      //default AP paswd
      password = WIFI_AP_PASWD;
      tft.setTextColor(ST7735_YELLOW);
      tft.println("with deflt password.");
      tft.setTextColor(ST7735_WHITE);
    }
    else
    {
      password = EEPROMGetPassword();
      tft.println("with custom password.");
    }

    //Connect
    WiFi.softAP(ssid, password);
    tft.setTextColor(ST7735_GREEN);
    tft.println("Access Point OK");
    tft.setTextColor(ST7735_WHITE);
    tft.printf("SSID: %s\nPswd: %s\n", ssid.c_str(), password.c_str());
  }

  //Starting ISR-time-clock
  if (TimerClockBase.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, runTimer)) //60s
  {
    tft.print("Clock ");
    tft.setTextColor(ST7735_GREEN);
    tft.println("OK");
    tft.setTextColor(ST7735_WHITE);
  }
  else
  {
    tft.setTextColor(ST7735_RED);
    tft.println("Clock ERROR!");
    tft.setTextColor(ST7735_WHITE);
  }

  TimerClock.setInterval(60000L, countMinute);
  TimerClock.setInterval(60000L, countTripMinute);

  //time&date
  GeneralTime.begin();
  if (GeneralTime.isSet())
  {
    tft.setTextColor(ST7735_GREEN);
    tft.println("Time record found.");
    tft.setTextColor(ST7735_WHITE);
  }
  else
  {
    tft.setTextColor(ST7735_RED);
    tft.println("Time not set!");
    tft.setTextColor(ST7735_WHITE);
  }

  //webserver
  server.begin();
  tft.print("Web server started,\nlocal ip is:\n");
  delay(1000);
  if (WiFiMode)
    tft.println(WiFi.localIP().toString().c_str());
  else
    tft.println(WiFi.softAPIP().toString().c_str());
  delay(7000);

  // SCREEN Draw
  if (!EEPROMGetBeginMode())
  {
    tft.fillScreen(ST7735_BLACK);
    if (EEPROMGetSSID() == "")
      tft.drawBeginScreen(WiFi.softAPIP().toString(), WIFI_AP_SSID, WIFI_AP_PASWD);
    else
      tft.drawBeginScreen(WiFi.softAPIP().toString(), EEPROMGetSSID(), EEPROMGetPassword());
  }
  else
  {
    tft.fillScreen(ST7735_BLACK);
    tft.drawFrame(4, xs, ys, widths, heights);
    tft.drawTime(EEPROMGetHours(), EEPROMGetMinutes());
    tft.drawDate(daysOfTheWeek[EEPROMGetDayOfTheWeek()].c_str());
    tft.drawTripNumber(EEPROMGetTripNumber());
    updateBattery();
    tft.drawSpeed(0);
    tft.drawCadence(0);
    tft.drawPulse(0);
  }

  //sleep timer set
  timerSleepCheck = millis();

  //HANDLERS
  server.onNotFound(handler404);
  server.on("/", handlerIndex);
  server.on("/data", HTTP_POST, handlerData);
  server.on("/setup", HTTP_POST, handlerChange);
  server.on("/stats", handlerStats);
  server.on("/info", handlerInfo);
  server.on("/switch_mode", HTTP_POST, handlerSwitch);
  server.on("/factory_reset", HTTP_POST, handlerHardReset);
  server.on("/get_settings", handlerGetSettings);
}

//-----Inf Loop-----
void loop(void) 
{
  server.handleClient();
  if (!EEPROMGetBeginMode())
  {
    uint32_t timer_button = millis();
    while (digitalRead(BUTTON_PIN))
    {
      if (millis() - timer_button > 500)
      {
        EEPROMSetBeginMode(true);
        break;
      }
      wdt_reset();
    }
  }
  else
  {
  if (!page)
  {
    if (pageOnChange)
    {
      pageOnChange = false;
      tft.fillScreen(ST7735_BLACK);
      tft.drawFrame(4, xs, ys, widths, heights);
      tft.drawTime(EEPROMGetHours(), EEPROMGetMinutes());
      tft.drawDate(daysOfTheWeek[EEPROMGetDayOfTheWeek()].c_str());
      tft.drawTripNumber(EEPROMGetTripNumber());
      updateBattery();
      tft.drawCadence(MainCounter.getCadence());
      tft.drawSpeed(MainCounter.getSpeed());
      tft.drawPulse(0);
    }
    if (update)
    {
      tft.drawPulse(pulseUint);
      update = false;
    }
    //RPM timers update every 1s
    if ((millis()-timerRPMUpdate) > UPDATE_RPM)
    {
      if (MainCounter.elapsed())
      {
        tft.drawCadence(MainCounter.getCadence());
        tft.drawSpeed(MainCounter.getSpeed());
      }
      if (MainCounter.cadenceUpdated())
        tft.drawCadence(MainCounter.getCadence());
      if (MainCounter.speedUpdated())
        tft.drawSpeed(MainCounter.getSpeed());
      timerRPMUpdate = millis();
    }
  }
  else
  {
    if (pageOnChange)
    {
      pageOnChange = false;
      tft.fillScreen(ST7735_BLACK);
      tft.drawFrame(5, xs1, ys1, widths1, heights1);
      tft.drawTime(EEPROMGetHours(), EEPROMGetMinutes());
      tft.drawDate(daysOfTheWeek[EEPROMGetDayOfTheWeek()].c_str());
      tft.drawTripNumber(EEPROMGetTripNumber());
      updateBattery();
      tft.drawTrip(MainCounter.getSessionTrip()/1000);
      tft.drawTripTime(EEPROMGetTripHours(), EEPROMGetTripMinutes());
      tft.drawAvgSpd(MainCounter.getAverageSpeedPerTrip());
      tft.drawOdo(EEPROMGetODO()/1000);
    }
    if ((millis()-timerRPMUpdate) > UPDATE_RPM)
    {
      if (MainCounter.tripUpdated())
        tft.drawTrip(MainCounter.getSessionTrip()/1000);
      if (MainCounter.avgSpdUpdated())
        tft.drawAvgSpd(MainCounter.getAverageSpeedPerTrip());
      if (MainCounter.odoUpdated())
        tft.drawOdo(EEPROMGetODO()/1000);
      if (millis()-timerTimeUpdate > TRIP_TIME_UPDATE)
      {
        tft.drawTripTime(EEPROMGetTripHours(), EEPROMGetTripMinutes());
        timerTimeUpdate = millis();
      }
      timerRPMUpdate = millis();
    }
  }
  //sleep check
  if (MainCounter.elapsed())
  {
    if (millis() - timerSleepCheck >= TIME_BEFORE_SLEEP)
    {
      ESP.deepSleep(TIME_TO_WAKE * 1000);
    }
  }
  else
  {
    timerSleepCheck = millis();
  }
  //external update
  if (updateHW)
  {
    MainCounter.updateRadius(EEPROMGetWheelRadius());
    updateHW = false;
  }
  //Hardware info update
  if (hardwareUpdate)
  {
    //TIME&DATE UPDATE EVERY Ns
    hardwareUpdate = false;
    tft.drawTime(EEPROMGetHours(), EEPROMGetMinutes());
    tft.drawDate(daysOfTheWeek[EEPROMGetDayOfTheWeek()].c_str());
    updateBattery();
  }
  //update data via period
  if (millis()-timerDataUpdate > 10000)
  {
    MainCounter.saveStats();
    timerDataUpdate = millis();
  }
  //update sd data
  if (millis() - timerSDUpdate > EEPROMGetdtSd())
  {
    MainCounter.saveStatsSD();
    timerSDUpdate = millis();
  }
  }
  delay(1);
}

//-----Function Definitions-----
void refresh(Adafruit_ST7735* screen)
{
  screen->fillScreen(ST7735_BLACK);
  screen->setCursor(0,0);
}

void updateBattery()
{
  tft.drawBattery(getBatteryCharge(), false);
}