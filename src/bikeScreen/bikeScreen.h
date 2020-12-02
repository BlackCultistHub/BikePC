#pragma once
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
    void drawBeginScreen(String ip, String ssid, String pwd);
    void drawPixelPic(String* pic, uint16_t x, uint16_t y, uint16_t color);
    void drawFrame(uint16_t amount, uint16_t* x, uint16_t* y, uint16_t* widths, uint16_t* heights);
    void drawTime(int timeH, int timeM);
    void drawDate(const char* date);
    void drawBattery(uint8_t charge, boolean plugged);
    void drawSpeed(uint8_t speed);
    void drawCadence(uint16_t rpm);
    void drawPulse(uint8_t bpm);
    void drawOdo(uint32_t dist);
    void drawTrip(float dist);
    void drawTripTime(uint16_t hours, uint16_t minutes);
    void drawAvgSpd(uint8_t avgSpd);
    void drawTripNumber(uint8_t tripNumber);
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
    int16_t _time_y = 4;
    int16_t _date_x = 5;
    int16_t _date_y = 13;
    int16_t _batt_x = 95;
    int16_t _batt_y = 9;
    int16_t _speed_x = 25;
    int16_t _speed_y = 40;
    int16_t _cadence_x = 30;
    int16_t _cadence_y = 85;
    int16_t _pulse_x = 30;
    int16_t _pulse_y = 125;
    int16_t _odo_x = 10;
    int16_t _odo_y = 130;
    int16_t _trip_x = 25;
    int16_t _trip_y = 40;
    int16_t _trip_time_x = 10;
    int16_t _trip_time_y = 71;
    int16_t _trip_spd_x = 10;
    int16_t _trip_spd_y = 104;
    //icons
    String _cadenceIcon = String("")+ //16x16
    "----********--**\n"+
    "----********--**\n"+
    "--**--------**--\n"+
    "--**--------**--\n"+
    "**--------**--**\n"+
    "**--------**--**\n"+
    "**------**----**\n"+
    "**------**----**\n"+
    "**----**------**\n"+
    "**----**------**\n"+
    "**--**--------**\n"+
    "**--**--------**\n"+
    "--**--------**--\n"+
    "--**--------**--\n"+
    "**--********----\n"+
    "**--********----\n";
    String _pulseIcon = String("")+
    "--****----****--\n"+
    "-******--******-\n"+
    "*******--*******\n"+
    "****************\n"+
    "****************\n"+
    "****************\n"+
    "-**************-\n"+
    "--************--\n"+
    "---**********---\n"+
    "----********----\n"+
    "-----******-----\n"+
    "------****------\n"+
    "-------**-------\n";
    String _speedIcon = String("")+
    "*--------*\n"+
    "**------**\n"+
    "**------**\n"+
    "**------**\n"+
    "***----***\n"+
    "***----***\n"+
    "***----***\n"+
    "***----***\n"+
    "***----***\n"+
    "-***--***-\n"+
    "-***--***-\n"+
    "--**--**--\n"+
    "--******--\n"+
    "---****---\n"+
    "---****---\n"+
    "----**----\n";
    String _tripIcon = String("")+ //14x14, orange
    "-************-\n"+
    "**************\n"+
    "**----**----**\n"+
    "-*----**----*-\n"+
    "------**------\n"+
    "------**------\n"+
    "------**------\n"+
    "------**------\n"+
    "------**------\n"+
    "------**------\n"+
    "------**------\n"+
    "------**------\n"+
    "------**------\n"+
    "------**------\n";
    String _tripTimeIcon1 = String("")+ //14x16, orange
    "**************\n"+
    "**************\n"+
    "**----------**\n"+
    "-**--------**-\n"+
    "--**------**--\n"+
    "---**----**---\n"+
    "----**--**----\n"+
    "-----****-----\n"+
    "-----****-----\n"+
    "----**--**----\n"+
    "---**----**---\n"+
    "--**------**--\n"+
    "-**--------**-\n"+
    "**----------**\n"+
    "**************\n"+
    "**************\n";
    String _tripTimeIcon2 = String("")+ //14x14, yellow
    "--------------\n"+
    "--------------\n"+
    "--------------\n"+
    "---***---**---\n"+
    "----******----\n"+
    "-----****-----\n"+
    "------**------\n"+
    "--------------\n"+
    "--------------\n"+
    "-------*------\n"+
    "-------*------\n"+
    "--------------\n"+
    "------***-----\n"+
    "----*******---\n";
    String _odoIcon1 = String("")+ //Green
    "-***\n"+
    "****\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "**--\n"+
    "****\n"+
    "-***\n";
    String _odoIcon2 = String("")+ //orange
    "***-----\n"+
    "****----\n"+
    "**-**---\n"+
    "**---**-\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**---**-\n"+
    "**-**---\n"+
    "****----\n"+
    "***-----\n";
    String _odoIcon3 = String("")+ //yellow (x0 = icon2.x0 + 4)
    "-******-\n"+
    "********\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "**----**\n"+
    "********\n"+
    "-******-\n";
};
#endif // _BIKE_SCREENH_