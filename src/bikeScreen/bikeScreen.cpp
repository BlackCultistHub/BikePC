#include "bikeScreen.h"

//Constructors
BikeScreen::BikeScreen(int8_t cs, int8_t dc, int8_t rst) : 
      Adafruit_ST7735 (cs, dc, rst) {
}

BikeScreen::BikeScreen(int8_t cs, int8_t dc, int8_t mosi,
  int8_t sclk, int8_t rst) : 
      Adafruit_ST7735 (cs, dc, mosi, sclk, rst) {
}

//Draws
void BikeScreen::drawBeginScreen(String ip, String ssid, String pwd)
{
    this->setCursor(0,0);
    this->println("        Hello!");
    this->println("");
    this->println("  You need to set up");
    this->println("  device via browser");
    this->println("    and connect a");
    this->println("   pulsometer now.");
    this->println("");
    this->println("        SSID:");
    this->print("    ");
    this->setTextColor(ST7735_YELLOW);
    this->println(ssid);
    this->setTextColor(ST7735_WHITE);
    this->println("");
    this->println("       Password:");
    this->print("    ");
    this->setTextColor(ST7735_YELLOW);
    this->println(pwd);
    this->setTextColor(ST7735_WHITE);
    this->println("");
    this->println("         IP:");
    this->print("     ");
    this->setTextColor(ST7735_YELLOW);
    this->println(ip);
    this->setTextColor(ST7735_WHITE);
    this->println("");
    this->println("");
    this->println("");
    this->println("   Press the button");
    this->println("      when done.");
}

