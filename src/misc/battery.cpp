#include "battery.h"

//@returns % of charge
uint8_t getBatteryCharge()
{
    if (analogRead(BATTERY_PIN_GPIO) >= 214)
        return 100;
    else if (analogRead(BATTERY_PIN_GPIO) >= 209)
        return 90;
    else if (analogRead(BATTERY_PIN_GPIO) >= 204)
        return 80;
    else if (analogRead(BATTERY_PIN_GPIO) >= 198)
        return 60;
    else if (analogRead(BATTERY_PIN_GPIO) >= 193)
        return 40;
    else if (analogRead(BATTERY_PIN_GPIO) >= 188)
        return 20;
    else if (analogRead(BATTERY_PIN_GPIO) >= 183)
        return 1;
    return 0;
}