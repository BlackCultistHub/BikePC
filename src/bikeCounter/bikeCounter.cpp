#include "bikeCounter.h"

bikeCounter::bikeCounter()
{
    timer_downtime = millis();
}

//check if need to reset
bool bikeCounter::elapsed()
{
    if ((millis() - timer_downtime) > 8000)
    {
        //CADENCE
        rpm = 0;
        //SPD
        speed = 0;
        //pulse
        pulseRaw = "";
        pulseUint = 0;

        timer_downtime = millis();
        return true;
    }
    return false;
}

void bikeCounter::init()
{
    radiusRAW = EEPROMGetWheelRadius();
    odo = EEPROMGetODO();
}

//Starter funcs
bool bikeCounter::initSD(const uint8_t cs_pin, String* errormsg)
{
        if (!SD.begin(cs_pin))
    {
        if (errormsg != nullptr)
            *errormsg = "Could not start SD!";
        return false;
    }
    if (!SD.exists("Data"))
    {
        if (!SD.mkdir("Data"))
        {
            if (errormsg != nullptr)
                *errormsg = "Could not create Data directory!";
            return false;
        }
    }
    if (!SD.exists("Logs"))
    {
        if (!SD.mkdir("Logs"))
        {
            if (errormsg != nullptr)
                *errormsg = "Could not create Logs directory!";
            return false;
        }
    }
    if (!SD.exists("Web"))
    {
        if (!SD.mkdir("Web"))
        {
            if (errormsg != nullptr)
                *errormsg = "Could not create Web directory!";
            return false;
        }
        else
        {
            auto file = SD.open("Web/ReadMe.txt", FILE_WRITE);
            if (!file)
            {
                if (errormsg != nullptr)
                    *errormsg = "Could not create ReadMe.txt file!";
                return false;
            }
            else
            {
                file.println("Please copy web files in this folder if you want charts to work!");
                file.println("Пожалуйста скопируйте веб-файлы сюда, если хотите, чтобы графики работали!");
                file.println("---LINK---");
                file.close();
            }
        }
    }
    sdCardReady = true;
    return true; 
}

//***[Cadence - RPM]***
//impulse
void bikeCounter::cad_impulse()
{
    if (micros() - lastIsrRpm > 170000)
    {
        if (!tripIsRunning())
            trip_start();
        timer_downtime = millis();
        rpm = 60/((float)(micros()-lastIsrRpm)/1000000); 
        rpm_summ += rpm;
        rpm_measures++;
        lastIsrRpm = micros();
        rpm_updated = true;
    }
}
uint16_t bikeCounter::getCadence()
{
    return rpm;
}

