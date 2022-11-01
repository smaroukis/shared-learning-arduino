parent::[[Actuators and Sensors]]

> Note: This is specifically about the 16 x 2 displays commonly used for beginner Arduino projects.

## Overview

The standard way of using an LCD will require 7 Arduino I/O pins (8 if you want to control backlight). This is an example of [[Parallel Communication.md|Parallel Communication]] on the pins `D0` to `D7`.

> [!tip]- Commonly you only need to connect 4 data pins 
> The LCD can be driven in `4-bit` parallel mode, which is the more common configuration that you will see in examples using the `LiquidCrystal` libary.	
> 
> This means you only need to connect RS, E, D4, D5, D6, and D7 pins to Arduino (see example below). (`RW`, `K`, and `VSS` go to `GND`; `VDD` &  `A` go to `+5V` )

There is another library that uses [[I2C]] (`LiquidCrystal_I2C`) that uses just the two `SCL` and `SCA` pins (in addition to `+V` and `GND`)

> [!note]- Block Diagram
> ![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221017112251.png]]

**Resources**
- https://docs.wokwi.com/parts/wokwi-lcd1602
- https://docs.arduino.cc/learn/electronics/lcd-displays

## Specifics for LCD1602

Example Part: LCD1602  - see [[Personal Folders/that_marouk_ish/attachments/Datasheet - LCD1602A LCD Display.pdf]]
- for quick reference see [[pinout - LCD1602]]
- typically using the popular [HD44780 LCD Controller](https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller) by Hitachi. 

> [!note]- Pin Descriptions 
> See Example in [[4-bit)](Table - LCD 16x2 Common Pin Configuration (4-bit|Table - LCD 16x2 Common Pin Configuration (4-bit)]].md))
> - `VSS:` A pin that connects to ground  
> - `VDD`: A pin that connects to a +5V power supply  
> - `VO`: A pin that adjust the contrast of LCD1602  
> - `RS`: A register select pin that controls where in the LCD’s memory you are writing data to. You can select either the data register, which holds what goes on the screen, or an instruction register, which is where the LCD’s controller looks for instructions on what to do next.
> - `R/W`: A Read/Write pin that selects reading mode or writing mode  
> - `E`: An enabling pin that, when supplied with low-level energy, causes the LDC module to execute relevant instructions.  
> - `D0-D7`:Pins that read and write data  
> - `A`: LED backlight anode (typ. connect to potentiometer or resistor)
> - `K`: LED backlight cathode (typ. -> GND)

> [!EXAMPLE]- Example Pin Configuration for LCD in 4-Bit Mode
> ![[4-bit)](Table - LCD 16x2 Common Pin Configuration (4-bit|Table - LCD 16x2 Common Pin Configuration (4-bit)]].md)

## Example

#refactor to standalone, fix deprecated nomenclautre

#code - LCD Hello World Example 
```c
// http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
```

Note if you print without clearing or resetting cursor it will just append the data.

> [!note]- Schematic: 16x2 LCD with HD44780 Driver in 4-bit Mode
> ![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221017115858.png]]

> [!CAUTION] Route to the correct [[SPI]] pins on the Arduino side as required

Note rows are labeled as COLS, ROWS and are 0-indexed:

### LCD Library Functions
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/liquidcrystal|LiquidCrystal()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/begin|begin()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/clear|clear()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/home|home()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/setcursor|setCursor()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/write|write()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/print|print()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/cursor|cursor()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/nocursor|noCursor()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/blink|blink()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/noblink|noBlink()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/display|display()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/nodisplay|noDisplay()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/scrolldisplayleft|scrollDisplayLeft()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/scrolldisplayright|scrollDisplayRight()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/autoscroll|autoscroll()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/noautoscroll|noAutoscroll()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/lefttoright|leftToRight()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/righttoleft|rightToLeft()]]
-   [[)](https://www.arduino.cc/reference/en/libraries/liquidcrystal/createchar|createChar()]]

## References and More
[1] https://docs.wokwi.com/parts/wokwi-lcd1602

**Resources**
- https://learn.adafruit.com/adafruit-arduino-lesson-11-lcd-displays-1/breadboard-layout
- https://learn.adafruit.com/adafruit-arduino-lesson-12-lcd-displays-part-2 - adds a temperature sensor (TMP36)
- basic weather project - https://create.arduino.cc/projecthub/Noshirt/arduino-weather-station-v1-0-bmp280-050e01?ref=tag&ref_id=lcd&offset=15
- TFT LCD displays - https://create.arduino.cc/projecthub/electropeak/ultimate-beginner-s-guide-to-run-tft-lcd-displays-by-arduino-081006?ref=tag&ref_id=lcd&offset=1

**Further - Hardware**
- Hitachi HD44780 LCD controller (https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller) 
- PCF8574 Remote 8-Bit I/O Expander for I 2C Bus https://www.ti.com/lit/ds/symlink/pcf8574.pdf) used to only require 4 parallel data inputs