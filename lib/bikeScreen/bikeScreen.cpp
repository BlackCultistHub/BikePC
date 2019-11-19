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
    delay(50);
    this->setTextSize(1);
    this->setCursor(_time_x, _time_y);
    this->print(timeH);
    this->print(":");
    this->print(timeM);
}
void BikeScreen::drawDate(char* date)
{
    this->fillRect(_date_x, _date_y, 50, 7, ST7735_BLACK);
    delay(50);
    this->setTextSize(0);
    this->setCursor(_date_x, _date_y);
    this->print(date);
}
void BikeScreen::drawBattery(uint8_t charge)
{
    this->setCursor(_batt_x, _batt_y);
    this->print(charge);
    this->print("%");
    //print icon green
    this->fillRect(_batt_x+20, _batt_y-2, 9, 12, ST7735_GREEN);
    this->drawRect(_batt_x+22, _batt_y-4, 5, 2, ST7735_GREEN);
    //delay(3000);
    //print charge
    this->fillRect(_batt_x+21, _batt_y-1, 7, 10, ST7735_BLACK);
    this->drawRect(_batt_x+20, _batt_y-2, 9, 12, ST7735_YELLOW);
    this->drawRect(_batt_x+22, _batt_y-4, 5, 2, ST7735_YELLOW);
    uint16_t x[] = {121, 120, 119, 118, 120, 119, 118},
            y[] = {9, 10, 11, 12, 14, 15, 16};
    for (uint8_t i = 0; i < 7; i++)
        this->drawPixel(x[i], y[i], ST7735_YELLOW);
    this->drawLine(117, 13, 121, 13, ST7735_YELLOW);
    //delay(3000);
    //print low-charge
    this->fillRect(_batt_x+21, _batt_y-1, 7, 10, ST7735_BLACK);
    this->drawRect(_batt_x+20, _batt_y-2, 9, 12, ST7735_RED);
    this->drawRect(_batt_x+22, _batt_y-4, 5, 2, ST7735_RED);
    this->drawLine(_batt_x+21, _batt_y+7, _batt_x+27, _batt_y+7, ST7735_RED);
    this->drawLine(_batt_x+24, _batt_y, _batt_x+24, _batt_y+3, ST7735_RED);
    this->drawPixel(_batt_x+24, _batt_y+5, ST7735_RED);
    //print mid green
    this->fillRect(_batt_x+21, _batt_y-1, 7, 10, ST7735_BLACK);
    this->drawRect(_batt_x+20, _batt_y-2, 9, 12, ST7735_GREEN);
    this->drawRect(_batt_x+22, _batt_y-4, 5, 2, ST7735_GREEN);
    this->fillRect(_batt_x+20, _batt_y+3, 9, 7, ST7735_GREEN);
}
void BikeScreen::drawSpeed(uint8_t speed)
{
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(3);
    this->setCursor(_speed_x, _speed_y);
    this->print(speed);
    this->setTextSize(2);
    this->setCursor(_speed_x+45, _speed_y+5);
    this->print("km/h");
    //icon
    this->drawPixelPic(&_speedIcon, _speed_x-15, _speed_y+3, ST7735_BLUE);
}
void BikeScreen::drawCadence(uint16_t rpm)
{
    this->fillRect(_cadence_x, _cadence_y, 58, 15, ST7735_BLACK);
    delay(50);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(3);
    this->setCursor(_cadence_x, _cadence_y);
    this->print(rpm);
    this->setTextSize(1);
    this->setCursor(_cadence_x+60, _cadence_y+13);
    this->print("rpm");
    //icon
    this->drawPixelPic(&_cadenceIcon, _cadence_x-23, _cadence_y+5, ST7735_WHITE);
}
void BikeScreen::drawPulse(uint8_t bpm)
{
    this->fillRect(_pulse_x, _pulse_y, 38, 25, ST7735_BLACK);
    delay(50);
    this->setTextColor(ST7735_WHITE);
    this->setTextSize(3);
    this->setCursor(_pulse_x, _pulse_y);
    this->print(bpm);
    this->setTextSize(1);
    this->setCursor(_pulse_x+40, _pulse_y+13);
    this->print("b/min");
    //icon
    this->drawPixelPic(&_pulseIcon, _pulse_x-23, _pulse_y+5, ST7735_RED);
}
void BikeScreen::drawOdo(uint64_t dist)
{
    this->setTextColor(ST7735_WHITE);
    this->setCursor(_odo_x, _odo_y);
    this->setTextSize(3);
    //this->print(dist);
    this->setTextSize(1);
    this->print("km");
}
void BikeScreen::drawTrip(uint64_t dist)
{
    this->setTextColor(ST7735_WHITE);
    this->setCursor(_trip_x, _trip_y);
    this->setTextSize(3);
    //this->print(dist);
    this->setTextSize(1);
    this->print("km");
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