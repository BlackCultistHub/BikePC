#ifndef _BIKE_SCREENH_
#define _BIKE_SCREENH_
#include <Adafruit_ST7735.h>

class BikeScreen : public Adafruit_ST7735
{
  public:
    //constructors
    BikeScreen(int8_t cs, int8_t dc, int8_t rst);
    BikeScreen(int8_t cs, int8_t dc, int8_t mosi,
  int8_t sclk, int8_t rst);
    //~BikeScreen(){}
    //draws
    void drawFrame(uint16_t amount, uint16_t* x, uint16_t* y, uint16_t* widths, uint16_t* heights);
    void drawTime(int time/*time type*/);
    void drawDate(int date/*date type*/);
    void drawBattery(uint8_t charge);
    void drawSpeed(uint8_t speed);
    void drawCadence(uint32_t rpm);
    void drawPulse(uint8_t bpm);
    void drawOdo(uint64_t dist);
    void drawTrip(uint64_t dist);
    //sets
    void setTime(int16_t ntime_x, int16_t ntime_y);
    void setDate(int16_t ndate_x, int16_t ndate_y);
    void setBattery(int16_t nbatt_x, int16_t nbatt_y);
    void setSpeed(int16_t nspeed_x, int16_t nspeed_y);
    void setCadence(int16_t ncadence_x, int16_t ncadence_y);
    void setPulse(int16_t npulse_x, int16_t npulse_y);
    void setOdo(int16_t nodo_x, int16_t nodo_y);
    void setTrip(int16_t ntrip_x, int16_t ntrip_y);
    //gets
    void getTime(uint16_t* time) {time[0]=time_x; time[1]=time_y;}
    void getDate(uint16_t* date) {date[0]=date_x; date[1]=date_y;}
    void getBattery(uint16_t* batt) {batt[0]=batt_x; batt[1]=batt_y;}
    void getSpeed(uint16_t* speed) {speed[0]=speed_x; speed[1]=speed_y;}
    void getCadence(uint16_t* cadence) {cadence[0]=cadence_x; cadence[1]=cadence_y;}
    void getPulse(uint16_t* pulse) {pulse[0]=pulse_x; pulse[1]=pulse_y;}
    void getOdo(uint16_t* odo) {odo[0]=odo_x; odo[1]=odo_y;}
    void getTrip(uint16_t* trip) {trip[0]=trip_x; trip[1]=trip_y;}
  protected:
    int16_t time_x;
    int16_t time_y;
    int16_t date_x;
    int16_t date_y;
    int16_t batt_x;
    int16_t batt_y;
    int16_t speed_x;
    int16_t speed_y;
    int16_t cadence_x;
    int16_t cadence_y;
    int16_t pulse_x;
    int16_t pulse_y;
    int16_t odo_x;
    int16_t odo_y;
    int16_t trip_x;
    int16_t trip_y;
};
#endif // _BIKE_SCREENH_