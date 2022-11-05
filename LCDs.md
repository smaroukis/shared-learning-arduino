parent::[Actuators and Sensors](Actuators%20and%20Sensors.md)

> Note: This is specifically about the 16 x 2 displays commonly used for beginner Arduino projects.

## Overview

The standard way of using an LCD will require 7 Arduino I/O pins (8 if you want to control backlight). This is an example of [Parallel Communication](Parallel%20Communication.md) on the pins `D0` to `D7`.

> [!tip]- Commonly you only need to connect 4 data pins 
> The LCD can be driven in `4-bit` parallel mode, which is the more common configuration that you will see in examples using the `LiquidCrystal` libary.	
> 
> This means you only need to connect RS, E, D4, D5, D6, and D7 pins to Arduino (see example below). (`RW`, `K`, and `VSS` go to `GND`; `VDD` &  `A` go to `+5V` )

There is another library that uses [I2C](I2C.md) (`LiquidCrystal_I2C`) that uses just the two `SCL` and `SCA` pins (in addition to `+V` and `GND`)

> [!note]- Block Diagram
> ![Pasted image 20221017112251](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221017112251.png)

**Resources**

## Specifics for LCD1602

[Example - LCD1602 Hello World](Example%20-%20LCD1602%20Hello%20World.md) - has the pin setup, etc, and code

## References and More

**References**
[1] https://docs.wokwi.com/parts/wokwi-lcd1602

**Resources**
- https://docs.wokwi.com/parts/wokwi-lcd1602
- https://docs.arduino.cc/learn/electronics/lcd-displays
- https://learn.adafruit.com/adafruit-arduino-lesson-11-lcd-displays-1/breadboard-layout
- https://learn.adafruit.com/adafruit-arduino-lesson-12-lcd-displays-part-2 - adds a temperature sensor (TMP36)

**Example Projects**
- basic weather project - https://create.arduino.cc/projecthub/Noshirt/arduino-weather-station-v1-0-bmp280-050e01?ref=tag&ref_id=lcd&offset=15
- TFT LCD displays - https://create.arduino.cc/projecthub/electropeak/ultimate-beginner-s-guide-to-run-tft-lcd-displays-by-arduino-081006?ref=tag&ref_id=lcd&offset=1

**Further - Hardware**
- Hitachi HD44780 LCD controller (https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller) 
- PCF8574 Remote 8-Bit I/O Expander for I 2C Bus https://www.ti.com/lit/ds/symlink/pcf8574.pdf) used to only require 4 parallel data inputs