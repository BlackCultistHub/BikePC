
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

}
void drawSpeed(uint8_t speed)
{

}
void drawCadence(uint32_t rpm)
{

}
void drawPulse(uint8_t bpm)
{

}
void drawOdo(uint64_t dist)
{

}
void drawTrip(uint64_t dist)
{

}
//sets
void BikeScreen::setTime(int16_t ntime_x, int16_t ntime_y):
time_x(ntime_x),
time_y(ntime_y){
}
void setDate(int16_t ndate_x, int16_t ndate_y)
{

}
void setBattery(int16_t nbatt_x, int16_t nbatt_y)
{

}
void setSpeed(int16_t nspeed_x, int16_t nspeed_y)
{

}
void setCadence(int16_t ncadence_x, int16_t ncadence_y)
{

}
void setPulse(int16_t npulse_x, int16_t npulse_y)
{

}
void setOdo(int16_t nodo_x, int16_t nodo_y)
{

}
void setTrip(int16_t ntrip_x, int16_t ntrip_y)
{

}
