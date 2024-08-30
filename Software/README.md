# Used sensors

## DHT11-Digital temperature and humidity sensor
The [DHT11](https://github.com/DochevM/Raspberry-Pi-Pico/blob/main/Documents/DHT11_Datasheet.pdf) is a basic, ultra low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air, and spits out a digital signal on the data pin (no analog input pins needed). 

 ### Library used for DHT11
 - [DHT sensor library](https://github.com/adafruit/DHT-sensor-library?utm_source=platformio&utm_medium=piohome)

## DHT22-Digital temperature and humidity sensor
[DHT22](https://github.com/DochevM/Raspberry-Pi-Pico/blob/main/Documents/DHT22_Datasheet.pdf) (or AM2302) is also a low cost digital temperature and humidity sensor, but it has a better accuracy and bigger range of the readings.
 ### Library for DHT22
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library?utm_source=platformio&utm_medium=piohome)

## DS18B20-Digital temperature sensor
The [DS18B20](https://github.com/DochevM/Raspberry-Pi-Pico/blob/main/Documents/DS18B20.pdf) is a digital temperature sensor provides 9-bit to 12-bit Celsius temperature measurements and has an alarm function with nonvolatile user-programmable upper and lower trigger points. Each DS18B20 has a unique 64-bit serial code, which allows multiple DS18B20s to function on the same 1-Wire bus.
 ### Libraries for DS18B20 
 - [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)
 - [OneWire](https://github.com/PaulStoffregen/OneWire)

## MCP9701A-Analog temperature sensor
MCP9700/A/B and [MCP9701/A](https://github.com/DochevM/Raspberry-Pi-Pico/blob/main/Documents/MCP970X-Family-Data-Sheet-DS20001942L.pdf) is a sensor with Linear Active Thermistor Integrated Circuit (IC) comprise a family of analog temperature sensors that convert temperature to analog voltage.


   **_No libraries required_**


## WEA012864D-OLED Display
[WEA012864D](https://github.com/DochevM/Raspberry-Pi-Pico/blob/main/Documents/WEA012864D.pdf) version OLED module is a diagonal size 0.96 inch COG OLED display with PCB board on it. This WEA012864D version OLED panel is made of 128x64 pixels.
### Libraries for WEA012864D
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) 
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)

## GDEY029T94-E-Paper display
[GDEY029T94](https://github.com/DochevM/Raspberry-Pi-Pico/blob/main/Documents/GDEY029T94.pdf)is an e ink screen, 2.9 inch, with 296x128 resolution, SSD1680, SPI interface. The 2.9'' e ink supports 4 grayscales and partial refresh. It can be customized to achieve 1.5s fast refresh.
### Libraries
- [GxEPD2](https://github.com/ZinggJM/GxEPD2)
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) 

## GDEW0154Z17-E-Paper display
[GDEW0154Z17](https://github.com/DochevM/Raspberry-Pi-Pico/blob/main/Documents/GDEW0154Z17.pdf) is an E ink display panel, 1.54 inch, 152x152 resolution, square, 24 pins FPC connection, optional FPC connector, communicating via SPI interface, with embedded controller(COG package) and on-chip stored waveform,supports red, black, and white three-color.
### Libraries
- [GxEPD2](https://github.com/ZinggJM/GxEPD2)
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) 