//***[TRIP]***
void bikeCounter::trip_start()
{
    tripStartTimer = millis();
    tripStartDate = String(EEPROMGetDay()) + "." + String(EEPROMGetMonth()) + "." + String(EEPROMGetYear());
    EEPROMSetTripStartDate(tripStartDate);
    String daysOfTheWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    tripStartDateDayOfTheWeek = daysOfTheWeek[EEPROMGetDayOfTheWeek()];
}
void bikeCounter::trip_stop()
{
    String currentDate = String(EEPROMGetDay()) + "." + String(EEPROMGetMonth()) + "." + String(EEPROMGetYear());
    tripStartDate = EEPROMGetTripStartDate();
    //Serial.println(currentDate);
    //Serial.println(tripStartDate);
    tripStartTimer = 0;
    if (currentDate != tripStartDate)
        EEPROMSetTripNumber(0);
    tripStartDate = "none";
    tripStartDateDayOfTheWeek = "none";
    EEPROMSetTrip(0);
    EEPROMSetTripHours(0);
    EEPROMSetTripMinutes(0);
    trip = 0;
    EEPROMSetTripSpd(0);
    spd_measures = 0;
    spd_summ = 0;
    EEPROMSetTripCad(0);
    rpm_summ = 0;
    rpm_measures = 0;
    EEPROMSetTripPulse(0);
    pulse_summ = 0;
    pulse_measures = 0;
    EEPROMSetTripNumber(EEPROMGetTripNumber() + 1);
}
bool bikeCounter::tripIsRunning()
{
    if (tripStartTimer == 0)
        return false;
    else
        return true;
}
uint8_t bikeCounter::getCurrentTripNumber()
{
    return EEPROMGetTripNumber();
}
float bikeCounter::getSessionTrip()
{
    return EEPROMGetTrip() + trip;
}
//***[SPEED]***
//real-time speed
void bikeCounter::spd_impulse()
{
    if (millis() - lastIsrSpd > 90)
    {
        if (!tripIsRunning())
            trip_start();

        timer_downtime = millis();

        //speed
        float rad = (float)radiusRAW/1000;
        float wheel_len = 2*PI*rad; //meters
        float down = (float)(millis()-lastIsrSpd)/1000;
        speed = (wheel_len/down)*3.6;
        lastIsrSpd = millis();
        //Serial.println(speed);
        //average speed
        spd_summ += speed;
        spd_measures++;
        //trip
        trip += wheel_len;
        odo += wheel_len;
        //Serial.println(trip);
        spd_updated = true;
        trip_updated = true;
        odo_updated = true;
    }
}
uint8_t bikeCounter::getSpeed()
{
    return speed;
}
uint8_t bikeCounter::getAverageSpeedPerTrip()
{
    return EEPROMGetTripSpd();
}
uint8_t bikeCounter::getAverageCadencePerTrip()
{
    return EEPROMGetTripCad();
}
uint8_t bikeCounter::getAveragePulsePerTrip()
{
    return EEPROMGetTripPulse();
}

void bikeCounter::saveStats() //eeprom
{
    //save trip (eeprom)
    auto savedTrip = EEPROMGetTrip();
    EEPROMSetTrip(savedTrip + trip);
    trip = 0;
    //save odo (eeprom)
    EEPROMSetODO(odo);
    odo_updated = true;
    //save avgSpd per trip (eeprom)
    auto savedSpeed = EEPROMGetTripSpd();
    EEPROMSetTripSpd((savedSpeed + getAverageSpeed())/2);
    //avg cad
    auto savedCad = EEPROMGetTripCad();
    EEPROMSetTripCad((savedCad + getAverageCad())/2);
    //avg pulse
    auto savedPulse = EEPROMGetTripPulse();
    EEPROMSetTripPulse((savedPulse + getAveragePulse())/2);
}

