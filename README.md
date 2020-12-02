BikePC Brains (NodeMCU ESP8266)
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

Flashing
--------
You can flash the latest firmware from [releases](https://github.com/BlackCultistHub/BikePC/releases) the way you like.

Connect your board via usb or uart and [flash](https://nodemcu.readthedocs.io/en/latest/flash/) the firmware via [NodeMCU-Flasher](https://github.com/nodemcu/nodemcu-flasher) or any other tool you'd like.

Building
--------
You'll need:

1.[VS Code](https://code.visualstudio.com/)

2.[PlatformIO plugin](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

3.These libs:

   a) [Adafruit ST7735 and ST7789 Library](https://platformio.org/lib/show/12/Adafruit%20ST7735%20and%20ST7789%20Library)

   b) [NTPClient](https://platformio.org/lib/show/551/NTPClient)

   c) [Adafruit BusIO](https://platformio.org/lib/show/6214/Adafruit%20BusIO)

   d) [ESP8266TimerInterrupt](https://platformio.org/lib/show/6901/ESP8266TimerInterrupt)