void BikeScreen::drawPixelPic(String* pic, uint16_t x, uint16_t y, uint16_t color)
{
    uint16_t x0 = x;
    for (uint16_t i = 0; i < pic->length(); i++)
    {
        if ((*pic)[i] == '-')
            x++;
        if ((*pic)[i] == '*')
        {
            this->drawPixel(x, y, color);
            x++;
        }
        if ((*pic)[i] == '\n')
        {
            y++;
            x = x0;
        }
    }
}
void BikeScreen::drawFrame(uint16_t amount, uint16_t* x, uint16_t* y, uint16_t* widths, uint16_t* heights)
{
    for(uint16_t i = 0; i < amount; i++)
    {
        this->setCursor(x[i], y[i]);
        this->drawRect(x[i], y[i], widths[i], heights[i], ST7735_WHITE);
    }
}
void BikeScreen::drawTime(int timeH, int timeM)
{
    this->fillRect(_time_x, _time_y, 30, 7, ST7735_BLACK);
    delay(10);
    this->setTextSize(1);
    this->setCursor(_time_x, _time_y);
    this->print(timeH);
    this->print(":");
    if(timeM < 10)
        this->print("0");
    this->print(timeM);
}
void BikeScreen::drawDate(const char* date)
{
    this->fillRect(_date_x, _date_y, 50, 7, ST7735_BLACK);
    delay(10);
    this->setTextSize(0);
    this->setCursor(_date_x, _date_y);
    this->print(date);
}
void BikeScreen::drawBattery(uint8_t charge, boolean plugged)
{
    this->setCursor(_batt_x-5, _batt_y);
    this->print(charge);
    this->print("%");
    if (plugged)
    {
        //print charge
        this->fillRect(_batt_x+21, _batt_y-1, 7, 10, ST7735_BLACK);
        this->drawRect(_batt_x+20, _batt_y-2, 9, 12, ST7735_YELLOW);
        this->drawRect(_batt_x+22, _batt_y-4, 5, 2, ST7735_YELLOW);
        uint16_t x[] = {121, 120, 119, 118, 120, 119, 118},
                y[] = {9, 10, 11, 12, 14, 15, 16};
        for (uint8_t i = 0; i < 7; i++)
            this->drawPixel(x[i], y[i], ST7735_YELLOW);
        this->drawLine(117, 13, 121, 13, ST7735_YELLOW);
    }
    else if (charge < 40)
    {
        //print low-charge
        this->fillRect(_batt_x+21, _batt_y-1, 7, 10, ST7735_BLACK);
        this->drawRect(_batt_x+20, _batt_y-2, 9, 12, ST7735_RED);
        this->drawRect(_batt_x+22, _batt_y-4, 5, 2, ST7735_RED);
        this->drawLine(_batt_x+21, _batt_y+7, _batt_x+27, _batt_y+7, ST7735_RED);
        this->drawLine(_batt_x+24, _batt_y, _batt_x+24, _batt_y+3, ST7735_RED);
        this->drawPixel(_batt_x+24, _batt_y+5, ST7735_RED);
    }
    else if (charge < 80)
    {
        //print mid green
        this->fillRect(_batt_x+21, _batt_y-1, 7, 10, ST7735_BLACK);
        this->drawRect(_batt_x+20, _batt_y-2, 9, 12, ST7735_GREEN);
        this->drawRect(_batt_x+22, _batt_y-4, 5, 2, ST7735_GREEN);
        this->fillRect(_batt_x+20, _batt_y+3, 9, 7, ST7735_GREEN);
    }
    else
    {
        //print icon green
        this->fillRect(_batt_x+20, _batt_y-2, 9, 12, ST7735_GREEN);
        this->drawRect(_batt_x+22, _batt_y-4, 5, 2, ST7735_GREEN);
    }
}
void BikeScreen::drawSpeed(uint8_t speed)
{
    this->fillRect(_speed_x, _speed_y, 58, 22, ST7735_BLACK);
    delay(10);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(3);
    this->setCursor(_speed_x, _speed_y);
    this->print(speed);
    this->setTextSize(2);
    this->setCursor(_speed_x+60, _speed_y+5);
    this->print("Kmh");
    //icon
    this->drawPixelPic(&_speedIcon, _speed_x-15, _speed_y+3, ST7735_BLUE);
}
void BikeScreen::drawCadence(uint16_t rpm)
{
    this->fillRect(_cadence_x, _cadence_y, 58, 22, ST7735_BLACK);
    delay(10);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(3);
    this->setCursor(_cadence_x, _cadence_y);
    this->print(rpm);
    this->setTextSize(2);
    this->setCursor(_cadence_x+58, _cadence_y+5);
    this->print("Rpm");
    //icon
    this->drawPixelPic(&_cadenceIcon, _cadence_x-23, _cadence_y+5, ST7735_WHITE);
}
void BikeScreen::drawPulse(uint8_t bpm)
{
    this->fillRect(_pulse_x, _pulse_y, 38, 25, ST7735_BLACK);
    delay(10);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(3);
    this->setCursor(_pulse_x, _pulse_y);
    this->print(bpm);
    this->setTextSize(2);
    this->setCursor(_pulse_x+58, _pulse_y+5);
    this->print("Bpm");
    //icon
    this->drawPixelPic(&_pulseIcon, _pulse_x-23, _pulse_y+5, ST7735_RED);
}
void BikeScreen::drawOdo(uint32_t dist)
{
    this->fillRect(_odo_x+30, _odo_y+6, 70, 20, ST7735_BLACK);
    delay(10);
    this->setTextColor(ST7735_WHITE);
    this->setCursor(_odo_x+30, _odo_y+6);
    this->setTextSize(2);
    this->print(dist);
    this->setTextSize(1);
    this->setCursor(_odo_x+95, _odo_y+17);
    this->print("Km");
    //icon
    this->drawPixelPic(&_odoIcon1, _odo_x-5, _odo_y+5, ST7735_YELLOW);
    this->drawPixelPic(&_odoIcon2, _odo_x-1, _odo_y+6, ST7735_ORANGE);
    this->drawPixelPic(&_odoIcon3, _odo_x+3, _odo_y+7, ST7735_YELLOW);
}
void BikeScreen::drawTrip(float dist)
{
    this->fillRect(_trip_x, _trip_y, 58, 22, ST7735_BLACK);
    delay(10);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(2);
    this->setCursor(_trip_x, _trip_y);
    this->print(dist);
    this->setTextSize(1);
    this->setCursor(_trip_x+80, _trip_y+5);
    this->print("Km");
    //icon
    this->drawPixelPic(&_tripIcon, _trip_x-20, _trip_y, ST7735_ORANGE);
}
void BikeScreen::drawTripTime(uint16_t hours, uint16_t minutes)
{
    this->fillRect(_trip_time_x+16, _trip_time_y+1, 70, 22, ST7735_BLACK);
    delay(10);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(2);
    this->setCursor(_trip_time_x+16, _trip_time_y+1);
    this->print(hours);
    this->print("h ");
    this->print(minutes); 
    this->print("m"); 
    //icon
    this->drawPixelPic(&_tripTimeIcon1, _trip_time_x-5, _trip_time_y, ST7735_ORANGE);
    this->drawPixelPic(&_tripTimeIcon2, _trip_time_x-5, _trip_time_y, ST7735_YELLOW);
}
void BikeScreen::drawAvgSpd(uint8_t avgSpd)
{
    this->fillRect(_trip_spd_x, _trip_spd_y, 90, 20, ST7735_BLACK);
    delay(10);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(2);
    this->setCursor(_trip_spd_x-5, _trip_spd_y);
    this->print("AvgV:");
    this->print(avgSpd);
    this->setTextSize(1);
    this->setCursor(_trip_spd_x+95, _trip_spd_y+5);
    this->print("Kmh");
}
void BikeScreen::drawTripNumber(uint8_t tripNumber)
{
    this->fillRect(_time_x+50, _time_y, 30, 7, ST7735_BLACK);
    delay(10);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(1);
    this->setCursor(_time_x+50, _time_y+2);
    this->print("T-");
    this->print(tripNumber);
}

//sets
void BikeScreen::setTime(int16_t ntime_x, int16_t ntime_y)
{
    _time_x = ntime_x;
    _time_y = ntime_y;
}
void BikeScreen::setDate(int16_t ndate_x, int16_t ndate_y)
{
    _date_x = ndate_x;
    _date_y = ndate_y;
}
void BikeScreen::setBattery(int16_t nbatt_x, int16_t nbatt_y)
{
    _batt_x = nbatt_x;
    _batt_y = nbatt_y;
}
void BikeScreen::setSpeed(int16_t nspeed_x, int16_t nspeed_y)
{
    _speed_x = nspeed_x;
    _speed_y = nspeed_y;
}
void BikeScreen::setCadence(int16_t ncadence_x, int16_t ncadence_y)
{
    _cadence_x = ncadence_x;
    _cadence_y = ncadence_y;
}
void BikeScreen::setPulse(int16_t npulse_x, int16_t npulse_y)
{
    _pulse_x = npulse_x;
    _pulse_y = npulse_y;
}
void BikeScreen::setOdo(int16_t nodo_x, int16_t nodo_y)
{
    _odo_x = nodo_x;
    _odo_y = nodo_y;
}
void BikeScreen::setTrip(int16_t ntrip_x, int16_t ntrip_y)
{
    _trip_x = ntrip_x;
    _trip_y = ntrip_y;
}