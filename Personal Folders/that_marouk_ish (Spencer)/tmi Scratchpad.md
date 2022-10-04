Summarized in [tmi Log](tmi%20Log.md)

[2022-10-04](2022-10-04)
https://docs.arduino.cc/software/ide-v1/tutorials/arduino-ide-v1-basics#sketchbook
- "When you upload a sketch, you're using the Arduino **bootloader**, a small program that has been loaded on to the microcontroller on your board. It allows you to upload code without using any additional hardware." 
- "Please note that the Serial Monitor does not process control characters; if your sketch needs a complete management of the serial communication with control characters, you can use an external terminal program and connect it to the COM port assigned to your Arduino board."

[2022-10-03](2022-10-03)
From https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573 on `millis()` vs `delay()` -> see [tmi 02 millis() forum examples](code/tmi%2002%20millis()%20forum%20examples/tmi%2002%20millis()%20forum%20examples.md)


[2022-10-02](2022-10-02)
- install zip libraries directly (no need to unpackage)
- a serial terminal is important to see the interaction with the Arduino via a computer - this is the Serial Monitor
- "Selecting which port to open in the Serial Monitor is the same as selecting a port for uploading Arduino code. Go to Tools -> Serial Port, and select the correct port." (source: [elegooCompleteStarterMega2560](elegooCompleteStarterMega2560.md)) - should be the same COM port as in DeviceManager
- [Mega2560](Mega2560.md) led is digital pin 13, see `LED_BUILTIN` variable
- tools > set board
- tools > set port (forgot this one)
- changed it to 500ms
- https://ht-deko.com/arduino/usb2serial.html#06 for [Serial to USB](Serial%20to%20USB.md) things (see [Serial Communication](Serial%20Communication.md)