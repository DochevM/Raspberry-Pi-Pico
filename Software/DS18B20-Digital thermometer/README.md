## Output
```
Locating devices...Found 1 devices.
Parasite power is: OFF
Device 0 Address: 28DCA4740E0000D9
Device 0 Resolution: 9
Temp C: 27.00
Temp C: 27.00
Temp C: 27.00
Temp C: 27.00
Temp C: 27.00

```

```
Locating devices...Found 2 devices.

Sensor 1 : 27.00°C
Sensor 2 : 26.62°C

Sensor 1 : 27.00°C
Sensor 2 : 26.62°C

```
## Connections

| Raspberry Pi Pico  |       DS18B20      |       DS18B20      |
| ------------------ | -------------------| -------------------|
| 3,3V               | Vdd                | Vdd                |
| GP22               | Dq                 | Dq                 |
| GND                | GND                | GND                |

![alt text](https://www.raspberrypi.com/documentation/microcontrollers/images/picow-pinout.svg)
