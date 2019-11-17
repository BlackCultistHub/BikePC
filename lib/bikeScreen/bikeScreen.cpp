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
void BikeScreen::drawFrame(uint16_t amount, uint16_t* x, uint16_t* y, uint16_t* widths, uint16_t* heights)
{
    for(uint16_t i = 0; i < amount; i++)
    {
        this->setCursor(x[i], y[i]);
        this->drawRect(x[i], y[i], widths[i], heights[i], ST7735_WHITE);
    }
}
void BikeScreen::drawTime(int time)
{

}
void BikeScreen::drawDate(int date)
{

}
void BikeScreen::drawBattery(uint8_t charge)
{
    this->setCursor(_batt_x, _batt_y);
    this->print(charge);
    this->print("%");
    //print icon
}
void BikeScreen::drawSpeed(uint8_t speed)
{
    this->setTextColor(ST7735_WHITE);
    this->setCursor(_speed_x, _speed_y);
    this->setTextSize(2);
    this->print(speed);
    this->setTextSize(1);
    this->print(" km/h");
}
void BikeScreen::drawCadence(uint32_t rpm)
{
    this->setTextColor(ST7735_WHITE);
    this->setCursor(_cadence_x, _cadence_y);
    this->setTextSize(2);
    this->print(rpm);
    this->setTextSize(1);
    this->print(" rpm");
}
void BikeScreen::drawPulse(uint8_t bpm)
{
    this->setTextColor(ST7735_WHITE);
    this->setCursor(_pulse_x, _pulse_y);
    this->setTextSize(2);
    this->print(bpm);
    this->setTextSize(1);
    this->print(" b/min");
}
void BikeScreen::drawOdo(uint64_t dist)
{
    this->setTextColor(ST7735_WHITE);
    this->setCursor(_odo_x, _odo_y);
    this->setTextSize(2);
    //this->print(dist);
    this->setTextSize(1);
    this->print(" km");
}
void BikeScreen::drawTrip(uint64_t dist)
{
    this->setTextColor(ST7735_WHITE);
    this->setCursor(_trip_x, _trip_y);
    this->setTextSize(2);
    //this->print(dist);
    this->setTextSize(1);
    this->print(" km");
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
