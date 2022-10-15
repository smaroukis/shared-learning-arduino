parent::[Actuators and Sensors](Actuators%20and%20Sensors.md)

Example Part: LCD1602  
- `VSS:` A pin that connects toground  
- `VDD`: A pin that connects to a +5V powersupply  
- `VO`: A pin that adjust the contrast of LCD1602  
- `RS`: A register select pin that controls where in the LCD’s memory you are writing data to. You can select either the data register, which holds what goes on the screen, or an instruction register, which is where the LCD’s controller looks for instructions on what to do next.
- `R/W`: A Read/Write pin that selects reading mode or writing mode  
- `E`: An enabling pin that, when supplied with low-level energy, causes the LDC module to execute relevant instructions.  
- `D0-D7`:Pins that read and write data  
- `A `and `K`: Pins that control the LED backlight

Note rows are labeled as COLS, ROWS and are 0-indexed:
e.g. `lcd.begin(16, 2); // 16 cols, 2 rows` and `lcd.setCursor(0, 1) // set at the 1st column, 2nd row'

A pot is usally used to control the brightness of the display k

Pinout:
![](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221016001836.png)

```
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
```

**Resources**
- https://learn.adafruit.com/adafruit-arduino-lesson-11-lcd-displays-1/breadboard-layout
- https://learn.adafruit.com/adafruit-arduino-lesson-12-lcd-displays-part-2 - adds a temperature sensor (TMP36)
- basic weather project - https://create.arduino.cc/projecthub/Noshirt/arduino-weather-station-v1-0-bmp280-050e01?ref=tag&ref_id=lcd&offset=15
- TFT LCD displays - https://create.arduino.cc/projecthub/electropeak/ultimate-beginner-s-guide-to-run-tft-lcd-displays-by-arduino-081006?ref=tag&ref_id=lcd&offset=1