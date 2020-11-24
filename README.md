# LED nixie clock with Arduino

## Description
This repository is about a nixie clock based on an Arduino Nano board, an RTC module, and some LED nixie boards. 


## Bill of materials
* Arduino Nano
* [DS3231 Real time clock (RTS) module](https://www.banggood.com/DS3231-AT24C32-IIC-Precision-RTC-Real-Time-Clock-Memory-Module-p-1547989.html)<br>
This module is powered by a battery, equipped with a quartz oscillator, and maintains the clock even after being cut off from power. By doing so, the LED clock will not lose the information on the current time, even after plugged out from electricity.
* CR2032 battery
* 4x [LED nixie boards](https://www.led-genial.de/LED-Nixie-M-Einzelmodul-Bausatz) <br>
with 20 LEDs each
* 220 ohm resistor
* 100 nF capacitor <br>
This capacitor stabilizes the power supply and prevents the LEDs from flickering or dimming, when the digits are shifting and the dragged current is changing considerably. Since the LEDs switch quickly, a smaller capacitor might also do the job. Depending on your board and power supply, a capacitor might not be necessary whatsoever.
* Dupont jumper wires


## Libraries
* DS3231.h
* Adafruit_NeoPixel.h

## Data sheets
* [DS3231 Real time clock (RTS) module](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf)


## Links
* https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-real-time-clock-module-ds3231-bc90fe