bool bikeCounter::saveStatsSD()
{
    if (!sdCardReady)
        return false;
    //prepare
    String daysOfTheWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    String folderDatePath;
    if (tripIsRunning())
        folderDatePath = "Data/" + tripStartDate + " " + tripStartDateDayOfTheWeek;
    else
        folderDatePath = "Data/" + String(EEPROMGetDay()) + "." + String(EEPROMGetMonth()) + "." + String(EEPROMGetYear()) + " " + daysOfTheWeek[EEPROMGetDayOfTheWeek()];
    String folderTripPath = folderDatePath + "/Trip-" + String(getCurrentTripNumber());
    String separatedPath = folderTripPath + "/Separated";
    if (!SD.exists(folderDatePath))
    {
        SD.mkdir(folderDatePath);
        SD.mkdir(folderTripPath);
        SD.mkdir(separatedPath);
    }
    else if (!SD.exists(folderTripPath))
    {
        SD.mkdir(folderTripPath);
        SD.mkdir(separatedPath);
    }
    else if (!SD.exists(separatedPath))
        SD.mkdir(separatedPath);
    auto write_date = String(EEPROMGetDay()) + "." + String(EEPROMGetMonth()) + "." + String(EEPROMGetYear());
    auto write_time = String(EEPROMGetHours()) + ":" + String(EEPROMGetMinutes());
    auto write_speed = String(speed);
    auto write_cadence = String(rpm);
    auto write_trip = String(getSessionTrip());
    auto write_pulse = String(pulseRaw)==""?"-":String(pulseRaw);
    //separated
    //save trip
        auto tripFile = SD.open(separatedPath + "/Trip.csv", FILE_WRITE);
        tripFile.println(write_date + ";" + write_time + ";" + write_trip + ";");
        tripFile.close();
    //save cadence (sd)
        auto cadFile = SD.open(separatedPath + "/Cadence.csv", FILE_WRITE);
        cadFile.println(write_date + ";" + write_time + ";" + write_cadence + ";");
        cadFile.close();
    //save pulse (sd)
        auto pulseFile = SD.open(separatedPath + "/Pulse.csv", FILE_WRITE);
        pulseFile.println(write_date + ";" + write_time + ";" + write_pulse + ";");
        pulseFile.close();
    //save speed (sd)
        auto speedFile = SD.open(separatedPath + "/Speed.csv", FILE_WRITE);
        speedFile.println(write_date + ";" + write_time + ";" + write_speed + ";");
        speedFile.close();
    //combined
        bool firstWrite = true;
        if (SD.exists(folderTripPath + "/Combined_data.csv"))
            firstWrite = false;
        auto combinedFile = SD.open(folderTripPath + "/Combined_data.csv", FILE_WRITE);
        if (firstWrite)
            combinedFile.println("Date;Time;Cadence;Pulse;Trip;Speed;");
        combinedFile.println(write_date + ";" + write_time + ";" + write_cadence + ";" + write_pulse + ";" + write_trip + ";" + write_speed + ";");
        combinedFile.close();
    //save stats
        if (SD.exists(folderTripPath + "/TripStats.txt")) 
            SD.remove(folderTripPath + "/TripStats.txt");
        auto statsFile = SD.open(folderTripPath + "/TripStats.txt", FILE_WRITE);
        statsFile.println(
            "Trip time: " + String(EEPROMGetTripHours()) + " h, " + String(EEPROMGetTripMinutes()) + " m\n" +
            "Total trip: " + String(getSessionTrip()) + " km\n" +
            "Average speed: " + String(getAverageSpeedPerTrip()) + " km/h\n" +
            "Average pulse: " + String(getAveragePulsePerTrip()) + " bpm\n" +
            "Average cadence: " + String(getAverageCadencePerTrip()) + " rpm\n" +
            "ODO: " + String(EEPROMGetODO()) + " m");
        statsFile.close();
    //save odo
        if (SD.exists("ODO.txt"))
            SD.remove("ODO.txt");
        auto odoFile = SD.open("ODO.txt", FILE_WRITE);
        odoFile.println(String(EEPROMGetODO()) + " m");
        odoFile.close();
    return true;
}

//updated detection
bool bikeCounter::cadenceUpdated() 
{
    if (rpm_updated)
    {
        rpm_updated = false;
        return true;
    }
    else
        return false;
}
bool bikeCounter::speedUpdated()
{
    if (spd_updated)
    {
        spd_updated = false;
        return true;
    }
    else
        return false;
}
bool bikeCounter::tripUpdated()
{
    if (trip_updated)
    {
        trip_updated = false;
        return true;
    }
    else
        return false;
}
bool bikeCounter::avgSpdUpdated()
{
    if (avgspd_updated)
    {
        avgspd_updated = false;
        return true;
    }
    else
        return false;
}
bool bikeCounter::odoUpdated()
{
    if (odo_updated)
    {
        odo_updated = false;
        return true;
    }
    else
        return false;
}
bool bikeCounter::tripNumberUpdated()
{
    if (tripNumber_updated)
    {
        tripNumber_updated = false;
        return true;
    }
    else
        return false;
}

void bikeCounter::updateRadius(uint16_t radius_mm)
{
    radiusRAW = radius_mm;
}