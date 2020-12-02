BikePC Brains
=============
This is a project of cycling computer with measuring speed, cadence and pulse in general.

It can also log the trip data on the sd-card and being set up via wi-fi.

Code is not modular yet.

> Note that this is the main module that comes to your bike.

> Pulsometer module that will connect to this main module is not ready yet so pulse will be always '0'

Schematic
---------
Current schematic of main module:
![Main_module](https://github.com/BlackCultistHub/ESP/blob/master/Resources/shematic.jpg?raw=true)

Building
--------
You'll need:

1.VS Code 

2.PlatformIO plugin

3.These libs:

      a) Adafruit ST7735 and ST7789 Library
      b) NTPClient
      c) Adafruit BusIO
      d) ESP8266TimerInterrupt
