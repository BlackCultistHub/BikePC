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
    void drawCadence(uint16_t rpm);
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
    void getTime(uint16_t* time) {time[0]=_time_x; time[1]=_time_y;}
    void getDate(uint16_t* date) {date[0]=_date_x; date[1]=_date_y;}
    void getBattery(uint16_t* batt) {batt[0]=_batt_x; batt[1]=_batt_y;}
    void getSpeed(uint16_t* speed) {speed[0]=_speed_x; speed[1]=_speed_y;}
    void getCadence(uint16_t* cadence) {cadence[0]=_cadence_x; cadence[1]=_cadence_y;}
    void getPulse(uint16_t* pulse) {pulse[0]=_pulse_x; pulse[1]=_pulse_y;}
    void getOdo(uint16_t* odo) {odo[0]=_odo_x; odo[1]=_odo_y;}
    void getTrip(uint16_t* trip) {trip[0]=_trip_x; trip[1]=_trip_y;}
  private:
    int16_t _time_x = 5;
    int16_t _time_y = 5;
    int16_t _date_x = 5;
    int16_t _date_y = 15;
    int16_t _batt_x = 95;
    int16_t _batt_y = 9;
    int16_t _speed_x = 25;
    int16_t _speed_y = 40;
    int16_t _cadence_x = 30;
    int16_t _cadence_y = 85;
    int16_t _pulse_x = 30;
    int16_t _pulse_y = 125;
    int16_t _odo_x = 20;
    int16_t _odo_y = 50;
    int16_t _trip_x = 20;
    int16_t _trip_y = 70;
};
#endif // _BIKE_SCREENH_